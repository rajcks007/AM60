/**
*@file          EEPROM.h
*
*/

#ifndef EEPROM_H
#define EEPROM_H
#include <stdint.h>
void Short_in_EEprom (uint16_t Wert, uint16_t Adr);
uint16_t Short_aus_EEPROM (uint16_t Adr);
void Byte_in_EEprom (uint8_t Wert, uint16_t Adr);
uint8_t BYTE_aus_EEPROM (uint16_t Adr);
void EEPROM_Erase_Buffer(void);

#endif // EEPROM_H