/**
******************************************************************************
* @file         LSM6DSL.c
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

/* P R E P R O C E S S O R   I N C L U D E S */
#include "LSM6DSL.h"
#include "board_conf.h"
#include "common.h"
#include "delay.h"
#include "twi.h"
#include "timer.h"


/* P R E P R O C E S S O R   D E F I N E S */
#define BAUDRATE                              400000UL        // bis zu 400 kHz



/** I2C Device Address 8 bit format  if SA0=0 -> D5 if SA0=1 -> D7 **/
#define LSM6DSL_I2C_ADD_L                       0xD5U
#define LSM6DSL_I2C_ADD_H                       0xD7U

/** Device Identification (Who am I) **/
#define LSM6DSL_ID                              0x6AU

#define LSM6DSL_FUNC_CFG_ACCESS                 0x01U
#define LSM6DSL_SENSOR_SYNC_TIME_FRAME          0x04U
#define LSM6DSL_SENSOR_SYNC_RES_RATIO           0x05U
#define LSM6DSL_FIFO_CTRL1                      0x06U
#define LSM6DSL_FIFO_CTRL2                      0x07U
#define LSM6DSL_FIFO_CTRL3                      0x08U
#define LSM6DSL_FIFO_CTRL4                      0x09U
#define LSM6DSL_FIFO_CTRL5                      0x0AU
#define LSM6DSL_DRDY_PULSE_CFG_G                0x0BU
#define LSM6DSL_INT1_CTRL                       0x0DU
#define LSM6DSL_INT2_CTRL                       0x0EU
#define LSM6DSL_WHO_AM_I                        0x0FU
#define LSM6DSL_CTRL1_XL                        0x10U
#define LSM6DSL_CTRL2_G                         0x11U
#define LSM6DSL_CTRL3_C                         0x12U
#define LSM6DSL_CTRL4_C                         0x13U
#define LSM6DSL_CTRL5_C                         0x14U
#define LSM6DSL_CTRL6_C                         0x15U
#define LSM6DSL_CTRL7_G                         0x16U
#define LSM6DSL_CTRL8_XL                        0x17U
#define LSM6DSL_CTRL9_XL                        0x18U
#define LSM6DSL_CTRL10_C                        0x19U
#define LSM6DSL_MASTER_CONFIG                   0x1AU
#define LSM6DSL_WAKE_UP_SRC                     0x1BU
#define LSM6DSL_TAP_SRC                         0x1CU
#define LSM6DSL_D6D_SRC                         0x1DU
#define LSM6DSL_STATUS_REG                      0x1EU

#define LSM6DSL_OUT_TEMP_L                      0x20U
#define LSM6DSL_OUT_TEMP_H                      0x21U
#define LSM6DSL_OUTX_L_G                        0x22U
#define LSM6DSL_OUTX_H_G                        0x23U
#define LSM6DSL_OUTY_L_G                        0x24U
#define LSM6DSL_OUTY_H_G                        0x25U
#define LSM6DSL_OUTZ_L_G                        0x26U
#define LSM6DSL_OUTZ_H_G                        0x27U
#define LSM6DSL_OUTX_L_XL                       0x28U
#define LSM6DSL_OUTX_H_XL                       0x29U
#define LSM6DSL_OUTY_L_XL                       0x2AU
#define LSM6DSL_OUTY_H_XL                       0x2BU
#define LSM6DSL_OUTZ_L_XL                       0x2CU
#define LSM6DSL_OUTZ_H_XL                       0x2DU
#define LSM6DSL_SENSORHUB1_REG                  0x2EU

#define LSM6DSL_SENSORHUB2_REG                  0x2FU
#define LSM6DSL_SENSORHUB3_REG                  0x30U
#define LSM6DSL_SENSORHUB4_REG                  0x31U
#define LSM6DSL_SENSORHUB5_REG                  0x32U
#define LSM6DSL_SENSORHUB6_REG                  0x33U
#define LSM6DSL_SENSORHUB7_REG                  0x34U
#define LSM6DSL_SENSORHUB8_REG                  0x35U
#define LSM6DSL_SENSORHUB9_REG                  0x36U
#define LSM6DSL_SENSORHUB10_REG                 0x37U
#define LSM6DSL_SENSORHUB11_REG                 0x38U
#define LSM6DSL_SENSORHUB12_REG                 0x39U
#define LSM6DSL_FIFO_STATUS1                    0x3AU
#define LSM6DSL_FIFO_STATUS2                    0x3BU
#define LSM6DSL_FIFO_STATUS3                    0x3CU

#define LSM6DSL_FIFO_DATA_OUT_L                 0x3EU
#define LSM6DSL_FIFO_DATA_OUT_H                 0x3FU
#define LSM6DSL_TIMESTAMP0_REG                  0x40U
#define LSM6DSL_TIMESTAMP1_REG                  0x41U
#define LSM6DSL_TIMESTAMP2_REG                  0x42U
#define LSM6DSL_STEP_TIMESTAMP_L                0x49U
#define LSM6DSL_STEP_TIMESTAMP_H                0x4AU
#define LSM6DSL_STEP_COUNTER_L                  0x4BU
#define LSM6DSL_STEP_COUNTER_H                  0x4CU

#define LSM6DSL_SENSORHUB13_REG                 0x4DU
#define LSM6DSL_SENSORHUB14_REG                 0x4EU
#define LSM6DSL_SENSORHUB15_REG                 0x4FU
#define LSM6DSL_SENSORHUB16_REG                 0x50U
#define LSM6DSL_SENSORHUB17_REG                 0x51U
#define LSM6DSL_SENSORHUB18_REG                 0x52U
#define LSM6DSL_FUNC_SRC1                       0x53U
#define LSM6DSL_FUNC_SRC2                       0x54U
#define LSM6DSL_WRIST_TILT_IA                   0x55U
#define LSM6DSL_TAP_CFG                         0x58U
#define LSM6DSL_TAP_THS_6D                      0x59U
#define LSM6DSL_INT_DUR2                        0x5AU
#define LSM6DSL_WAKE_UP_THS                     0x5BU
#define LSM6DSL_WAKE_UP_DUR                     0x5CU
#define LSM6DSL_FREE_FALL                       0x5DU
#define LSM6DSL_MD1_CFG                         0x5EU
#define LSM6DSL_MD2_CFG                         0x5FU
#define LSM6DSL_MASTER_CMD_CODE                 0x60U
#define LSM6DSL_SENS_SYNC_SPI_ERROR_CODE        0x61U
#define LSM6DSL_OUT_MAG_RAW_X_L                 0x66U
#define LSM6DSL_OUT_MAG_RAW_X_H                 0x67U
#define LSM6DSL_OUT_MAG_RAW_Y_L                 0x68U
#define LSM6DSL_OUT_MAG_RAW_Y_H                 0x69U
#define LSM6DSL_OUT_MAG_RAW_Z_L                 0x6AU
#define LSM6DSL_OUT_MAG_RAW_Z_H                 0x6BU
#define LSM6DSL_X_OFS_USR                       0x73U
#define LSM6DSL_Y_OFS_USR                       0x74U
#define LSM6DSL_Z_OFS_USR                       0x75U
#define LSM6DSL_SLV0_ADD                        0x02U

#define LSM6DSL_SLV0_SUBADD                     0x03U
#define LSM6DSL_SLAVE0_CONFIG                   0x04U
#define LSM6DSL_SLV1_ADD                        0x05U
#define LSM6DSL_SLV1_SUBADD                     0x06U
#define LSM6DSL_SLAVE1_CONFIG                   0x07U
#define LSM6DSL_SLV2_ADD                        0x08U
#define LSM6DSL_SLV2_SUBADD                     0x09U
#define LSM6DSL_SLAVE2_CONFIG                   0x0AU
#define LSM6DSL_SLV3_ADD                        0x0BU
#define LSM6DSL_SLV3_SUBADD                     0x0CU
#define LSM6DSL_SLAVE3_CONFIG                   0x0DU
#define LSM6DSL_DATAWRITE_SRC_MODE_SUB_SLV0     0x0EU
#define LSM6DSL_CONFIG_PEDO_THS_MIN             0x0FU
#define LSM6DSL_SM_THS                          0x13U
#define LSM6DSL_PEDO_DEB_REG                    0x14U

#define LSM6DSL_STEP_COUNT_DELTA                0x15U
#define LSM6DSL_MAG_SI_XX                       0x24U
#define LSM6DSL_MAG_SI_XY                       0x25U
#define LSM6DSL_MAG_SI_XZ                       0x26U
#define LSM6DSL_MAG_SI_YX                       0x27U
#define LSM6DSL_MAG_SI_YY                       0x28U
#define LSM6DSL_MAG_SI_YZ                       0x29U
#define LSM6DSL_MAG_SI_ZX                       0x2AU
#define LSM6DSL_MAG_SI_ZY                       0x2BU
#define LSM6DSL_MAG_SI_ZZ                       0x2CU
#define LSM6DSL_MAG_OFFX_L                      0x2DU
#define LSM6DSL_MAG_OFFX_H                      0x2EU
#define LSM6DSL_MAG_OFFY_L                      0x2FU
#define LSM6DSL_MAG_OFFY_H                      0x30U
#define LSM6DSL_MAG_OFFZ_L                      0x31U
#define LSM6DSL_MAG_OFFZ_H                      0x32U
#define LSM6DSL_A_WRIST_TILT_LAT                0x50U
#define LSM6DSL_A_WRIST_TILT_THS                0x54U
#define LSM6DSL_A_WRIST_TILT_MASK               0x59U
#define PROPERTY_DISABLE                        0U
#define PROPERTY_ENABLE                         1U
#define TWI_BAUDSETTING                         (TWI_BAUD(CLKsys, BAUDRATE))
#define LSM6DSL_ADDR                            (0xD5 >> 1)



/* P R E P RO C E S S O R   M A C R O S */



/* M O D U L E   I N T E R N   T Y P E   D E F I N I T I O N S */
typedef enum {
    LSM6DSL_XL_ODR_OFF = 0,
    LSM6DSL_XL_ODR_12Hz5 = 1,
    LSM6DSL_XL_ODR_26Hz = 2,
    LSM6DSL_XL_ODR_52Hz = 3,
    LSM6DSL_XL_ODR_104Hz = 4,
    LSM6DSL_XL_ODR_208Hz = 5,
    LSM6DSL_XL_ODR_416Hz = 6,
    LSM6DSL_XL_ODR_833Hz = 7,
    LSM6DSL_XL_ODR_1k66Hz = 8,
    LSM6DSL_XL_ODR_3k33Hz = 9,
    LSM6DSL_XL_ODR_6k66Hz = 10,
    LSM6DSL_XL_ODR_1Hz6 = 11,
    LSM6DSL_XL_ODR_ND = 12,  /* ERROR CODE */
} lsm6dsl_odr_xl_t;

typedef enum {
    LSM6DSL_2g = 0,
    LSM6DSL_16g = 1,
    LSM6DSL_4g = 2,
    LSM6DSL_8g = 3,
    LSM6DSL_XL_FS_ND = 4,  /* ERROR CODE */
} lsm6dsl_fs_xl_t;

typedef struct {
    int16_t   x_tilt;
    int16_t   y_tilt;
    int16_t   z_tilt;

} LSM6DSL_axes_gyro_t;

typedef struct {
    int16_t   x_acc;
    int16_t   y_acc;
    int16_t   z_acc;

} LSM6DSL_axes_acc_t;


typedef enum {
    LSM6DSL_250dps = 0,
    LSM6DSL_125dps = 1,
    LSM6DSL_500dps = 2,
    LSM6DSL_1000dps = 4,
    LSM6DSL_2000dps = 6,
    LSM6DSL_GY_FS_ND = 7,    /* ERROR CODE */
} lsm6dsl_fs_g_t;

typedef enum {
    LSM6DSL_GY_ODR_OFF = 0,
    LSM6DSL_GY_ODR_12Hz5 = 1,
    LSM6DSL_GY_ODR_26Hz = 2,
    LSM6DSL_GY_ODR_52Hz = 3,
    LSM6DSL_GY_ODR_104Hz = 4,
    LSM6DSL_GY_ODR_208Hz = 5,
    LSM6DSL_GY_ODR_416Hz = 6,
    LSM6DSL_GY_ODR_833Hz = 7,
    LSM6DSL_GY_ODR_1k66Hz = 8,
    LSM6DSL_GY_ODR_3k33Hz = 9,
    LSM6DSL_GY_ODR_6k66Hz = 10,
    LSM6DSL_GY_ODR_ND = 11,    /* ERROR CODE */
} lsm6dsl_odr_g_t;

/* G L O B A L   V A R I A B L E S */
static TWI_Master_t g_twi_master;

/* E X T E R N   F U N C T I O N   P R O T O T Y P E S */

/* M O D U L E   I N T E R N   F U N C T I O N   P R O T O T Y P E S */
static uint8_t LSM6DSL_read_write_reg(uint8_t* const p_buf_tx, uint8_t bytes_to_write);

// setter
static uint8_t LSM6DSL_set_auto_incr(uint8_t b_set_auto_incr);
static uint8_t LSM6DSL_set_data_rate_xl(lsm6dsl_odr_xl_t val);
static uint8_t LSM6DSL_set_full_scale_xl(lsm6dsl_fs_xl_t val);
static uint8_t LSM6DSL_set_full_scale_gy(lsm6dsl_fs_g_t val);
static uint8_t LSM6DSL_set_data_rate_gy(lsm6dsl_odr_g_t val);
static uint8_t LSM6DSL_set_block_data_update(uint8_t val);
static uint8_t LSM6DSL_set_sw_reset(uint8_t val);
static uint8_t LSM6DSL_get_axes_acc(LSM6DSL_axes_acc_t* gyro_axes_acc);

// getter
static uint8_t LSM6DSL_get_ID(void);
static uint8_t LSM6DSL_get_gyro_axes_tilt(LSM6DSL_axes_gyro_t* gyro_axes_tilt);
static uint8_t LSM6DSL_get_auto_incr(void);
static uint8_t LSM6DSL_get_data_rate_xl(void);
static uint8_t LSM6DSL_get_full_scale_xl(void);
static uint8_t LSM6DSL_get_data_rate_gy(void);
static uint8_t LSM6DSL_get_full_scale_gy(void);
static uint8_t LSM6DSL_get_block_data_update(void);
static uint16_t get_z_axis_cmp_val(bool b);

/* P U B L I C   F U N C T I O N   I M P L E M E N T A T I O N S */
uint8_t LSM6DSL_init(void) {
    uint8_t rv = 0;    // return value

    TWI_MasterInit(&g_twi_master, &TWI_I2C, TWI_MASTER_INTLVL_HI_gc, TWI_BAUDSETTING);
    LSM6DSL_select_chip(0);

    if (LSM6DSL_get_ID() == LSM6DSL_ID) {
        LSM6DSL_set_sw_reset(true);
        LSM6DSL_set_data_rate_xl(LSM6DSL_XL_ODR_104Hz);
        LSM6DSL_set_full_scale_xl(LSM6DSL_2g);
        LSM6DSL_set_data_rate_gy(LSM6DSL_GY_ODR_104Hz);
        LSM6DSL_set_full_scale_gy(LSM6DSL_2000dps);
        LSM6DSL_set_block_data_update(true);
        rv = OK;         // gyro was found
    }

    return rv;
}

/**
 * This function initializes the LSM6DSL sensor and continuously reads the tilt of the gyro axes.
 */
void LSM6DSL_test(void) {
    LSM6DSL_axes_gyro_t gyro_axes_tilt;

    LSM6DSL_init();

    while (1) {
        LSM6DSL_get_gyro_axes_tilt(&gyro_axes_tilt);
        DELAY_wait_1ms_busily(1000);
    }
}

void LSM6DSL_int_handler(void) {
    TWI_MasterInterruptHandler(&g_twi_master);
}
static uint16_t get_z_axis_cmp_val(bool b) {
#define Z_AXIS_HYSTERESE_1 12000
#define Z_AXIS_HYSTERESE_2 14000

    if (!b) return Z_AXIS_HYSTERESE_2;
    else return Z_AXIS_HYSTERESE_1;
}


bool hysterese_state = false;
uint16_t cmp_val = Z_AXIS_HYSTERESE_1;

uint8_t LSM6DSL_is_z_tilted(void) {
    uint8_t b_is_z_tilted = 0x00;

    LSM6DSL_axes_gyro_t gyro_axes_tilt;

    LSM6DSL_get_gyro_axes_tilt(&gyro_axes_tilt);

    if ((gyro_axes_tilt.z_tilt < cmp_val) && (gyro_axes_tilt.y_tilt < 0)) {
        b_is_z_tilted = 0x01;
        cmp_val = get_z_axis_cmp_val(hysterese_state);
        hysterese_state = !hysterese_state;
    }

    return b_is_z_tilted;
}

bool LSM6DSL_is_accelerated(void) {
    bool is_accelerated = false;

    LSM6DSL_axes_acc_t acc;

    LSM6DSL_get_axes_acc(&acc);

    if ((acc.x_acc > 300) || (acc.x_acc < -300))
        is_accelerated = true;
    if ((acc.y_acc > 300) || (acc.y_acc < -300))
        is_accelerated = true;
    if ((acc.z_acc > 300) || (acc.z_acc < -300))
        is_accelerated = true;

    return is_accelerated;
}






/**
@brief          use to impliment a LCD on-off
*/
/*
void checkAccelX(void) {
    LSM6DSL_axes_acc_t acc;
    LSM6DSL_get_axes_acc(&acc);
    
    if (LSM6DSL_is_accelerated()) {
      Time_newflag = true;
    } else {
        if (startTime == 0) {
            TIM_start_E1(); // Start timer
            startTime = tick();
        } else if ((tick() - startTime) >= TIME_LIMIT) {
            Time_newflag = false;
            TIM_stop_E1();
        }
    }
}
*/
/**
@brief          use to impliment a LCD on-off
*/






/* M O D U L E   I N T E R N   F U N C T I O N   I M P L E M E N T A T I O N S */
static uint8_t LSM6DSL_read_write_reg(uint8_t* const p_buf_tx, uint8_t bytes_to_write) {
    uint8_t rv = 0;

    if (TWI_MasterWriteRead(&g_twi_master, LSM6DSL_ADDR, p_buf_tx, bytes_to_write, 1)) {
        while (!TWI_MasterReady(&g_twi_master));
        rv = g_twi_master.readData[0];
    }

    return rv;
}

// getter
static uint8_t LSM6DSL_get_ID(void) {
    uint8_t rv = 0;
    uint8_t p_buf_tx[] = { LSM6DSL_WHO_AM_I };
    rv = LSM6DSL_read_write_reg(p_buf_tx, 1);
    return rv;
}

static uint8_t LSM6DSL_get_axes_acc(LSM6DSL_axes_acc_t* const gyro_axes_acc) {
    uint8_t rv = 0;
    uint8_t lsB;
    uint8_t msB;
    uint8_t p_buf_tx[] = { LSM6DSL_OUTX_L_G, LSM6DSL_OUTX_H_G, LSM6DSL_OUTY_L_G, LSM6DSL_OUTY_H_G, LSM6DSL_OUTZ_L_G, LSM6DSL_OUTZ_H_G };

    lsB = LSM6DSL_read_write_reg(&p_buf_tx[0], 1);
    msB = LSM6DSL_read_write_reg(&p_buf_tx[1], 1);
    gyro_axes_acc->x_acc = lsB | (msB << 8);

    lsB = LSM6DSL_read_write_reg(&p_buf_tx[2], 1);
    msB = LSM6DSL_read_write_reg(&p_buf_tx[3], 1);
    gyro_axes_acc->y_acc = lsB | (msB << 8);

    lsB = LSM6DSL_read_write_reg(&p_buf_tx[4], 1);
    msB = LSM6DSL_read_write_reg(&p_buf_tx[5], 1);
    gyro_axes_acc->z_acc = lsB | (msB << 8);

    rv = 1;
    return rv;
}

static uint8_t LSM6DSL_get_gyro_axes_tilt(LSM6DSL_axes_gyro_t* gyro_axes_tilt) {
    uint8_t rv = 0;
    uint8_t lsB;
    uint8_t msB;
    uint8_t p_buf_tx[] = { LSM6DSL_OUTX_L_XL, LSM6DSL_OUTX_H_XL, LSM6DSL_OUTY_L_XL, LSM6DSL_OUTY_H_XL, LSM6DSL_OUTZ_L_XL, LSM6DSL_OUTZ_H_XL };

    lsB = LSM6DSL_read_write_reg(&p_buf_tx[0], 1);
    msB = LSM6DSL_read_write_reg(&p_buf_tx[1], 1);
    gyro_axes_tilt->x_tilt = lsB | (msB << 8);

    lsB = LSM6DSL_read_write_reg(&p_buf_tx[2], 1);
    msB = LSM6DSL_read_write_reg(&p_buf_tx[3], 1);
    gyro_axes_tilt->y_tilt = lsB | (msB << 8);

    lsB = LSM6DSL_read_write_reg(&p_buf_tx[4], 1);
    msB = LSM6DSL_read_write_reg(&p_buf_tx[5], 1);
    gyro_axes_tilt->z_tilt = lsB | (msB << 8);

    rv = 1;
    return rv;
}

static uint8_t LSM6DSL_get_auto_incr(void) {
    uint8_t p_buf_tx[] = { LSM6DSL_CTRL3_C };

    return LSM6DSL_read_write_reg(p_buf_tx, 1) & BIT_3;
}

static uint8_t LSM6DSL_get_data_rate_xl(void) {
    uint8_t p_buf_tx[] = { LSM6DSL_CTRL1_XL };

    return LSM6DSL_read_write_reg(p_buf_tx, 1) & (BIT_7 | BIT_6 | BIT_5 | BIT_4);
}

static uint8_t LSM6DSL_get_full_scale_xl(void) {
    uint8_t p_buf_tx[] = { LSM6DSL_CTRL1_XL, };

    return LSM6DSL_read_write_reg(p_buf_tx, 1) & (BIT_3 | BIT_2);
}

static uint8_t LSM6DSL_get_data_rate_gy(void) {
    uint8_t p_buf_tx[] = { LSM6DSL_CTRL2_G };

    return LSM6DSL_read_write_reg(p_buf_tx, 1) & (BIT_7 | BIT_6 | BIT_5 | BIT_4);
}

static uint8_t LSM6DSL_get_full_scale_gy(void) {
    uint8_t p_buf_tx[] = { LSM6DSL_CTRL2_G };

    return LSM6DSL_read_write_reg(p_buf_tx, 1) & (BIT_3 | BIT_2);
}

static uint8_t LSM6DSL_get_block_data_update(void) {
    uint8_t p_buf_tx[] = { LSM6DSL_CTRL3_C };

    return LSM6DSL_read_write_reg(p_buf_tx, 1) & BIT_6;
}

//setter
static uint8_t LSM6DSL_set_auto_incr(uint8_t b_val) {
    uint8_t rv;
    uint8_t p_buf_tx[] = { LSM6DSL_CTRL3_C, b_val << 2 };

    rv = LSM6DSL_read_write_reg(p_buf_tx, 1);
    if (p_buf_tx[1] > 0) p_buf_tx[1] = rv | p_buf_tx[1];
    else p_buf_tx[1] = rv & ~p_buf_tx[1];

    rv = LSM6DSL_read_write_reg(p_buf_tx, 2);
    rv = LSM6DSL_read_write_reg(p_buf_tx, 1);
    return rv;
}

/**
 * The function sets the data rate for the LSM6DSL accelerometer.
 *
 * @param val The input parameter "val" is of type "lsm6dsl_odr_xl_t", which is an enumeration type
 * representing the output data rate (ODR) for the accelerometer in the LSM6DSL sensor. The possible
 * values for this parameter are defined in the enumeration type and correspond to specific
 *
 * @return a uint8_t value, which is the result of the last call to LSM6DSL_read_write_reg().
 */
static uint8_t LSM6DSL_set_data_rate_xl(lsm6dsl_odr_xl_t val) {
    uint8_t rv = 0;
    uint8_t p_buf_tx[] = { LSM6DSL_CTRL1_XL, val << 4 };

    rv = LSM6DSL_read_write_reg(p_buf_tx, 1);
    if (p_buf_tx[1] > 0) p_buf_tx[1] = rv | p_buf_tx[1];
    else p_buf_tx[1] = rv & ~p_buf_tx[1];

    rv = LSM6DSL_read_write_reg(p_buf_tx, 2);       // write reg
    rv = LSM6DSL_read_write_reg(p_buf_tx, 1);

    return rv;
}

static uint8_t LSM6DSL_set_full_scale_xl(lsm6dsl_fs_xl_t val) {
    uint8_t rv = 0;
    uint8_t p_buf_tx[] = { LSM6DSL_CTRL1_XL, val << 2 };

    rv = LSM6DSL_read_write_reg(p_buf_tx, 1);
    if (p_buf_tx[1] > 0) p_buf_tx[1] = rv | p_buf_tx[1];
    else p_buf_tx[1] = rv & ~p_buf_tx[1];

    rv = LSM6DSL_read_write_reg(p_buf_tx, 2);
    rv = LSM6DSL_read_write_reg(p_buf_tx, 1);

    return rv;
}

static uint8_t LSM6DSL_set_data_rate_gy(lsm6dsl_odr_g_t val) {
    uint8_t rv = 0;
    uint8_t p_buf_tx[] = { LSM6DSL_CTRL2_G, val << 4 };

    rv = LSM6DSL_read_write_reg(p_buf_tx, 1);
    if (p_buf_tx[1] > 0) p_buf_tx[1] = rv | p_buf_tx[1];
    else p_buf_tx[1] = rv & ~p_buf_tx[1];

    rv = LSM6DSL_read_write_reg(p_buf_tx, 2);

    return rv;
}

static uint8_t LSM6DSL_set_full_scale_gy(lsm6dsl_fs_g_t val) {
    uint8_t rv = 0;
    uint8_t p_buf_tx[] = { LSM6DSL_CTRL2_G, val << 2 };

    rv = LSM6DSL_read_write_reg(p_buf_tx, 1);
    if (p_buf_tx[1] > 0) p_buf_tx[1] = rv | p_buf_tx[1];
    else p_buf_tx[1] = rv & ~p_buf_tx[1];

    rv = LSM6DSL_read_write_reg(p_buf_tx, 2);

    return rv;
}

static uint8_t LSM6DSL_set_block_data_update(uint8_t b_val) {
    uint8_t rv = 0;
    uint8_t p_buf_tx[] = { LSM6DSL_CTRL3_C, b_val << 6 };

    rv = LSM6DSL_read_write_reg(p_buf_tx, 1);
    if (p_buf_tx[1] > 0) p_buf_tx[1] = rv | p_buf_tx[1];
    else p_buf_tx[1] = rv & ~p_buf_tx[1];

    rv = LSM6DSL_read_write_reg(p_buf_tx, 2);

    return rv;
}

static uint8_t LSM6DSL_set_sw_reset(uint8_t b_val) {
    uint8_t rv = 0;
    uint8_t p_buf_tx[] = { LSM6DSL_CTRL3_C, p_buf_tx[1] };

    rv = LSM6DSL_read_write_reg(p_buf_tx, 1);
    if (p_buf_tx[1] > 0) p_buf_tx[1] = rv | p_buf_tx[1];
    else p_buf_tx[1] = rv & ~p_buf_tx[1];

    rv = LSM6DSL_read_write_reg(p_buf_tx, 2);

    return rv;
}

void LSM6DSL_select_chip(bool b) {
    b ? CLR_BIT(GYRO_CS_PORT, GYRO_CS_PIN) : SET_BIT(GYRO_CS_PORT, GYRO_CS_PIN);
}
