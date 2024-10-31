#ifndef __BM83_H__
#define __BM83_H__

#include <stdint.h>
#include "common.h"

#define BM83_PWR_PORT           BT_PWR_PORT
#define BM83_PWR_PIN            BT_PWR_PIN
#define BM83_UART_RX_PORT       BT_UART_RX_PORT
#define BM83_UART_RX_PIN        BT_UART_RX_PIN
#define BM83_UART_TX_PORT       BT_UART_TX_PORT
#define BM83_UART_TX_PIN        BT_UART_TX_PIN
#define BM83_UART_RTS_PORT      BT_UART_RTS_PORT
#define BM83_UART_RTS_PIN       BT_UART_RTS_PIN
#define BM83_UART_CTS_PORT      BT_UART_CTS_PORT
#define BM83_UART_CTS_PIN       BT_UART_CTS_PIN
#define BM83_P3_2_PORT          BT_P3_2_PORT    ///< Mutes an existing bluetooth connection
#define BM83_P3_2_PIN           BT_P3_2_PIN
#define BM83_P2_6_PORT          BT_P2_6_PORT    ///< Indicats whether a bt connection is established
#define BM83_P2_6_PIN           BT_P2_6_PIN
#define BM83_RST_N_PORT         BT_RST_N_PORT
#define BM83_RST_N_PIN          BT_RST_N_PIN

#define BM83_SHORT_DELAY            4000       
#define BM83_LONG_DELAY             8000    

void BM83_read_link_status(void);
void BM83_read_paired_device_record(void);
bt_result_t bm83_init_module(void);
bt_result_t bm83_start_normal(void);
bt_result_t bm83_start_with_pairing(void);
bt_result_t bm83_set_mute(mute_flag_t mute);
bt_result_t bm83_off(void);
bt_result_t bm83_on(void);
void bm83_mfb_pulse(const uint16_t delay);
bt_result_t bm83_reset_off(void);

#endif /* __BM83_H__ */