/**
*@file          flashlight.c
*
*/
#include <ioavr.h>
#include "flashlight.h"
#include "common.h"
#include "delay.h"
#include "board_conf.h"


lighting_t LIGHT_switch_lights (lighting_t lighting){
    lighting++;
    
    if(lighting >= LIGHTS_MAX) lighting = LIGHTS_OFF;
    
    switch (lighting){
    case LIGHTS_OFF: 
        CLR_BIT(FLASHLIGHT_PORT, FLASHLIGHT_PIN) ;
        CLR_BIT(LCD_BACKLIGHT_PORT, LCD_BACKLIGHT_BIT);
        break;
    case LED_ON_FLASH_ON: 
        SET_BIT(FLASHLIGHT_PORT, FLASHLIGHT_PIN) ;
        SET_BIT(LCD_BACKLIGHT_PORT, LCD_BACKLIGHT_BIT);
        break;
    case LED_ON_FLASH_OFF: 
        CLR_BIT(FLASHLIGHT_PORT, FLASHLIGHT_PIN) ;
        SET_BIT(LCD_BACKLIGHT_PORT, LCD_BACKLIGHT_BIT);
        break;
    }
    DELAY_wait_1ms_busily(50);
    
    return lighting;
}
