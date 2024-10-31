/**
*@file  power.c
*/
#include <ioavr.h>
#include <intrinsics.h>
#include "power.h"
#include "common.h"
#include "button.h"
#include "delay.h"
#include "flashlight.h"
#include "board_conf.h"
#include "bluetooth.h"
#include "LCD.h"
#include "bm83.h"
#include "wdt.h"
extern bool is_pulse_active;


/***********************************************************************************************
                            PWR_save_energy
Der Prozessor + Perepherie wird in Power Save gesetzt
kann nur mit INT auf Asyncon Pin2 oder Atmel RTC geweckt werden
************************************************************************************************/
void PWR_save_energy(void){
    
    SLEEP.CTRL |= 0x6;
    SLEEP.CTRL |= 0x1;
    asm ("sleep");                    
    CLR_BIT(SLEEP.CTRL, BIT_0);                                           
    CLR_BIT(SLEEP.CTRL, 0x0E);
}


void PWR_turn_device_off (void){  
    wdt_reset();
    LCD_show_off();
    DELAY_wait_1ms_busily(250);
    
    LCD_turn_off();

    __disable_interrupt();
    while(1) CLR_BIT(POWER_ON_PORT, POWER_ON_PIN);    
}
