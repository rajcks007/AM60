/**
*@file  NVM.h
*/
#ifndef NVM_H
#define NVM_H

#include <stdint.h>
void Write_to_protected_Register (volatile uint8_t *Adr, uint8_t value);
void Wait_NVM_Not_busy( void );
void NVM_Command_ausfuehren( void );
uint8_t Read_Calibrations_Byte(uint8_t Calibrations_BYTE_Nr);

#endif // NVM_H