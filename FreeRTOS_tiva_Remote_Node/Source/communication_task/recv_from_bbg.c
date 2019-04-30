/*
 * recv_from_bbg.c
 *
 *  Created on: 26-Apr-2019
 *      Author: Sorabh
 */

#include "recv_from_bbg.h"
#include "FreeRTOS.h"
#include "queue.h"
#include "helper.h"
#include "semphr.h"
#include "my_uart.h"

void recv_from_bbg_task(void *pvParameters)
{
    UARTprintf("***********RECV_FROM_BBG_TASK************\n\r");

    for (;;) {

        while (UARTCharsAvail(UART1_BASE)) {
            char c = ROM_UARTCharGet(UART1_BASE);
            UARTprintf("Rec %d\r\n", c);
        }

    }
}
