/**
******************************************************************************
* @file         LCD.h
* @author       J. Hoerle
******************************************************************************
* @attention
*
* <h2><center>&copy; Copyright (c) 2022 FAST GmbH.
* All rights reserved.</center></h2>
*
******************************************************************************/
#ifndef LCD_H
#define LCD_H

#include "common.h"

#define LCD_MAX_VAL         99      ///< highest value to be displayed

typedef struct {
    uint8_t volatile COM_Mode;                                    
    uint8_t first_digit;                 // left (not tilted), right (tilted)
    uint8_t second_digit;               // right (not tilted), left (tilted)
    bool is_hp_flash_on;                                         
    uint8_t hp_flash_cnt;                                     
    bool is_bat_flash_on;                                         
    uint8_t bat_flash_cnt;                                   
    uint8_t is_z_tilted;                                        ///< indicates if z axis of gyro is tilted and display needs to be flipped
} LCD_t;


void LCD_Show_All (uint8_t Wert, const bat_level_t bat_lvl, const filter_t Filter, const headphones_t KH_Mode);
void Code_an_LCD (const uint8_t left_digit, const uint8_t right_digit);
void LCD_turn_off(void);
void LCD_show_calibration_reset(void);
void LCD_show_on(void);
void LCD_show_off(void);
void LCD_show_BT_pairing(bool b);
void LCD_turn_on(void);
void LCD_toggle_elements(void);
void LCD_show_number(const uint8_t n);
void LCD_show_headphone(const headphones_t hp, const mute_flag_t m);
void LCD_show_battery(const bat_level_t b);
void LCD_show_filter(const filter_t f);


#endif // LCD_H