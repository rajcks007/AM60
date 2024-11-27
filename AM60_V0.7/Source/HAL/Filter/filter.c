/**
*@file  filter.c
*/
#include <ioavr.h>
#include "filter.h"
#include "board_conf.h"
#include "common.h"
#include "LCD.h"
#include "EEPROM.h"

void FIL_set_filter_lvl(const filter_t filter_lvl) {
    switch (filter_lvl) {
        case FILTER_OFF:
            CLR_BIT(FILTER_ON_OFF_PORT, FILTER_ON_OFF_MASK);
            LCD_Show_All(0xFF, BAT_LVL_DO_NOT_REFRESH, FILTER_OFF, KH_DO_NOT_REFRESH);
            break;
        case FILTER_LP:
            SET_BIT(FILTER_ON_OFF_PORT, FILTER_ON_OFF_MASK);
            CLR_BIT(FILTER_SELECT_PORT, FILTER_SELECT_MASK);
            LCD_Show_All(0xFF, BAT_LVL_DO_NOT_REFRESH, FILTER_LP, KH_DO_NOT_REFRESH);
            break;

        case FILTER_HP:
            SET_BIT(FILTER_ON_OFF_PORT, FILTER_ON_OFF_MASK);
            SET_BIT(FILTER_SELECT_PORT, FILTER_SELECT_MASK);
            LCD_Show_All(0xFF, BAT_LVL_DO_NOT_REFRESH, FILTER_HP, KH_DO_NOT_REFRESH);
            break;
    }
    Byte_in_EEprom(filter_lvl, __Filter_EEAdr);
}

filter_t FIL_init(void) {
    filter_t filter_lvl = (filter_t)BYTE_aus_EEPROM(__Filter_EEAdr);

    if (filter_lvl >= FILTER_MAX) filter_lvl = FILTER_OFF;
    FIL_set_filter_lvl(filter_lvl);

    return filter_lvl;
}