/**
******************************************************************************
* @file         Interrupt.c
* @brief        This file provides code to access GYRO.
* @author       J. Hoerle
* @date         October 2022
******************************************************************************
* @attention
*
* <h2><center>&copy; Copyright (c) 2022 FAST GmbH.
* All rights reserved.</center></h2>
*
******************************************************************************/
#include <ioAVR.h>
#include "interrupt.h"
#include "board_conf.h"
#include "common.h"
void INT_init(void){
    PMIC.CTRL = __PMIC_CTRL;                            //Generelle INT Level freigabe
    INT_enable();  
}

void INT_enable(void){
    SET_BIT(SREG,BIT_7);
}
void INT_disable(void){
    CLR_BIT(SREG,BIT_7);
}



