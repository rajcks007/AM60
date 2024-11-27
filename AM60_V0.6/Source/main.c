/**
*@file          main.c
*
*/
#include <ioavr.h>     
#include <stdlib.h>
#include <stdio.h>
#include <math.h>                           
#include <intrinsics.h>
#include "gpio.h"
#include "CPU.h"
#include "timer.h"
#include "AC.h"
#include "interrupt.h"
#include "LSM6DSL.h"
#include "wdt.h"
#include "Version.h"
#include "LCD.h"
#include "bluetooth.h"
#include "RTC.h"
#include "usart.h"
#include "ADC.h"
#include "measurement.h"
#include "button.h"
#include "AC.h"
#include "battery.h"
#include "delay.h"
#include "wdt.h"
#include "bluetooth.h"
#include "NVM.h"
#include "EEPROM.h"
#include "filter.h"
#include "flashlight.h"
#include "common.h"
#include "board_conf.h"
#include "DAC.h"
#include "bm83.h"
#include "main.h"

static uint8_t ADC_val_to_LCD_val(const uint16_t measurement_val, const uint16_t calibration_val);
static void Check_intern_extern_Sensor(void);
static void parameter_init(void);
static void system_init(void);
static void hardware_init(void);
static void show_version_num(void);
static void display_bt_status(void);

LCD_t LCDP;

bool check_bat_lvl = true;
operating_param_t op_param;
floating_mean_val_t floating_mean_val;

#define U32_MAX                     4294967295
#define ADC_CMP_VAL                 1800         /* Upper Limit for measured adc noise value. 
                                                    equals LCD value of 99 */
#define NOISE_SAMPLING_RATE         2000 
#define NOISE_SAMPLING_SIZE         250
#define NOISE_MEAN_SIZE             35 


/*******************************************************************************
@brief          use to impliment a LCD on-off
*******************************************************************************/
// Make all declareation here to devlop a function for LCD on-off
volatile bool Lcd_on_flag = true;
extern bool volatile light_flag;
extern bool volatile light_flag1;

/******************************************************************************/

int main(void) {
    const MEAS_meas_par_t noise_meas_param = { NOISE_SAMPLING_RATE, NOISE_SAMPLING_SIZE, NOISE_MEAN_SIZE };
    uint16_t noise_lvl;
    uint8_t display_value;
    uint8_t tmp;

    LCDP.COM_Mode = 1;

    wdt_set_timeout_period(WDT_TIMEOUT_PERIOD_8KCLK);
    wdt_enable();
    
    system_init();
    hardware_init();
    parameter_init();

/*
TODO:
1. Make a separatly funktions for start/stop/reset LCD-observations timer (where you call start/stop and set to 0 the timer E1)

The code is now running rigth.
Oleg.

*/
    while (1) {

        wdt_reset();
               
//      LCDP.is_z_tilted = LSM6DSL_is_z_tilted();

/*******************************************************************************
            check weather device is accelerated or not
            and make a flage true if acceleraton is detected
            @brief          use to impliment a LCD on-off
*******************************************************************************/
        
        if (LSM6DSL_is_accelerated()) {
          if (!Lcd_on_flag)
            TIM_start_E1();
          Lcd_on_flag = true;
          TCE1.CNT = 0;
        } 
       
        wdt_reset();

/*******************************************************************************
    if acceleration detected then in normal condion and LCD is On
*******************************************************************************/

      if (Lcd_on_flag){               // start if statement
          
          noise_lvl = MEAS_read_val(&noise_meas_param, op_param.Kalibrations_Wert);
          display_value = ADC_val_to_LCD_val(noise_lvl, op_param.Kalibrations_Wert);
          
            if (!op_param.show_min_value) {
                  if (display_value <= op_param.min_val) {
                      op_param.min_val = display_value;
                  }
              tmp = op_param.min_val;
            }
            else {
                display_value = tmp;
                op_param.min_val = LCD_MAX_VAL;
            }

          display_bt_status();

          LCD_Show_All(display_value, BAT_LVL_DO_NOT_REFRESH, FILTER_DO_NOT_REFRESH, KH_DO_NOT_REFRESH);
        
          if (check_bat_lvl) {
            check_bat_lvl = false;
            op_param.bat_lvl = BAT_read_level(op_param.battery_calib_val);
            BAT_show_level(op_param.bat_lvl);
          }
        
/*******************************************************************************
            if LED and back_light is ON previuse then make it  ON again       
*******************************************************************************/
        
          if (light_flag1){
            SET_BIT(FLASHLIGHT_PORT, FLASHLIGHT_PIN) ;
            SET_BIT(LCD_BACKLIGHT_PORT, LCD_BACKLIGHT_BIT);
          }
          // if back_light is ON previuse then make it  ON again
          else if (light_flag){
            SET_BIT(LCD_BACKLIGHT_PORT, LCD_BACKLIGHT_BIT);
          }
                
    }           // end if statement
        
/*******************************************************************************
            if acceleration not detected then in LCD is OFF
*******************************************************************************/
    
        else {
            LCD_turn_off();
//            LCD_show_off();
            TIM_stop_E1();
          
              // back_light  and LED is also OFF if it is on
              if (light_flag1){
                CLR_BIT(FLASHLIGHT_PORT, FLASHLIGHT_PIN) ;
                CLR_BIT(LCD_BACKLIGHT_PORT, LCD_BACKLIGHT_BIT);
              }
              // back_light is OFF if it is ON
              else if (light_flag)
              {     
                CLR_BIT(LCD_BACKLIGHT_PORT, LCD_BACKLIGHT_BIT);
              }
            // Make the timer stop to stop toggal the bit of LCD port 4 and PIN4
            TIM_stop_C1(); 
            
//            TCD1.INTCTRLB = TC_CCAINTLVL_OFF_gc;
        }
        
/******************************************************************************/        
        wdt_reset();
        
        if (op_param.button_left_pushed || BUT_is_left_button_pressed())
            BUT_handle_left_button_click();

        if (op_param.button_right_pushed || BUT_is_right_button_pressed())
            BUT_handle_right_button_click(&op_param);
        
        Check_intern_extern_Sensor();

    }
}

static void system_init(void) {
    CPU_init();
    TIM_init();
    GPIO_init();
    SET_BIT(POWER_ON_PORT, POWER_ON_PIN);
    TIM_start_D1();
    TIM_start_E0();
    INT_init();
    RTC_init();
    LSM6DSL_init();
    DAC_init();
    AC_init();
    ADC_init();
    op_param.filter_select = FIL_init();
}

static void hardware_init(void) {
    ADC_SET_Calibration_BYTE();
    Init_ADC_NF_Signal();
    Init_ADC_bat_lvl();
    TIM_start_E1(); // Start timer
}
/**
 * The function checks the Bluetooth connection status and sets the pairing status accordingly, while
 * also controlling the mute state and displaying relevant information on an LCD screen.
 *
 * @return a variable of type `pairing_status_t`, which indicates whether the device is paired or not.
 */
static void display_bt_status(void) {
    if (op_param.pairing_status == PAIRED) {
        switch (op_param.Mute) {
            case __MUTE_ON:
                LCD_Show_All(0xFF, BAT_LVL_DO_NOT_REFRESH, FILTER_DO_NOT_REFRESH, __KH_on_Mute_on);
                break;
            case __MUTE_OFF:
                LCD_Show_All(0xFF, BAT_LVL_DO_NOT_REFRESH, FILTER_DO_NOT_REFRESH, __KH_on_Mute_off);
                break;
        }
        TIM_stop_C1();
    }
    else {
       LCD_Show_All(0xFF, BAT_LVL_DO_NOT_REFRESH, FILTER_DO_NOT_REFRESH, MUTE_ON_KH_BLINKT);   
    }
}

/****************************************************************************************************
                                 Check_intern_extern_Sensor
Wenn ext Sensor angesteckt dann mit est Sensor messen
*******************************************************************************************************/
static void Check_intern_extern_Sensor(void) {
    amp_select_t amp_sel;

    //...............pr�fe ob ver�nderung
    if ((EXT_SENSOR_DETECTION_PORT & EXT_SENSOR_DETECTION_PIN) == 0)
        amp_sel = AMP_SELECT_EXTERN;
    else
        amp_sel = AMP_SELECT_INTERN;
    if (amp_sel == op_param.amp_sel)
        return;
    //................neu setzen
    op_param.amp_sel = amp_sel;
    if (op_param.amp_sel == AMP_SELECT_EXTERN)
        SET_BIT(EXT_SENSOR_SELECT_PORT, EXT_SENSOR_SELECT_PIN);
    else
        CLR_BIT(EXT_SENSOR_SELECT_PORT, EXT_SENSOR_SELECT_PIN);

}

/**
 * The function initializes various parameters and settings for the device.
 */
static void parameter_init(void) {
    show_version_num();

    if(op_param.Mute == __MUTE_ON){
        BT_toggle_mute();
    }

    op_param.battery_calib_val = bat_lvl_read_calib_offset();


    op_param.pairing_status = NOT_PAIRED;
    bt_start();


    op_param.Kalibrations_Wert = Short_aus_EEPROM(__Kalibration_EEAdr);
    if (op_param.Kalibrations_Wert == 0xFFFF)
        op_param.Kalibrations_Wert = 0;


    op_param.button_left_pushed = false;
    op_param.button_right_pushed = false;

    op_param.min_val = LCD_MAX_VAL;

    floating_mean_val.index = 0;
    
    
    // show last filter setting                                            
    LCD_Show_All(0xFF, BAT_LVL_DO_NOT_REFRESH, op_param.filter_select, MUTE_ON_KH_BLINKT);
    op_param.bat_lvl = BAT_read_level(op_param.battery_calib_val);
    BAT_show_level(op_param.bat_lvl);
    
    Lcd_on_flag = true;
}


/**
 * The function displays the version number on an LCD screen with delays in between each digit.
 */
static void show_version_num(void) {
    LCD_turn_off();
    LCD_Show_All(VERSION_MAJOR, BAT_LVL_DO_NOT_REFRESH, FILTER_DO_NOT_REFRESH, KH_DO_NOT_REFRESH);
    DELAY_wait_1ms_busily(400);
    LCD_turn_off();
    DELAY_wait_1ms_busily(400);
    LCD_Show_All(VERSION_MINOR, BAT_LVL_DO_NOT_REFRESH, FILTER_DO_NOT_REFRESH, KH_DO_NOT_REFRESH);
    DELAY_wait_1ms_busily(400);
    LCD_turn_off();
    DELAY_wait_1ms_busily(400);
    LCD_Show_All(VERSION_QFE, BAT_LVL_DO_NOT_REFRESH, FILTER_DO_NOT_REFRESH, KH_DO_NOT_REFRESH);
    DELAY_wait_1ms_busily(400);
}

/**
*@brief Scales the measured value as a function of the calibration value over the display scale.
*
*@param measurement_val         value measured by adc
*@param calibration_val         ADC measured value offset for masking out ambient noise
*@return                        value between 0 - 99
*/
static uint8_t ADC_val_to_LCD_val(const uint16_t measurement_val, const uint16_t calibration_val) {
    uint16_t rv = measurement_val;
    rv /= (ADC_CMP_VAL - calibration_val) / 100;

    if (rv > 99)
        rv = 99;

    MEAS_push_back(&floating_mean_val, rv);

    rv = MEAS_calculate_floating_mean_val(&floating_mean_val);

    return (uint8_t)rv;
}



void BT_set_connection_status(pairing_status_t ps){
    op_param.pairing_status = ps;
}

void BT_toggle_mute(void){
    if(op_param.Mute == __MUTE_ON){
        op_param.Mute = __MUTE_OFF;
        op_param.show_min_value = false;
        bt_set_mute(__MUTE_OFF);
    }
    else{
        op_param.Mute = __MUTE_ON;
        op_param.show_min_value = true;
        bt_set_mute(__MUTE_ON);
    }
}