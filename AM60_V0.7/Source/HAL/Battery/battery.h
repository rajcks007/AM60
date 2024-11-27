/**
*@file          bat_lvltery.h
*/
#ifndef bat_lvlTERY_H
#define bat_lvlTERY_H

#include "common.h"

void BAT_show_level (const uint16_t operating_param_t);
uint16_t BAT_read_level (const uint16_t bat_calib_val);

/**
*@brief         Since ADC is unable to measure bat_lvltery voltage with highest Precision,
*               a calibration offset is measured before activating the corresponding ADC channel.
*
*@return        offset value
*/
uint16_t bat_lvl_read_calib_offset (void);



#endif // bat_lvlTERY_H