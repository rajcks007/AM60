/* This file has been prepared for Doxygen automatic documentation generation.*/
/*! \file *********************************************************************
 *
 * \brief  XMEGA TWI master driver header file.
 *
 *      This file contains the function prototypes and enumerator definitions
 *      for various configuration parameters for the XMEGA TWI master driver.
 *
 *      The driver is not intended for size and/or speed critical code, since
 *      most functions are just a few lines of code, and the function call
 *      overhead would decrease code performance. The driver is intended for
 *      rapid prototyping and documentation purposes for getting started with
 *      the XMEGA TWI master module.
 *
 *      For size and/or speed critical code, it is recommended to copy the
 *      function contents directly into your application instead of making
 *      a function call.
 *
 * \par Application note:
 *      AVR1308: Using the XMEGA TWI
 *
 * \author
 *      Atmel Corporation: http://www.atmel.com \n
 *      Support email: avr@atmel.com
 *
 * $Revision: 1569 $
 * $Date: 2008-04-22 13:03:43 +0200 (ti, 22 apr 2008) $  \n
 *
 * Copyright (c) 2008, Atmel Corporation All rights reserved.
 *
 *****************************************************************************/
#ifndef TWI_MASTER_DRIVER_H
#define TWI_MASTER_DRIVER_H

#include <ioAVR.h>
#include <stdbool.h>

/*! Baud register setting calculation. Formula described in datasheet. */
#define TWI_BAUD(F_SYS, F_TWI) ((F_SYS / (2 * F_TWI)) - 5)


/*! Transaction status defines. */
#define TWIM_STATUS_READY              0
#define TWIM_STATUS_BUSY               1


/*! Transaction result enumeration. */
typedef enum TWIM_RESULT_enum {
	TWIM_RESULT_UNKNOWN          = (0x00<<0),
	TWIM_RESULT_OK               = (0x01<<0),
	TWIM_RESULT_BUFFER_OVERFLOW  = (0x02<<0),
	TWIM_RESULT_ARBITRATION_LOST = (0x03<<0),
	TWIM_RESULT_BUS_ERROR        = (0x04<<0),
	TWIM_RESULT_NACK_RECEIVED    = (0x05<<0),
	TWIM_RESULT_FAIL             = (0x06<<0),
} TWIM_RESULT_t;

/*! Buffer size defines */
#define TWIM_WRITE_BUFFER_SIZE         8
#define TWIM_READ_BUFFER_SIZE          8


/*! \brief TWI master driver struct
 *
 *  TWI master struct. Holds pointer to TWI module,
 *  buffers and necessary varibles.
 */
typedef struct TWI_Master 
{
	TWI_t *interface;                                          /*!< Pointer to what interface to use */
	volatile uint8_t address;                            /*!< Slave address */
	volatile uint8_t writeData[TWIM_WRITE_BUFFER_SIZE];  /*!< Data to write */
	volatile uint8_t readData[TWIM_READ_BUFFER_SIZE];    /*!< Read data */
	volatile uint8_t bytesToWrite;                       /*!< Number of bytes to write */
	volatile uint8_t bytesToRead;                        /*!< Number of bytes to read */
	volatile uint8_t bytesWritten;                       /*!< Number of bytes written */
	volatile uint8_t bytesRead;                          /*!< Number of bytes read */
	volatile uint8_t status;                             /*!< Status of transaction */
	volatile uint8_t result;                             /*!< Result of transaction */
} TWI_Master_t;



void TWI_MasterInit(TWI_Master_t *twi,
                    TWI_t *module,
                    TWI_MASTER_INTLVL_t intLevel,
                    uint8_t baudRateRegisterSetting);
TWI_MASTER_BUSSTATE_t TWI_MasterState(TWI_Master_t *twi);
bool TWI_MasterReady(TWI_Master_t *twi);
bool TWI_MasterWrite(TWI_Master_t *twi,
                     uint8_t address,
                     uint8_t * writeData,
                     uint8_t bytesToWrite);
bool TWI_MasterRead(TWI_Master_t *twi,
                    uint8_t address,
                    uint8_t bytesToRead);
bool TWI_MasterWriteRead(TWI_Master_t *twi,
                         uint8_t address,
                         uint8_t *writeData,
                         uint8_t bytesToWrite,
                         uint8_t bytesToRead);
void TWI_MasterInterruptHandler(TWI_Master_t *twi);
void TWI_MasterArbitrationLostBusErrorHandler(TWI_Master_t *twi);
void TWI_MasterWriteHandler(TWI_Master_t *twi);
void TWI_MasterReadHandler(TWI_Master_t *twi);
void TWI_MasterTransactionFinished(TWI_Master_t *twi, uint8_t result);
void TWI_MasterWaitForReady(TWI_Master_t *twi);

/*! TWI master interrupt service routine.
 *
 *  Interrupt service routine for the TWI master. Copy the needed vectors
 *  into your code.
 *
    ISR(TWIC_TWIM_vect)
    {
      TWI_MasterInterruptHandler(&twiMaster);
    }

    for IAR:
    #pragma vector = TWIC_TWIM_vect
    __interrupt void Interuppt_TWIM_C( void )
    {
      TWI_MasterInterruptHandler(&twiMaster);
    }

*
 */

#endif /* TWI_MASTER_DRIVER_H */
