/*
 * @file        common.h
 */

#ifndef COMMON_H_
#define COMMON_H_

#include <stdint.h>
#include <stdbool.h>



#define Puffer_size 265                                      //Puffergr@e

#define __ADC_CH0     (0)                      // ADC Kanal 0
#define __ADC_CH1     (1)                      // ADC Kanal 1
#define __ADC_CH2     (2)                      // ADC Kanal 2
#define __ADC_CH3     (3)                      // ADC Kanal 3


typedef enum { __MUTE_OFF = 0, __MUTE_ON = 1, MUTE_MAX } mute_flag_t;

typedef enum {
  BT_RES_NOT_OK = 0,
  BT_RES_OK = 1,
  BT_RES_ERROR = 2,
  BT_RES_WRONG_PARAMETER = 3,
  BT_RES_TIMEOUT = 4,
  BT_RES_BUFFER_EMPTY = 5,
  BT_RES_UNKNOW = 0xFF
} bt_result_t;

typedef enum { AMP_SELECT_INTERN = 0, AMP_SELECT_EXTERN }amp_select_t;
typedef enum { FILTER_OFF = 0, FILTER_LP, FILTER_HP, FILTER_MAX, FILTER_DO_NOT_REFRESH = 0xFF }filter_t;
typedef enum { BAT_CMP_0 = 2700, BAT_CMP_25 = 3000, BAT_CMP_50 = 3170, BAT_CMP_75 = 3400, BAT_CMP_100 = 3620 }bat_lvltery_cmp_t;
typedef enum { BAT_LVL_0 = 0, BAT_LVL_25 = 25, BAT_LVL_50 = 50, BAT_LVL_75 = 75, BAT_LVL_100 = 100, BAT_LVL_DO_NOT_REFRESH = 0xFF }bat_level_t;
typedef enum { __KH_off_Mute_off = 0, __KH_on_Mute_off = 1, __KH_on_Mute_on = 2, __KH_blinks = 3, MUTE_ON_KH_BLINKT, KH_DO_NOT_REFRESH = 0xFF }headphones_t;
typedef enum { BT_MODE_OLD_PAIRING = 0, BT_MODE_NEW_PAIRING = 1 } bt_mode_t;
typedef enum { NOT_PAIRED, PAIRED, UNDEFINED }pairing_status_t;
typedef enum { LIGHTS_OFF, LED_ON_FLASH_OFF, LED_OFF_FLASH_ON, LED_ON_FLASH_ON, LIGHTS_MAX }lighting_t;

typedef struct {
  uint16_t            bat_lvl;                              ///< battery voltage level
  uint16_t            battery_calib_val;                    ///< ADC-calibartion value for measuring battery voltage level
    bool button_left_pushed;
    bool button_right_pushed;
  lighting_t             Lampen;
  filter_t            filter_select;
  volatile mute_flag_t         Mute;
  volatile pairing_status_t    pairing_status;
  amp_select_t        amp_sel;
  uint16_t            Kalibrations_Wert;
  bool                show_min_value;
  uint8_t             min_val;                                ///< lowest registered value
} operating_param_t;


#define SET_BIT( SFR, MASK ) ((SFR) |=  (MASK))
#define CLR_BIT( SFR, MASK ) ((SFR) &= ~(MASK))
#define INV_BIT( SFR, MASK ) ((SFR) ^=  (MASK))

#define MEMBER_SIZE(type, member) sizeof(((type *)0)->member)

#define BIT(A) (1<<(A))
#define BIT_0 (0x01)
#define BIT_1 (0x02)
#define BIT_2 (0x04)
#define BIT_3 (0x08)
#define BIT_4 (0x10)
#define BIT_5 (0x20)
#define BIT_6 (0x40)
#define BIT_7 (0x80)
#define BIT_8 (0x0100)
#define BIT_9 (0x0200)
#define BIT_10 (0x0400)
#define BIT_11 (0x0800)
#define BIT_12 (0x1000)
#define BIT_13 (0x2000)
#define BIT_14 (0x4000)
#define BIT_15 (0x8000)

#define NOT_OK (0x0)
#define OK     (0x1)


#endif /* COMMON_H_ */