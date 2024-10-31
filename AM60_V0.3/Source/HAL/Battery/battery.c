/**
*@file          bat_lvltery.c
*/
#include "battery.h"
#include <stdint.h>
#include <ioavr.h>
#include "board_conf.h"
#include "common.h"
#include "LCD.h"
#include "ADC.h"

void Init_ADC_bat_lvl (void){
    Init_ADC_Kanal (&ADCA, __ADC_CH1, 1);              
}

uint16_t BAT_read_level (const uint16_t bat_calib_val){
    uint16_t battery_lvl;
    SET_BIT(EN_BAT_MEAS_PORT, EN_BAT_MEAS_PIN);                                                 
    
    battery_lvl = ADC_Sample_Single (&ADCA, __ADC_CH1, 10, 20); 
    
//    if(bat_calib_val < battery_lvl) battery_lvl -= bat_calib_val;
//    else battery_lvl = 0;
    

    CLR_BIT(EN_BAT_MEAS_PORT, EN_BAT_MEAS_PIN);                                                

    return battery_lvl;
}


void BAT_show_level (const uint16_t val){

      if(val > BAT_CMP_100) 
          LCD_Show_All (0xFF, BAT_LVL_100, FILTER_DO_NOT_REFRESH, KH_DO_NOT_REFRESH);
      else if(val > BAT_CMP_75) 
          LCD_Show_All (0xFF, BAT_LVL_75, FILTER_DO_NOT_REFRESH, KH_DO_NOT_REFRESH);
      else if(val > BAT_CMP_50)
          LCD_Show_All (0xFF, BAT_LVL_50, FILTER_DO_NOT_REFRESH, KH_DO_NOT_REFRESH);
      else if(val > BAT_CMP_25)
          LCD_Show_All (0xFF, BAT_LVL_25, FILTER_DO_NOT_REFRESH, KH_DO_NOT_REFRESH);
      else
          LCD_Show_All (0xFF, BAT_LVL_0, FILTER_DO_NOT_REFRESH, KH_DO_NOT_REFRESH);
}


uint16_t bat_lvl_read_calib_offset (void){
    uint16_t calibration_value;
    calibration_value = ADC_Sample_Single (&ADCA, __ADC_CH1, 10, 20); 
    return calibration_value;
}
