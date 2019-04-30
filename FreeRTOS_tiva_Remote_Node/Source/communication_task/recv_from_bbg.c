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
#include "timers.h"

void vRecv_from_bbg_TimerCallback( TimerHandle_t xTimer );

int current_count;
int previous_count;

void vRecv_from_bbg_TimerCallback( TimerHandle_t xTimer )
 {
    if(current_count <= previous_count)
    {
        UARTprintf("Error!!\n\r");

    }
    else
    {
        UARTprintf("Task is alive!\n\r");
    }
    previous_count= current_count;
 }

void recv_from_bbg_task(void *pvParameters)
{


    UARTprintf("***********RECV_FROM_BBG_TASK************\n\r");
//    TimerHandle_t xTimers_hb = xTimerCreate
//                        (
//                        "recv_from_bbg_task",
//                        pdMS_TO_TICKS(5000),
//                        pdTRUE,
//                        ( void * ) 0,
//                        vRecv_from_bbg_TimerCallback
//                        );
//
//        xTimerStart(xTimers_hb, 0);


    for (;;) {

        while (UARTCharsAvail(UART1_BASE)) {
            char c = ROM_UARTCharGet(UART1_BASE);

            UARTprintf("Rec %d\r\n", c);

//            if(c == 0x7e)
//            {
//                current_count++;
//            }
        }

    }
}
