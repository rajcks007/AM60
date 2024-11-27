/**
******************************************************************************
* öfile         LCD.c
* öbrief        This file provides code to access 7 segment LCD.
* öauthor       J. Hoerle
* ödate         October 2022
******************************************************************************
* öattention
*
* <h2><center>&copy; Copyright (c) 2022 FAST GmbH.
* All rights reserved.</center></h2>
*
******************************************************************************/

#pragma language=extended
#include <ioavr.h>                      
#include "board_conf.h"               
#include <math.h>
#include "LCD.h"
#include "common.h"
#include "button.h"
#include "delay.h"
#include "timer.h"

#define LCD_HEADPHONE_FLASH_PERIODE (64)
#define LCD_BAT_FLASH_PERIODE (64)

static void LCD_show_BAT_LVL_100(void);
static void LCD_show_BAT_LVL_75(void);
static void LCD_show_BAT_LVL_50(void);
static void LCD_show_BAT_LVL_25(void);
static void LCD_show_BAT_LVL_0(void);
static void LCD_set_headphones(const headphones_t);
static void LCD_clear_right_digit(void);
static void LCD_clear_left_digit(void);

extern LCD_t LCDP;


__flash uint8_t __ZL[10] = { 0x7E, 0x0C, 0xB6, 0x9E, 0xCC, 0xDA, 0xFA, 0x4E, 0xFE, 0xDE };
__flash uint8_t __ZR[10] = { 0x7E, 0x0C, 0xB6, 0x9E, 0xCC, 0xDA, 0xFA, 0x4E, 0xFE, 0xDE };
__flash uint8_t inverted_digits[10] = {
    0x7E,  // 0 := Segments ABCDEF
    0x60,  // 1 := Segments EF
    0xB6,  // 2 := Segments ABDEG
    0xF2,  // 3 := Segments ADEFG
    0xE8,  // 4 := Segments CEFG
    0xDA,  // 5 := Segments ACDFG
    0xDE,  // 6 := Segments ABCDFG
    0x70,  // 7 := Segments DEF
    0xFE,  // 8 := Segments ABCDEFG
    0xFA   // 9 := Segments ACDEFG

};


void LCD_Show_All(uint8_t Zahl, const bat_level_t bat_lvl, const filter_t Filter, const headphones_t KH_Mode) {
    uint8_t Ziffer_links;
    uint8_t Ziffer_rechts;

    while (LCDP.COM_Mode == 0);
    while (LCDP.COM_Mode == 1);

    //...............Zahl setzen
    if ((Zahl < 0xFF) && (Zahl > LCD_MAX_VAL)) Zahl = LCD_MAX_VAL;
    if (Zahl < 0xFF) {
        //...............Ziffer links setzen
        Ziffer_links = Zahl / 10;
        Ziffer_rechts = Zahl % 10;

        if (LCDP.is_z_tilted) {                                // inverted view, left digit
            LCDP.second_digit = inverted_digits[Ziffer_links];
            LCD_clear_right_digit();
            SET_BIT(PORTF.OUT, LCDP.second_digit);                      //PORT F set left digit
        }
        else {
            LCDP.first_digit = __ZL[Ziffer_links];                //TODO Generisch machen
            LCD_clear_left_digit();
            SET_BIT(PORTE.OUT, LCDP.first_digit);                          //PORT E Ziffer links setzen
        }
        //...............Ziffer rechts setzen
        if (LCDP.is_z_tilted) {                                // inverted view, right digit
            LCDP.first_digit = inverted_digits[Ziffer_rechts];
            LCD_clear_left_digit();
            SET_BIT(PORTE.OUT, LCDP.first_digit);                      // PORT E set right digit
        }
        else {
            LCDP.second_digit = __ZR[Ziffer_rechts];               // TODO in eigene funktion
            LCD_clear_right_digit();
            SET_BIT(PORTF.OUT, LCDP.second_digit);                      //PORT F Ziffer rechts setzen
        }
    }
    //...............bat_lvl setzen
    if (bat_lvl < 0xFF) {
        if (bat_lvl == BAT_LVL_0)LCD_show_BAT_LVL_0();
        if (bat_lvl == BAT_LVL_25)LCD_show_BAT_LVL_25();
        if (bat_lvl == BAT_LVL_50)LCD_show_BAT_LVL_50();
        if (bat_lvl == BAT_LVL_75)LCD_show_BAT_LVL_75();
        if (bat_lvl == BAT_LVL_100)LCD_show_BAT_LVL_100();

    }
    //...............Filter setzen
    if (Filter < 0xFF) {
        CLR_BIT(LCD_T1_PORT, LCD_T1_PIN);
        CLR_BIT(LCD_T2_PORT, LCD_T2_PIN);

        if (Filter == FILTER_LP) SET_BIT(LCD_T1_PORT, LCD_T1_PIN);
        if (Filter == FILTER_HP) SET_BIT(LCD_T2_PORT, LCD_T2_PIN);

    }
    //...............Kopfh@er setzen
    if (KH_Mode < 0xFF) {
        LCD_set_headphones(KH_Mode);

        if ((KH_Mode & 0x10) > 0) LCDP.is_hp_flash_on = 1;
        else LCDP.is_hp_flash_on = 0;
    }
}

void LCD_show_calibration_reset(void) {
    //TODO
}

void LCD_show_BT_pairing(bool b) {
    b ? Code_an_LCD(0xC6, 0xB8) : Code_an_LCD(0xB8, 0xC6);
}

void LCD_show_on(void) {
    Code_an_LCD(0xB8, 0xA8);
}
void LCD_show_off(void) {
    Code_an_LCD(0x7E, 0xE2);
}


void Code_an_LCD(const uint8_t left_digit, const uint8_t right_digit) {
    while (LCDP.COM_Mode == 0);
    while (LCDP.COM_Mode == 1);

    CLR_BIT(LCDP.first_digit, 0xFE);
    SET_BIT(LCDP.first_digit, left_digit);
    CLR_BIT(PORTE.OUT, 0xFE);
    SET_BIT(PORTE.OUT, LCDP.first_digit);

    CLR_BIT(LCDP.second_digit, 0xFE);
    SET_BIT(LCDP.second_digit, right_digit);
    CLR_BIT(PORTF.OUT, 0xFE);
    SET_BIT(PORTF.OUT, LCDP.second_digit);
}

void LCD_turn_on(void) {
    Code_an_LCD(0xFE, 0xFE);

    SET_BIT(LCD_B0_PORT, LCD_B0_PIN);
    SET_BIT(LCD_B1_PORT, LCD_B1_PIN);
    SET_BIT(LCD_B2_PORT, LCD_B2_PIN);
    SET_BIT(LCD_B3_PORT, LCD_B3_PIN);
    SET_BIT(LCD_B4_PORT, LCD_B4_PIN);

    SET_BIT(LCD_T1_PORT, LCD_T1_PIN);
    SET_BIT(LCD_T2_PORT, LCD_T2_PIN);
    SET_BIT(LCD_T3_PORT, LCD_T3_PIN);
    SET_BIT(LCD_T4_PORT, LCD_T4_PIN);
}

void LCD_turn_off(void) {
    Code_an_LCD(0x00, 0x00);

    CLR_BIT(LCD_B0_PORT, LCD_B0_PIN);
    CLR_BIT(LCD_B1_PORT, LCD_B1_PIN);
    CLR_BIT(LCD_B2_PORT, LCD_B2_PIN);
    CLR_BIT(LCD_B3_PORT, LCD_B3_PIN);
    CLR_BIT(LCD_B4_PORT, LCD_B4_PIN);

    CLR_BIT(LCD_T1_PORT, LCD_T1_PIN);
    CLR_BIT(LCD_T2_PORT, LCD_T2_PIN);
    CLR_BIT(LCD_T3_PORT, LCD_T3_PIN);
    CLR_BIT(LCD_T4_PORT, LCD_T4_PIN);
}

static void LCD_show_BAT_LVL_100(void) {
    SET_BIT(LCD_B0_PORT, LCD_B0_PIN);
    SET_BIT(LCD_B1_PORT, LCD_B1_PIN);
    SET_BIT(LCD_B2_PORT, LCD_B2_PIN);
    SET_BIT(LCD_B3_PORT, LCD_B3_PIN);
    SET_BIT(LCD_B4_PORT, LCD_B4_PIN);
}
static void LCD_show_BAT_LVL_75(void) {
    SET_BIT(LCD_B0_PORT, LCD_B0_PIN);
    SET_BIT(LCD_B1_PORT, LCD_B1_PIN);
    SET_BIT(LCD_B2_PORT, LCD_B2_PIN);
    SET_BIT(LCD_B3_PORT, LCD_B3_PIN);
    CLR_BIT(LCD_B4_PORT, LCD_B4_PIN);
}
static void LCD_show_BAT_LVL_50(void) {
    SET_BIT(LCD_B0_PORT, LCD_B0_PIN);
    SET_BIT(LCD_B1_PORT, LCD_B1_PIN);
    SET_BIT(LCD_B2_PORT, LCD_B2_PIN);
    CLR_BIT(LCD_B3_PORT, LCD_B3_PIN);
    CLR_BIT(LCD_B4_PORT, LCD_B4_PIN);
}
static void LCD_show_BAT_LVL_25(void) {
    SET_BIT(LCD_B0_PORT, LCD_B0_PIN);
    SET_BIT(LCD_B1_PORT, LCD_B1_PIN);
    CLR_BIT(LCD_B2_PORT, LCD_B2_PIN);
    CLR_BIT(LCD_B3_PORT, LCD_B3_PIN);
    CLR_BIT(LCD_B4_PORT, LCD_B4_PIN);
}
static void LCD_show_BAT_LVL_0(void) {
    SET_BIT(LCD_B0_PORT, LCD_B0_PIN);
    CLR_BIT(LCD_B1_PORT, LCD_B1_PIN);
    CLR_BIT(LCD_B2_PORT, LCD_B2_PIN);
    CLR_BIT(LCD_B3_PORT, LCD_B3_PIN);
    CLR_BIT(LCD_B4_PORT, LCD_B4_PIN);
}

static void LCD_set_headphones(const headphones_t hp) {
    CLR_BIT(LCD_T3_PORT, LCD_T3_PIN);

    if (hp == __KH_on_Mute_off) {
        SET_BIT(LCD_T4_PORT, LCD_T4_PIN);
    }
    if (hp == __KH_on_Mute_on) {
        SET_BIT(LCD_T4_PORT, LCD_T4_PIN);
        SET_BIT(LCD_T3_PORT, LCD_T3_PIN);
    }
    if (hp == MUTE_ON_KH_BLINKT) {
        SET_BIT(LCD_T3_PORT, LCD_T3_PIN);
        TIM_start_C1();
    }
}

static void LCD_clear_left_digit(void) {
    CLR_BIT(LCD_1A_PORT, LCD_1A_PIN);
    CLR_BIT(LCD_1B_PORT, LCD_1B_PIN);
    CLR_BIT(LCD_1C_PORT, LCD_1C_PIN);
    CLR_BIT(LCD_1D_PORT, LCD_1D_PIN);
    CLR_BIT(LCD_1E_PORT, LCD_1E_PIN);
    CLR_BIT(LCD_1F_PORT, LCD_1F_PIN);
    CLR_BIT(LCD_1G_PORT, LCD_1G_PIN);
}

static void LCD_clear_right_digit(void) {
    CLR_BIT(LCD_2A_PORT, LCD_2A_PIN);
    CLR_BIT(LCD_2B_PORT, LCD_2B_PIN);
    CLR_BIT(LCD_2C_PORT, LCD_2C_PIN);
    CLR_BIT(LCD_2D_PORT, LCD_2D_PIN);
    CLR_BIT(LCD_2E_PORT, LCD_2E_PIN);
    CLR_BIT(LCD_2F_PORT, LCD_2F_PIN);
    CLR_BIT(LCD_2G_PORT, LCD_2G_PIN);
}

void LCD_toggle_elements(void) {
    if (LCDP.COM_Mode == 1) LCDP.COM_Mode = 0;
    else LCDP.COM_Mode = 1;

    INV_BIT(LCD_COMM_PORT, LCD_COMM_PIN);

    INV_BIT(LCD_1A_PORT, LCD_1A_PIN);
    INV_BIT(LCD_1B_PORT, LCD_1B_PIN);
    INV_BIT(LCD_1C_PORT, LCD_1C_PIN);
    INV_BIT(LCD_1D_PORT, LCD_1D_PIN);
    INV_BIT(LCD_1E_PORT, LCD_1E_PIN);
    INV_BIT(LCD_1F_PORT, LCD_1F_PIN);
    INV_BIT(LCD_1G_PORT, LCD_1G_PIN);

    INV_BIT(LCD_2A_PORT, LCD_2A_PIN);
    INV_BIT(LCD_2B_PORT, LCD_2B_PIN);
    INV_BIT(LCD_2C_PORT, LCD_2C_PIN);
    INV_BIT(LCD_2D_PORT, LCD_2D_PIN);
    INV_BIT(LCD_2E_PORT, LCD_2E_PIN);
    INV_BIT(LCD_2F_PORT, LCD_2F_PIN);
    INV_BIT(LCD_2G_PORT, LCD_2G_PIN);

    INV_BIT(LCD_B0_PORT, LCD_B0_PIN);
    INV_BIT(LCD_B1_PORT, LCD_B1_PIN);
    INV_BIT(LCD_B2_PORT, LCD_B2_PIN);
    INV_BIT(LCD_B3_PORT, LCD_B3_PIN);
    INV_BIT(LCD_B4_PORT, LCD_B4_PIN);

    INV_BIT(LCD_T1_PORT, LCD_T1_PIN);
    INV_BIT(LCD_T2_PORT, LCD_T2_PIN);
    INV_BIT(LCD_T3_PORT, LCD_T3_PIN);
    INV_BIT(LCD_T4_PORT, LCD_T4_PIN);

    if (LCDP.is_hp_flash_on) {
        LCDP.hp_flash_cnt++;
        if (LCDP.hp_flash_cnt > LCD_HEADPHONE_FLASH_PERIODE) {
            LCDP.hp_flash_cnt = 0;
            INV_BIT(LCD_T3_PORT, LCD_T3_PIN);
            INV_BIT(LCD_T4_PORT, LCD_T4_PIN);
        }
    }
    if (LCDP.is_bat_flash_on) {
        LCDP.bat_flash_cnt++;
        if (LCDP.bat_flash_cnt > LCD_BAT_FLASH_PERIODE) {
            LCDP.bat_flash_cnt = 0;
            INV_BIT(LCD_B0_PORT, LCD_B0_PIN);
        }
    }
}