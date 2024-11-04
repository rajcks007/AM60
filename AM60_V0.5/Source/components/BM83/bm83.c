#include "bm83.h"
#include <ioavr.h>
#include "gpio.h"
#include "usart.h"
#include "delay.h"
#include "common.h"
#include "board_conf.h"
#include "bin.h"
#include "bluetooth.h"
#include "LCD.h"
#include "wdt.h"
            


uint32_t wait_time_ms;
bool is_pulse_active = false;
uint8_t count_up = 0;



bt_result_t bm83_reset_off(void){
    CLR_BIT(PORTB.DIR, BIT_7);
    
    return BT_RES_OK;
}


bt_result_t bm83_on(void){
    SET_BIT(BM83_PWR_PORT, BM83_PWR_PIN);
    bm83_reset_off();
    bm83_mfb_pulse(BM83_SHORT_DELAY);

    return BT_RES_OK;
}


bt_result_t bm83_set_mute(mute_flag_t mute){
    if (mute == __MUTE_ON){
      SET_BIT(BM83_P3_2_PORT, BM83_P3_2_PIN);
    }
    else{
      CLR_BIT(BM83_P3_2_PORT, BM83_P3_2_PIN);
    }
    return BT_RES_OK;
}


bt_result_t bm83_start_with_pairing(void){
    SET_BIT(BM83_PWR_PORT, BM83_PWR_PIN);
    bm83_reset_off();
    bm83_mfb_pulse(BM83_LONG_DELAY);
    return BT_RES_OK;
}


bt_result_t bm83_start_normal(void){
  bt_result_t res;

  res = bm83_on();
  if (res != BT_RES_OK) return res;

  return res;
}


bt_result_t bm83_off(void){
    return bm83_on();
}


void bm83_mfb_pulse(const uint16_t delay){
    SET_BIT(BM83_PWR_PORT, BM83_PWR_PIN);
    count_up = 0;
    wait_time_ms = delay;
    is_pulse_active = true;
}
