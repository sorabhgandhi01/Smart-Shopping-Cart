/*
 * uart.h
 *
 *  Created on: 19-Apr-2019
 *      Author: Sorabh
 */

#ifndef MY_UART_H_
#define MY_UART_H_

#include <stdbool.h>
#include <stdint.h>

#include "driverlib/sysctl.h"
#include "driverlib/debug.h"
#include "driverlib/rom.h"
#include "driverlib/rom_map.h"
#include "driverlib/sysctl.h"
#include "driverlib/pin_map.h"
#include "driverlib/gpio.h"
#include "driverlib/interrupt.h"
#include "driverlib/uart.h"

#include "inc/hw_memmap.h"
#include "inc/hw_types.h"
#include "inc/hw_ints.h"

#include "utils/uartstdio.h"

void init_TX_serial(void);
void init_RX_serial(void);
void UART_send(char* ptr, int len);

#endif /* MY_UART_H_ */
