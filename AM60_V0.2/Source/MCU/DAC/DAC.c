/**
*@file  DAC.c
*/
#include <ioavr.h>
#include "DAC.h"
#include "board_conf.h"
#include "common.h"

void DAC_init(void) {
    if (DAC_B_aktiv != OK) return;
}


void DAC_enable(uint8_t Mode) {
    if ((DAC_B_aktiv == OK) && (Mode == 1))
        SET_BIT(DACB.CTRLA, BIT_0);                    //S.320 S.320 DAC A Control Register A
    else CLR_BIT(DACB.CTRLA, BIT_0);
}
