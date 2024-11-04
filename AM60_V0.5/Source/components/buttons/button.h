/**
*@file button.h
*/
#ifndef BUTTON_H
#define BUTTON_H
#include "common.h"

// TODO nur einmal verwenden ABER dafür zwei daten typen erstellen
bool BUT_is_left_button_pressed(void);
bool BUT_is_right_button_pressed(void);
void BUT_handle_left_button_click (void);
void BUT_handle_right_button_click(operating_param_t *const op_param);

#endif // BUTTON_H