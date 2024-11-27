/**
*@file          EEPROM.c
*
*/
#include <ioavr.h>
#include "board_conf.h"
#include "EEPROM.h"
#include "NVM.h"
/*****************************************************************************************************
                           EEPROM_Erase_Page_Buffer
Der EEprom Buffer wird gel@cht
*******************************************************************************************************/
void EEPROM_Erase_Buffer(void)
{
    Wait_NVM_Not_busy();                                // Wait until NVM is not busy.
    if ((NVM.STATUS & NVM_EELOAD_bm) != 0)              // Erase EEPROM Buffer if necessary. */
    {
        NVM.CMD = NVM_CMD_ERASE_EEPROM_BUFFER_gc;          // NVM Status REG S.28
        NVM_Command_ausfuehren();
    }
}



/*****************************************************************************************************
                                   BYTE aus EEPROM
Ein Byte wird direkt aus dem EEPRom gelesen (ohne Benutzung des Buffers)
Das EEprom beim 128A1 besteht aus 64 Pages a 32 Byte
*******************************************************************************************************/
uint8_t BYTE_aus_EEPROM (uint16_t Adr)
{
    Wait_NVM_Not_busy();                            // Wait until NVM is not busy.
    Adr = Adr & 0x7FF;                              // max 2 K
    NVM.ADDR0 = Adr  & 0xFF;                        // low Adr 0:4 Byte Adr 5:10 Page Adr
    NVM.ADDR1 = Adr >> 8;                           // high Adr
    NVM.ADDR2 = 0x00;
    NVM.CMD = NVM_CMD_READ_EEPROM_gc;               // EEPROM Read command in NVM Controller
    NVM_Command_ausfuehren();
    return NVM.DATA0;
}

/*****************************************************************************************************
                          Byte_in_EEprom
Ein Byte wird ins EEprom geschrieben. - Eine Page in Buffer lesen, Byte in Buffer
schreiben; Das EEprom beim 128A1 besteht aus 64 Pages a 32 Byte
Adr: Direkte Adr im Epprom
*******************************************************************************************************/
void Byte_in_EEprom (uint8_t Wert, uint16_t Adr)
{
    EEPROM_Erase_Buffer();
    Wait_NVM_Not_busy();                            // Wait until NVM is not busy.
    NVM.CMD = NVM_CMD_LOAD_EEPROM_BUFFER_gc;        // NVM Command: Load EEPROM Page Buffer
    Adr = Adr & 0x7FF;                              // max 2 K
    NVM.ADDR0 = Adr  & 0xFF;                        // low Adr 0:4 Byte Adr 5:10 Page Adr
    NVM.ADDR1 = Adr >> 8;                           // high Adr
    NVM.ADDR2 = 0x00;
    NVM.DATA0 = Wert;                               // triggerd lese Page in Buffer + schreibe Byte in Buffer
    NVM.CMD = NVM_CMD_ERASE_WRITE_EEPROM_PAGE_gc;   // NVM Command: Erase & Write EEPROM Page command
    NVM_Command_ausfuehren();
}


/*****************************************************************************************************
                                   Short aus EEPROM
Ein Short wird direkt aus dem EEPRom gelesen (ohne Benutzung des Buffers)
Das EEprom beim 128A1 besteht aus 64 Pages a 32 Byte
*******************************************************************************************************/
uint16_t Short_aus_EEPROM (uint16_t Adr)
{
    uint16_t Help_Short;
    uint8_t *Zeiger;
    Zeiger = (uint8_t *)&Help_Short;                 /*dem Char -Zeiger einmalig Adr der short VAR zuweisen*/
    *(Zeiger + 1) = BYTE_aus_EEPROM (Adr);                 /*HB*/
    *Zeiger = BYTE_aus_EEPROM (Adr + 1);                   /*LB*/
    return Help_Short;
}

/*****************************************************************************************************
                          Short_in_EEprom
Ein Short wird ins EEprom geschrieben. - Eine Page in Buffer lesen, Byte in Buffer
schreiben; Das EEprom beim 128A1 besteht aus 64 Pages a 32 Byte
Adr: Direkte Adr im Epprom
*******************************************************************************************************/
void Short_in_EEprom (uint16_t Wert, uint16_t Adr)
{
    uint8_t *Zeiger;
    Zeiger = (uint8_t *)&Wert;
    Byte_in_EEprom (Zeiger[1], Adr);               // HB ins EEprom
    Byte_in_EEprom (Zeiger[0], Adr + 1);           // LB ins EEprom

}