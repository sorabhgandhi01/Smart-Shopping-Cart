/*
 * uart.h
 *
 *  Created on: 19-Apr-2019
 *      Author: Sorabh
 */

#ifndef MY_UART_H_
#define MY_UART_H_



void init_TX_serial(void);
void init_RX_serial(void);
void UART_send(char* ptr, int len);

#endif /* MY_UART_H_ */
