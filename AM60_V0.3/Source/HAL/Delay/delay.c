
/**
*@file  delay.c
*/
#include <ioavr.h>
#include "delay.h"
#include "common.h"
#include "board_conf.h"

void DELAY_wait_10us_busily (uint16_t Anzahl){
    TCC0.CTRLA = __TC0_CTRLA;              
    
    for (uint16_t i = 0; i < Anzahl; i++)    {
        TCC0.CNT = 0;
        while(TCC0.CNT < __TC0_1_usec);         
    }

    TCC0.CTRLA &= ~0x0f;                     
            
}

void DELAY_wait_1ms_busily (uint16_t Anzahl){
    TCC0.CTRLA = __TC0_CTRLA;                

    for (uint16_t i = 0; i < Anzahl; i++)    {
        TCC0.CNT = 0;
        while(TCC0.CNT < __TC0_1_msec);         
    }

    TCC0.CTRLA &= ~0x0f;     
}


