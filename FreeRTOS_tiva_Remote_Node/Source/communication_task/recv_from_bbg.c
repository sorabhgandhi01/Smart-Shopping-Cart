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
#include "task.h"

void vRecv_from_bbg_TimerCallback( TimerHandle_t xTimer );

int current_count;
int previous_count;

extern TaskHandle_t xLeft_Motion;
extern TaskHandle_t xStop_Motion;
extern TaskHandle_t xRight_Motion;
extern TaskHandle_t xForward_Motion;
extern TaskHandle_t xBackward_Motion;


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
    TimerHandle_t xTimers_hb = xTimerCreate
                        (
                        "recv_from_bbg_task",
                        pdMS_TO_TICKS(5000),
                        pdTRUE,
                        ( void * ) 0,
                        vRecv_from_bbg_TimerCallback
                        );

        xTimerStart(xTimers_hb, 0);


    for (;;) {
        while (UARTCharsAvail(UART1_BASE)) {
            char c = ROM_UARTCharGet(UART1_BASE);
            UARTprintf("Rec %x\r\n", c);
            if(c == 0x7e)
            {
                current_count++;
            }
            if(c == BBG_FORWARD_MOTION_SIGNAL)
            {
               xTaskNotifyGive(xForward_Motion);
            }
            else if(c == BBG_RIGHT_MOTION_SIGNAL)
            {
               xTaskNotifyGive(xRight_Motion);
            }
            else if(c == BBG_LEFT_MOTION_SIGNAL)
            {
               xTaskNotifyGive(xLeft_Motion);
            }
            else if(c == BBG_BACKWARD_MOTION_SIGNAL)
            {
               xTaskNotifyGive(xBackward_Motion);
            }
            else if(c == BBG_MOTOR_STOP_SIGNAL)
            {
               xTaskNotifyGive(xStop_Motion);
            }
        }
    }
}
