/**
******************************************************************************
* @file         LSM6DSL.h
* @brief        This file provides code to access GYRO.
* @author       J. Hoerle
* @date         June 2021
******************************************************************************
* @attention
*
* <h2><center>&copy; Copyright (c) 2021 FAST GmbH.
* All rights reserved.</center></h2>
*
******************************************************************************
*/
/* P U B L I C   P R E P R O C E S S O R   I N C L U D E S */

#ifndef     LSM6DSL_H
#define     LSM6DSL_H
#include <stdbool.h>
#include "common.h"
/* P U B L I C   P R E P R O C E S S O R   D E F I N E S */

/* P U B L I C   P R E P R O C E S S O R   M A C R O S */

/* P U B L I C   T Y P E   D E F I N I T I O N S */

/* P U B L I C   F U N C T I O N   P R O T O T Y P E S */
void LSM6DSL_int_handler(void);
void LSM6DSL_test(void);
uint8_t LSM6DSL_init(void);
uint8_t LSM6DSL_is_z_tilted(void);
void LSM6DSL_select_chip(bool b);
void LSM6DSL_int_handler(void);
bool LSM6DSL_is_accelerated(void);

#endif      /* LSM6DSL_H */