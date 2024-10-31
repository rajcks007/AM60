/**
*@file          AC.c
*
*/
#include <ioavr.h>
#include "board_conf.h"
#include "common.h"
void AC_init(void) {
    if ((AC_A_aktiv != OK) && (AC_B_aktiv != OK))
        return;
}