
#include "RTC.h"
#include <ioavr.h>
#include "board_conf.h"

void RTC_init (void)
{
    OSC.CTRL |= OSC_RC32KEN_bm;

    while(RTC_STATUS & RTC_SYNCBUSY_bm);    //warte bis schreiben erlaubt -- siehe RTC COPM REG
    RTC.PER = __RTC_PER;                    //S.194 Real Time Counter Period REG
    RTC.CNT = 0;
    RTC.COMP = __RTC_COMP;                  //S.194 Real Time Compare REG
    // while(RTC_STATUS&RTC_SYNCBUSY_bm);      //warte bis schreiben erlaubt

    RTC.INTCTRL = __RTC_INTCTRL;            //S.192 Real Time Interrupt Control
    //CLK.RTCCTRL = __RTC_RTCCTRL;            // S.86 RTC Control REG Clock l嶦t
}




/***************************************************************************************
                        XMEGA RTC Period Overflow  -- INTLevel 0
XMEGA RTC setz INT wenn das Period REG Overflow hat; Counter wird automatisch zur𣫧esetzt
 **************************************************************************************/
#pragma vector = RTC_OVF_vect
__interrupt void RTC_PER_OVF( void )
{
}

