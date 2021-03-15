#ifndef __I2C_DRIVER_H__
#define __I2C_DRIVER_H__

#include "tm4c123gh6pm.h"
#include <stdint.h>

#define SM		0					/*	Standard Mode	*/
#define FM		1					/* Fast Mode */
#define FMP		2					/* Fast Mode Plus */


#define START			I2C_MCS_START
#define STOP			I2C_MCS_STOP


void I2C_init(uint8_t mode);				/*Initialize I2C1 module */
uint8_t i2c_tpr(uint8_t mode);
void i2c_begin(uint8_t slav_add);
void i2c_write(uint8_t data, uint32_t condition);
void i2c_stop(void);
uint8_t i2c_read(uint8_t condition);


#endif			// __I2C_DRIVER_H__