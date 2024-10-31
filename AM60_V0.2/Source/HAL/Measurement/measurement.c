/**
*@file  measurement.c
*/
#include <ioavr.h>
#include "measurement.h"
#include <stdint.h>
#include "common.h"
#include "timer.h"
#include "delay.h"
#include "ADC.h"
#include "utilities.h"
#include "LCD.h"
#include "button.h"
static uint16_t Abtastzeit_Timer_D0_berechnen (uint16_t Abtastfrequenz);

/*****************************************************************************************************
                           Init_ADC_NF_Signal
Der ADC Chanel 0 f𲠎F Signalmessung wird freigegeben
*******************************************************************************************************/
void Init_ADC_NF_Signal (void){
    Init_ADC_Kanal (&ADCA, __ADC_CH0, 0);                // zeitsignal
}


/*****************************************************************************************************
                       NF_Signal_sampling
Eine Wandlung gestartet; Der entsprechende Kanal 0-3 muss zuvor initialisert sein
ADC   : ADC_A oder ADC_B
CH_Nr : ADC Kanal 0 - 3
Sample_data : Feld f𲠄aten float oder short
Anzahl: aus wievielen Werten wird ein Wert gemittelt;
Abtastfrequenz :  Abtastfrequenz = 2 * Eckfrequenz
*******************************************************************************************************/
void NF_Signal_sampling (ADC_t *ADC, uint8_t CH_Nr, uint16_t *const Sample_data, const uint16_t Anzahl, uint16_t Abtastfrequenz){
    ADC_CH_t *ADC_CH;
    SET_BIT(ADC->CTRLA, ADC_ENABLE_bm);              //ADC freigeben

    switch (CH_Nr){
    case __ADC_CH0:
        ADC_CH = &ADC->CH0;
        break;      
    case __ADC_CH1:
        ADC_CH = &ADC->CH1;
        break;
    case __ADC_CH2:
        ADC_CH = &ADC->CH2;
        break;
    case __ADC_CH3:
        ADC_CH = &ADC->CH3;
        break;
    }
    TCD0.CCA = Abtastzeit_Timer_D0_berechnen(Abtastfrequenz);  //Timer D0 compare Reg setzen
    DELAY_wait_10us_busily(1);
    TIM_start_D0();                       //freilaufender Timer D0 = Abtastfrequenz
    for(uint16_t i = 0; i < Anzahl; i++){
        SET_BIT(ADC_CH->INTFLAGS, 0x01);                //Interrupt Flag l@chen
        SET_BIT(ADC_CH->CTRL, ADC_CH_START_bm);         //start Conversion
        while((ADC_CH->INTFLAGS & 0x01) == 0);         //warte bis Interrupt Flag gesetzt
        Sample_data[i] = ADC_CH->RES;   //Ergebnis lesen
        while((TCD0_INTFLAGS & TC1_CCAIF_bm) == 0);    //Timer D0 warte bis compare
        SET_BIT(TCD0_INTFLAGS, TC1_CCAIF_bm);           //Timer D0 INT Flag zur𣫳etzen
    }
    TIM_stop_D0();
    CLR_BIT(ADC->CTRLA, ADC_ENABLE_bm);              //ADC sperren

}

/*******************************************************************************************
                             Abtastzeit_Timer_D0_berechnen
f𲠤ie 𢥲gebene Eckfrequenz wird die Wartezeit des Timer C1 berechnet
Takte = Quarzfrequenz / (Abtastfrequenz * Clockteiler)
hier : (Quarz) 16000000  / (Abtastfrequenz * 1 (Clockteiler))
**********************************************************************************************/
static uint16_t Abtastzeit_Timer_D0_berechnen (uint16_t Abtastfrequenz){
    return (uint16_t) (16000000 / Abtastfrequenz);
}

uint16_t MEAS_fit_to_calib_val(const uint16_t calib_val, const uint16_t meas_val){
   
    return ( meas_val > calib_val) ? (meas_val - calib_val) : (0);
}

    uint16_t Puffer[Puffer_size];

uint16_t MEAS_read_val (const MEAS_meas_par_t *const mP, const uint16_t calib_val){
    uint16_t *(buffer) = Puffer;

    uint16_t calibrated__mean_val;
    uint32_t sum = 0;
    uint16_t mean_val = 0;
    uint16_t lower_limit = mP->sample_size -  mP->mean_size - 1;     // range to build a mean value
    uint16_t upper_limit = mP->sample_size - 1;
    
    NF_Signal_sampling (&ADCA, __ADC_CH0, buffer, mP->sample_size, mP->sampling_rate);

    selectionSortAscU16 (buffer, mP->sample_size);

    for(uint16_t i = upper_limit; i >= lower_limit ; i--){
        sum += buffer[i];
    }
    mean_val = sum / mP->mean_size;
    
    calibrated__mean_val = MEAS_fit_to_calib_val(calib_val, mean_val);
    
    return calibrated__mean_val;
    

}


uint16_t MEAS_read_calib_val(void){
    uint16_t calib_val = 0;

#define SAMPLE_SIZE 20
#define SAMPLING_RATE 1800

    uint16_t cal_buf [SAMPLE_SIZE];
    NF_Signal_sampling (&ADCA, __ADC_CH0, cal_buf, SAMPLE_SIZE, SAMPLING_RATE);

    for(uint8_t i = 0; i < SAMPLE_SIZE; i++){
       calib_val += cal_buf[i];
    }
     return calib_val / SAMPLE_SIZE;
}



/****************************************************************************************************
                                 MEAS_reset_calibration
Die Kalibration wird zur𣫧esetzt
*******************************************************************************************************/
uint16_t MEAS_reset_calibration (void){
#define BUTTON_PRESSED_CNT_MS   3
    
    uint8_t push_cnt = 0, Flag1;
    
    while (push_cnt < BUTTON_PRESSED_CNT_MS)    {
        if (BUT_is_right_button_pressed() == NOT_OK) push_cnt++;
        else push_cnt = 0;
        Flag1++;
        if(Flag1 > 1){
            Code_an_LCD (0x1E, 0x72);
            Flag1 = 0;
        }
        else Code_an_LCD (0x72, 0x1E);
        DELAY_wait_1ms_busily(120);
    }
    Code_an_LCD (0x00, 0x1C);                  
    DELAY_wait_1ms_busily(1000);
   
    return MEAS_read_calib_val();
}



/**
 * This function calculates the floating mean value of an array of uint8_t values.
 *
 * @param floating_mean_val floating_mean_val is a pointer to a struct of type floating_mean_val_t.
 * This struct contains an array of uint8_t values and a variable to keep track of the current index in
 * the array. The purpose of this function is to calculate the mean value of the elements in the array.
 *
 * @return a uint8_t value, which is the calculated floating mean value of the array stored in the
 * floating_mean_val_t struct.
 */
uint8_t MEAS_calculate_floating_mean_val(const floating_mean_val_t* const floating_mean_val) {
    uint16_t rv = 0;

    for (uint8_t i = 0; i < sizeof(floating_mean_val->arr); i++) {
        rv += floating_mean_val->arr[i];
    }

    rv /= sizeof(floating_mean_val->arr);

    return (uint8_t)rv;
}


/**
 * The function pushes a value to an array and updates the index, wrapping around if necessary.
 *
 * @param floating_mean_val a pointer to a struct of type floating_mean_val_t, which contains an array
 * of uint8_t values and an index indicating the current position in the array.
 * @param val The value to be added to the array in the floating_mean_val struct.
 */
void MEAS_push_back(floating_mean_val_t* const floating_mean_val, const uint8_t val) {
    floating_mean_val->arr[floating_mean_val->index] = val;
    floating_mean_val->index++;

    if (floating_mean_val->index == sizeof(floating_mean_val->arr)) {
        floating_mean_val->index = 0;
    }
}