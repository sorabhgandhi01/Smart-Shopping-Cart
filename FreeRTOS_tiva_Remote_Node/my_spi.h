/*
 * my_spi.h
 *
 *  Created on: 14-Apr-2019
 *      Author: Sorabh
 */

#ifndef MY_SPI_H_
#define MY_SPI_H_

#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h>

#include "inc/hw_memmap.h"

#include "driverlib/pin_map.h"
#include "driverlib/rom_map.h"
#include "driverlib/sysctl.h"
#include "driverlib/gpio.h"
#include "driverlib/ssi.h"
#include "driverlib/debug.h"


void SPI_enable(uint32_t SPI_port);
void SPI_disable(uint32_t SPI_port, uint32_t SPI_clock);

void SPI_Pin_Configure(uint32_t clk, uint32_t ss, uint32_t rx, uint32_t tx);
void SPI_Pin_Init(uint32_t SPI_port);


void SPI_Clock_Init(uint32_t SPI_port, uint32_t SPI_clock, uint32_t sysclock);
void SPI_Clock_deinit(uint32_t SPI_clock);

void SPI_Blocking_write_byte(uint32_t SPI_port, uint8_t data);
void SPI_Blocking_read_byte(uint32_t SPI_port, uint8_t *data);

void SPI_NonBlocking_write_byte(uint32_t SPI_port, uint8_t data);
void SPI_NonBlocking_read_byte(uint32_t SPI_port, uint8_t *data);

void SPI_Blocking_write_bytes(uint32_t SPI_port, uint8_t *data, size_t length);
//void SPI_Blocking_read_bytes(uint32_t SPI_port, uint8_t *data, size_t length);

//void SPI_clear_pending_RxTransaction(uint32_t SPI_port);
void SPI_clear_pending_TxTransaction(uint32_t SPI_port);


#endif /* MY_SPI_H_ */
