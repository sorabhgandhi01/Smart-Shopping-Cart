/*
 * I2C.h
 *
 *  Created on: Apr 18, 2019
 *      Author: omrah
 */

#ifndef I2C_H_
#define I2C_H_

/* Standard C Library Headers */
#include <stdarg.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>
#include "inc/hw_i2c.h"
#include "inc/hw_memmap.h"
#include "inc/hw_types.h"
#include "inc/hw_gpio.h"
#include "driverlib/i2c.h"
#include "driverlib/sysctl.h"
#include "driverlib/gpio.h"
#include "driverlib/pin_map.h"

#include "gesture_sensor_task.h"


///* Exported Global variables */
//extern uint32_t output_clock_rate_hz;

/* Function Prototypes */

/**
 * @brief Configures I2C communications and initializes registers to defaults
 *
 * @return True if initialized successfully. False otherwise.
 */
void I2C_Init(void);

/**
 * @brief Writes a single byte to the I2C device and specified register
 *
 * @param[in] reg the register in the I2C device to write to
 * @param[in] val the 1-byte value to write to the I2C device
 * @return True if successful write operation. False otherwise.
 */
bool I2C_WriteDataByte(uint8_t reg, uint8_t val);

/**
 * @brief Reads a single byte from the I2C device and specified register
 *
 * @param[in] reg the register to read from
 * @param[out] the value returned from the register
 * @return True if successful read operation. False otherwise.
 */
bool I2C_ReadDataByte(uint8_t reg, uint8_t *val);



int I2C_ReadDataBlock(uint8_t reg, uint8_t *val, unsigned int len);

#endif /* I2C_H_ */
