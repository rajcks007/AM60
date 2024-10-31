/**
*@file          ADC.c
*/
#pragma language = extended
#include <ioavr.h>
#include "ADC.h"
#include "board_conf.h"
#include "NVM.h"
#include "common.h"
#include "delay.h"
typedef uint8_t __flash uint8f_t;


__flash Def_ADC_Gain(ADC_CH_Gain);              //CHANNEL CTRL : Gain Faktor [6] Faktoren
__flash Def_ADC_InMo(ADC_CH_Input_mode);        //CHANNEL CTRL : Input Mode[2] 2 M򧬩chkeiten
__flash Def_ADC_MPi(ADC_CH_MUX_Internal);      //CHANNEL MUX  : Internal Sources [2]
__flash Def_ADC_MPPP(ADC_CH_MUX_POS);           //CHANNEL MUX  : Pin Nr[8] 0-7
__flash Def_ADC_INTL(ADC_CH_INT_Level);         //CHANNEL INT  : INT Level[4]




static void Register_in_Feld(uint8_t* Feld, uint8_t Reg7, uint8_t Reg6, uint8_t Reg5, uint8_t Reg4, uint8_t Reg3, uint8_t Reg2, uint8_t Reg1, uint8_t Reg0);

uint8_t ADC_A_CH_Def[4][8];                        //ADC A Kanal Definitionen

void ADC_init() {
    if (ADC_A_aktiv == OK)   //...................ADC A aktivieren
    {
        ADCA.CTRLA = __ADC_A_CTRL_A;                  // Control Register A
        ADCA.CTRLB = __ADC_A_CTRL_B;                  // Control Register B
        ADCA.REFCTRL = __ADC_A_REFCTRL;                 // Referenz Control
        ADCA.EVCTRL = __ADC_A_EVCTRL;                  // Event Control
        ADCA.PRESCALER = __ADC_A_PRESCALE;                 // Clock Prescaler
        Register_in_Feld(ADC_A_CH_Def[0], __ADC_A_Gain);   // Kanal DEF [0-7] Gain
        Register_in_Feld(ADC_A_CH_Def[1], __ADC_A_Mode);   // Kanal DEF [0-7] Mode
        Register_in_Feld(ADC_A_CH_Def[2], __ADC_A_Mux);    // Kanal DEF [0-7] Mux
        Register_in_Feld(ADC_A_CH_Def[3], __ADC_A_INT);    // Kanal DEF [0-7] INT
    }
}

/*****************************************************************************************************
                                 Register_in_Feld
Eine mit #define erstellte 8 Byte Register definition wird zur besseren Weiterverarbeitung
in ein Feld umgespeichert
*******************************************************************************************************/
static void Register_in_Feld(uint8_t* Feld, uint8_t Reg7, uint8_t Reg6, uint8_t Reg5, uint8_t Reg4, uint8_t Reg3, uint8_t Reg2, uint8_t Reg1, uint8_t Reg0) {
    Feld[0] = Reg0;
    Feld[1] = Reg1;
    Feld[2] = Reg2;
    Feld[3] = Reg3;
    Feld[4] = Reg4;
    Feld[5] = Reg5;
    Feld[6] = Reg6;
    Feld[7] = Reg7;
}



/*****************************************************************************************************
                            ADC_SET_Calibration_BYTE
Die ADC Calibrations Byte werden gelesen und gespeichert in
        ADCACAL0_offset = 0x20, // ADCA Calibration Byte 0
    ADCACAL1_offset = 0x21, // ADCA Calibration Byte 1
    ADCBCAL0_offset = 0x24, // ADCB Calibration Byte 0
    ADCBCAL1_offset = 0x25, // ADCB Calibration Byte 1
*******************************************************************************************************/
void ADC_SET_Calibration_BYTE(void) {
    ADCA.CALL = Read_Calibrations_Byte(0x20);
    ADCA.CALH = Read_Calibrations_Byte(0x21);
}


/*****************************************************************************************************
                           Init_ADC_Kanal
Einer der 4 ADC Kan孥 wird initialisiert aber nicht gestartet
ADC     : pointer auf ADC A oder B Register Definitionen siehe "ATmega128A1.h" "ADC_struct....ADC_t"
CH_Nr   : Kanal 0-3 kann definiert werden; Pro ADC k򮮥n 4 Kan孥 definiert werden
Def_Nr  : Definition Nr 0-7 welche dem Kanal 0-3 zugewiesen wird

CH_Def  : Pointer auf die in "ADC_A_CH_Def" umgespeicherten Chanal Definitionen aus "XMEGA128_def.h"
*******************************************************************************************************/
void Init_ADC_Kanal(ADC_t* ADC, uint8_t CH_Nr, uint8_t Def_Nr) {
    uint8f_t* Ptr;
    uint8_t(*CH_Def)[8];
    ADC_CH_t* ADC_CH;

    if (Def_Nr > 7) return;                              //max 0-7 Kanal Definitionen
    if (CH_Nr > 3) return;                               //max 0-3 Kan孥 m򧬩ch

    if (ADC == &ADCA) CH_Def = ADC_A_CH_Def;             //Kanal Definitionen
    if (ADC == &ADCB) CH_Def = ADC_A_CH_Def;             //Kanal Definitionen

    switch (CH_Nr)                  //....................Kanalnummer
    {
        case 0:
            ADC_CH = &ADC->CH0;
            break;            //Pointer auf ADC_CH = ADCx.CH0.
        case 1:
            ADC_CH = &ADC->CH1;
            break;            //Pointer auf ADC_CH = ADCx.CH1.
        case 2:
            ADC_CH = &ADC->CH2;
            break;            //Pointer auf ADC_CH = ADCx.CH2.
        case 3:
            ADC_CH = &ADC->CH3;
            break;            //Pointer auf ADC_CH = ADCx.CH3.
    }

    Ptr = (uint8f_t*)&ADC_CH_Gain;       //............REG CTRL 4:2 Gain
    if (CH_Def[0][Def_Nr] > 6) return;                             //max 0-6
    CLR_BIT(ADC_CH->CTRL, (0x07 << 2));
    ADC_CH->CTRL = ADC_CH->CTRL | Ptr[CH_Def[0][Def_Nr]];

    Ptr = (uint8f_t*)&ADC_CH_Input_mode;  //............REG CTRL 1:0 Input Mode
    if (CH_Def[1][Def_Nr] > 1) return;                             //max 0-1  bisher kein Differenzeingang zul
    CLR_BIT(ADC_CH->CTRL, (0x03 << 0));
    ADC_CH->CTRL = ADC_CH->CTRL | Ptr[CH_Def[1][Def_Nr]];

    if (Ptr[CH_Def[1][Def_Nr]] == 0) //........if Input Mode = internal
    {
        Ptr = (uint8f_t*)&ADC_CH_MUX_Internal;  //................REG MUXCTRL 6:3 internal an Chanel
        if (CH_Def[2][Def_Nr] > 3) return;                             //max 0-3
        CLR_BIT(ADC_CH->MUXCTRL, (0x07 << 3));
        ADC_CH->MUXCTRL = ADC_CH->MUXCTRL | Ptr[CH_Def[2][Def_Nr]];
    }
    else                                //........else external Pin
    {
        Ptr = (uint8f_t*)&ADC_CH_MUX_POS; //................REG MUXCTRL 6:3 Pin an Chanel
        if (CH_Def[2][Def_Nr] > 7) return;                             //max 0-7
        CLR_BIT(ADC_CH->MUXCTRL, (0x07 << 3));
        ADC_CH->MUXCTRL = ADC_CH->MUXCTRL | Ptr[CH_Def[2][Def_Nr]];
    }

    Ptr = (uint8f_t*)&ADC_CH_INT_Level;  //............REG INT CTRL 1:0 INT Level
    if (CH_Def[3][Def_Nr] > 3) return;                             //max 0-3
    CLR_BIT(ADC_CH->INTCTRL, (0x03 << 0));
    ADC_CH->INTCTRL = ADC_CH->INTCTRL | Ptr[CH_Def[3][Def_Nr]];
}


/*****************************************************************************************************
                           ADC_Kanal_messen
Eine Wandlung gestartet; Der entsprechende Kanal 0-3 muss zuvor initialisert sein
ADC   : ADC_A oder ADC_B
CH_Nr : ADC Kanal 0 - 3
Anzahl: aus wievielen Werten wird ein Wert gemittelt;
Delay : Pause zwischen den Samples in 10 usec Einheiten
*******************************************************************************************************/
uint16_t ADC_Sample_Single(ADC_t* ADC, uint8_t CH_Nr, uint8_t Anzahl, uint16_t Delay) {
    ADC_CH_t* ADC_CH;
    unsigned short Result;
    unsigned long Summe;
    unsigned char i;
    SET_BIT(ADC->CTRLA, ADC_ENABLE_bm);                        //ADC freigeben

    switch (CH_Nr)                  //....................Kanalnummer
    {
        case 0:
            ADC_CH = &ADC->CH0;
            break;            //Pointer ADC_CH = ADCx.CH0.
        case 1:
            ADC_CH = &ADC->CH1;
            break;
        case 2:
            ADC_CH = &ADC->CH2;
            break;
        case 3:
            ADC_CH = &ADC->CH3;
            break;
    }

    DELAY_wait_10us_busily(1);
    Summe = 0;
    for (i = 0; i < Anzahl; i++) {
        SET_BIT(ADC_CH->INTFLAGS, 0x01);                //Interrupt Flag l򳣨en
        SET_BIT(ADC_CH->CTRL, ADC_CH_START_bm);         //start Conversion
        while ((ADC_CH->INTFLAGS & 0x01) == 0);         //warte bis Interrupt Flag gesetzt
        Summe = Summe + ADC_CH->RES;                   //Ergebnis lesen
        if (Delay > 0)DELAY_wait_10us_busily(Delay);
    }
    CLR_BIT(ADC->CTRLA, ADC_ENABLE_bm);                        //ADC sperren
    Result = Summe / Anzahl;
    return Result;
}

