/**
*@file          filter.h
*/
#ifndef FILTER_H
#define FILTER_H

#include <stdint.h>
#include "common.h"
void FIL_set_filter_lvl (filter_t filter_lvl);

/**
*@brief         Intialises filter.
*@return        Last filter level saved to EEPROM. Returns FILTER_OFF, if value is corrupt.
*/
filter_t FIL_init(void);

#endif // FILTER_H