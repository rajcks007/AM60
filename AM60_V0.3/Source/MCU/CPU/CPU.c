/**
*@file                  CPU.c
*
*/
#include <ioavr.h>
#include "CPU.h"
#include "common.h"
#include "board_conf.h"
#include "NVM.h"

/*****************************************************************************************************
                                 CPU_init
Alle CPU REG werden gesetzt
*******************************************************************************************************/
void CPU_init (void){
    while ((OSC.STATUS & BIT_0) == 0);        //warte bis int 2 MHz RC OSC l嶦t
    //return;
    OSC.PLLCTRL = __O_PLLCTRL;      /*S.90 PLL Control Register*/
    OSC.XOSCCTRL = __O_XOSCCTRL;    /*S.88 XOSC Control: Extern Crystal Oscilator Control*/
    OSC.CTRL    = __O_CTRL;         /*S.87 Oscillator Control : Reset:Bit0=1: INT 2MHz OSC aktiv*/
    while ((OSC.STATUS & __O_Status) == 0);   //warte bis gew婬te Quelle stabil l嶦t
    Write_to_protected_Register (&CLK.CTRL, __C_CTRL); /*S.84 System Clock Control : Extern Oscillator or Clock*/

    if (OSC.CTRL > 1) CLR_BIT(OSC.CTRL, BIT_0); //int 2MHz RC OSC abschalten wenn gewollt

    Write_to_protected_Register (&CLK.PSCTRL, __C_PSCTRL); /*S.84 System Clock Prescaler 6:2-Prescaler A,1:0-B,C */
    CLK.LOCK    = __C_LOCK;         /*S.86 Clock System Lock: 0-LOCK the CTRL+PSCTRL REGISTER*/
    CLK.RTCCTRL = __C_RTCCTRL;      /*S.86 RTC Control Register: 3:1-Clock Source,0-Clock enable*/

}
