/**
*@file  button.c
*/
#include <ioavr.h>
#include "button.h"
#include <stdint.h>
#include "common.h"
#include "wdt.h"
#include "delay.h"
#include "power.h"
#include "bluetooth.h"
#include "EEPROM.h"
#include "LCD.h"
#include "board_conf.h"
#include "filter.h"
#include "measurement.h"
#include "flashlight.h"

#define SHORT_PRESS                 0      
#define LONG_PRSS_COUNTER           5 
#define TIME_BETWEEN_RIGHT_CLICKS   2

bool BUT_is_left_button_pressed(void){
    if ((BUTTON_LEFT_PORT.IN & BUTTON_LEFT_PIN) == 0) return true;
    else return false;
}

bool BUT_is_right_button_pressed(void){
    if ((BUTTON_RIGHT_PORT.IN & BUTTON_RIGHT_PIN) == 0) return true;
    else return false;
}




void BUT_handle_left_button_click (void ){
    uint8_t Flag1 = 0, Flag2 = 0;
    
    while((Flag1 < 10) && (Flag2 < 50)){
        wdt_reset();
        if(!BUT_is_left_button_pressed())Flag1++;
        else Flag1 = 0;
        Flag2++;
        DELAY_wait_1ms_busily(20);
    }

    if(Flag2 >= 50) 
        PWR_turn_device_off();                                      
}


/****************************************************************************************************
                                 BUT_handle_right_button_click
Die Filter werden getoggelt oder die Lampe on/off oder die Hintergrundbeleuchtung on/off geschaltet
*******************************************************************************************************/
void BUT_handle_right_button_click(operating_param_t *const op_param) {
    uint8_t Flag1 = 0;
    uint8_t Flag2 = 0;
    uint8_t Flag3 = 0;
    uint16_t Kalibrations_Flag = 0;

    //............... Taste schon wieder losgelassen ?
    for (uint8_t i = 0; i < TIME_BETWEEN_RIGHT_CLICKS; i++) {
        if (!BUT_is_right_button_pressed()) {
            Flag1++;
        }
        DELAY_wait_1ms_busily(20);
    }

    if (Flag1 > TIME_BETWEEN_RIGHT_CLICKS) {
        op_param->button_right_pushed = false;
        SET_BIT(BUTTON_RIGHT_PORT.INT0MASK, BUTTON_RIGHT_PIN);
        return;
    }

    while (Flag2 < LONG_PRSS_COUNTER) {
        wdt_reset();
        if (BUT_is_right_button_pressed()) {
            Flag2 = 0;
            if (Flag1 < 50)Flag1++;
            if (Flag1 == 50) {
                op_param->Lampen = LIGHT_switch_lights(op_param->Lampen);
                Flag1 = 25;
                Flag3 = 1;
            }
            Kalibrations_Flag++;
            if (Kalibrations_Flag > 200) {
                op_param->Kalibrations_Wert = MEAS_reset_calibration();      // Two times. For production to put device in box while calibrating.
                op_param->Kalibrations_Wert = MEAS_reset_calibration();
                Short_in_EEprom(op_param->Kalibrations_Wert, __Kalibration_EEAdr);
                op_param->Lampen = LIGHT_switch_lights(op_param->Lampen);
            }
            DELAY_wait_1ms_busily(20);
        }
        else {
            DELAY_wait_1ms_busily(20);
            Flag2++;
        }
    }

    if (Flag3 == SHORT_PRESS) {
        op_param->filter_select++;

        if (op_param->filter_select > FILTER_HP)op_param->filter_select = FILTER_OFF;

        FIL_set_filter_lvl(op_param->filter_select);
    }

    //....................INT wieder freigeben
    op_param->button_right_pushed = false;
    SET_BIT(BUTTON_RIGHT_PORT.INT0MASK, BUTTON_RIGHT_PIN);
}
