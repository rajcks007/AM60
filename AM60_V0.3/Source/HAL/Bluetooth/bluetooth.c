/*
 * bluetooth.c
 *
 * Created: 05.07.2022 13:02:11
 *  Author: Soletskiy
 */

#include <stdint.h>
#include "gpio.h"
#include "usart.h"
#include "ring_buffer.h"
#include "bm83.h"
#include "bluetooth.h"
#include "board_conf.h"
#include "LCD.h"
#include "button.h"
#include "delay.h"
#include "common.h"
extern operating_param_t op_param;

static bt_mode_t Check_Delete_BT_Pairing(void);



bool bt_is_connected(void) {
    bool rv = BT_P2_6_PORT & BT_P2_6_PIN;
    return rv;
}


/**
 * The function starts MIT pairing using the BM83 module and returns a Bluetooth result.
 *
 * @return The function `bt_start_mit_paring` is returning a variable of type `bt_result_t`, which is
 * the result of calling the function `bm83_start_with_pairing()`.
 */
bt_result_t bt_start_mit_paring(void) {
    return bm83_start_with_pairing();
}

/**
 * The function sets the mute flag for a BM83 device.
 *
 * @param mute is used to indicate whether the audio output should be muted or
 * not.
 */

void bt_set_mute(const mute_flag_t mute) {
    bm83_set_mute(mute);
}


/**
 * The function bt_start checks for existing Bluetooth pairing and starts either a new pairing or
 * normal operation.
 */
void bt_start(void) {
    LCD_Show_All(0xFF, BAT_LVL_DO_NOT_REFRESH, FILTER_DO_NOT_REFRESH, __KH_blinks);
    SET_BIT(PORTB.INT0MASK, BM83_P2_6_PIN); 
    bt_mode_t bt_mode = Check_Delete_BT_Pairing();

    if (bt_mode == BT_MODE_NEW_PAIRING)
        bt_start_mit_paring();
    else {
        bt_start_mit_alter_kopplung();
    }
}

bt_result_t bt_start_mit_alter_kopplung(void) {
    return bm83_start_normal();
}

/****************************************************************************************************
                                 Check_Delete_BT_Pairing
Die aktive Pairingvernբindung wird gel򳣨t
*******************************************************************************************************/
static bt_mode_t Check_Delete_BT_Pairing(void) {
#define COUNT_DOWN      5
    uint8_t Flag1 = 0;
    uint8_t Flag2 = 0;
    uint8_t cnt = 0;
    uint8_t count_down = COUNT_DOWN;

    bt_mode_t Pairing = BT_MODE_NEW_PAIRING;
    bool bt_symbol_blink = false;

    //............... Taste schon wieder losgelassen ?
    for (uint8_t i = 0; i < 5; i++) {
        if (!BUT_is_right_button_pressed())Flag1++;
        DELAY_wait_1ms_busily(20);
    }
    if (Flag1 > 2) {
        op_param.button_left_pushed = false;     //Taste links INT freigeben
        SET_BIT(BUTTON_RIGHT_PORT.INT0MASK, BUTTON_RIGHT_PIN);
        return BT_MODE_OLD_PAIRING;
    }
    //................ lang gedr𣫴 -> Count down 5 - 0 f𲠤el BT pairing

    while ((Flag2 < 5) && (count_down >= 1)) {
        if (BUT_is_right_button_pressed()) {
            Flag2 = 0;
            if (Flag1 < 30)Flag1++;
            if (Flag1 >= 30) {
                Flag1 = 0;
                LCD_Show_All(count_down, BAT_LVL_DO_NOT_REFRESH, FILTER_DO_NOT_REFRESH, KH_DO_NOT_REFRESH);    // count down
                count_down--;
            }
            DELAY_wait_1ms_busily(10);
        }
        else {
            DELAY_wait_1ms_busily(10);    // nicht gedr𣫴
            Flag2++;
        }
    }
    DELAY_wait_1ms_busily(100);

    if (count_down == 0) Pairing = BT_MODE_NEW_PAIRING;
    else Pairing = BT_MODE_OLD_PAIRING;

    cnt = 0;
    while ((cnt < 5) && (Pairing == BT_MODE_NEW_PAIRING))  //......warte bis losgelassen
    {
        LCD_show_BT_pairing(bt_symbol_blink);
        bt_symbol_blink = !bt_symbol_blink;
        DELAY_wait_1ms_busily(120);
        cnt++;
    }

    LCD_show_on();

    //....................INT wieder freigeben
    op_param.button_right_pushed = false;
    SET_BIT(BUTTON_RIGHT_PORT.INT0MASK, BUTTON_RIGHT_PIN);

    if (count_down == 0) return BT_MODE_NEW_PAIRING;
    return Pairing;
}


void bt_shut_down(void){
    bm83_off();
}   

