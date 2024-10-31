/*
 * bluetooth.h
 *
 * Created: 05.07.2022 13:01:51
 *  Author: Soletskiy
 */


#ifndef BLUETOOTH_H_
#define BLUETOOTH_H_

#include "common.h"

#define USART_BUF_SIZE  512

     
void bt_start(void);
void show_bt_fehler (void)  ;    //TODO

bt_result_t bt_init(void);
bool bt_is_connected(void);

bt_result_t bt_check_pairing(void);
bt_result_t bt_start_mit_alter_kopplung ( void);
bt_result_t bt_start_mit_paring (void);
void bt_set_mute(const mute_flag_t mute);
void bt_shut_down(void);
#endif /* BLUETOOTH_H_ */