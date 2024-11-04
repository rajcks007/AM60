/**
*@file  NVM.c
*/
#include <ioavr.h>
#include <stdint.h>
#include "NVM.h"


/******************************************************************************
                   Write_to_protected_Register
Model huge -> Pointer 3 BYte
Model near -> Pointer 2 BYte siehe IAR S.141
volatile uint8_t *Adr : Reg 16,17,18 ; LB..HB
uint8_t value : Reg 19
*******************************************************************************/
void Write_to_protected_Register (volatile uint8_t *Adr, uint8_t value)
{
    asm ("ldi r20, 0xD8");  //CCP = 0xD8; S.13 Signature in CCP um Protected Reg f𲠴 Cyclen freizugeben
    asm ("out __?CCP,r20"); /*CCP Configuration Change Protection Register*/

    asm ("movw r30, r16");  // *Adr = in Z  r30=Wert, r31=0;
    asm ("st     Z, r18");  // Wert in Adr 19

}



/*****************************************************************************************************
                          Wait_NVM_Not_busy
Warte bis NVM-Controller nicht mehr besch姴igt ist
*******************************************************************************************************/
void Wait_NVM_Not_busy( void )
{
    while ((NVM.STATUS & NVM_NVMBUSY_bm) == NVM_NVMBUSY_bm);       //NVM Status REG S.28
}

/*****************************************************************************************************
                           NVM_Command_ausfuehren
Der Befehl im NVM-Controller wird ausgef𨲴 durch schreiben des CMDEX Bits im NVM.CTRLA REG S.27
*******************************************************************************************************/
void NVM_Command_ausfuehren( void )
{
    asm("push r30"      "\n\t"  \
        "push r31"      "\n\t"  \
        "push r16"      "\n\t"  \
        "push r18"      "\n\t"  \
        "ldi r30, 0xCB" "\n\t"  \
        "ldi r31, 0x01" "\n\t"  \
        "ldi r16, 0xD8" "\n\t"  \
        "ldi r18, 0x01" "\n\t"  \
        "out 0x34, r16" "\n\t"  \
        "st Z, r18"     "\n\t"  \
        "pop r18"       "\n\t"  \
        "pop r16"       "\n\t"  \
        "pop r31"       "\n\t"  \
        "pop r30"       "\n\t"  \
       );
}


/*****************************************************************************************************
                           Read_Calibrations_Byte
Ein Wert wird aus der Calibrations Reihe gelesen
Liste mit allen Calibrationswerten S. 47
Liste mit den NVM Befehlen S. 369
return Calibrations Wert
*******************************************************************************************************/
uint8_t Read_Calibrations_Byte(uint8_t Calibrations_BYTE_Nr)
{
    uint8_t Help;
    Help = Calibrations_BYTE_Nr;       // Help R17; Calibrations_BYTE_Nr R16 -- sonst meckert Compiler
    asm("ldi r20, 0x02");              // 0x02: Befehl  lese Calibrations Wert
    asm("ldi r31, 0x00");              // Z-Pointer High = 0
    asm("mov r30, r16");               // Z-Pointer Low  = Calibrations_BYTE_Nr
    asm("sts 0x01CA, r20");            // Befehl 0x02 in NVM_CMD
    asm("lpm r17, Z");                 // lpm instruction ausf𨲥n Wert in r17 = Help
    asm("ldi r20, 0x00");              // 0x00: NVM_CMD no operation
    asm("sts 0x01CA, r20");            // Befehl 0x00 in NVM_CMD
    return Help;
}
