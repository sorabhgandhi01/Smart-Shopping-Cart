/*
 * recv_from_bbg.c
 *
 *  Created on: 26-Apr-2019
 *      Author: Sorabh
 */

#include <stdbool.h>
#include "recv_from_bbg.h"
#include "FreeRTOS.h"
#include "queue.h"
#include "helper.h"
#include "semphr.h"
#include "my_uart.h"
#include "timers.h"
#include "task.h"
#include "motor_control.h"
#include "Lcd_display.h"

void vRecv_from_bbg_TimerCallback( TimerHandle_t xTimer );

int current_count;
int previous_count;

extern TaskHandle_t xLeft_Motion;
extern TaskHandle_t xStop_Motion;
extern TaskHandle_t xRight_Motion;
extern TaskHandle_t xForward_Motion;
extern TaskHandle_t xBackward_Motion;
extern SemaphoreHandle_t xMutex;
extern QueueHandle_t xQueue;


bool DEGRADED_MODE;
TIVA_MSG degraded_mode;

void vRecv_from_bbg_TimerCallback( TimerHandle_t xTimer )
 {
    if(current_count <= previous_count)
    {
        DEGRADED_MODE = true;
        UARTprintf("DEGRADED MODE -> %d\n\r",DEGRADED_MODE);
        UARTprintf("Error!!\n\r");
        display_lcd_row1("Degraded mode");
        SysCtlDelay(100);


        degraded_mode.msg_type = REMOTE_NODE_OFF;
        degraded_mode.log_level = ERROR_T;
        xSemaphoreTake(xMutex, ( TickType_t )10);
        if(xQueueSend(xQueue, (void *)&degraded_mode,(TickType_t)10) != pdPASS)
        {
            UARTprintf("Failed to post the message, even after 10 ticks\n\r");
        }
        xSemaphoreGive(xMutex);

    }
    else
    {
        DEGRADED_MODE = false;
        UARTprintf("DEGRADED MODE -> %d\n\r",DEGRADED_MODE);
        UARTprintf("Task is alive!\n\r");
        display_lcd_row1("Normal mode");
        SysCtlDelay(100);

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

            UARTprintf("Rec %d\r\n", c);

            if(c == 0x7e)
            {
                current_count++;
            }
            if(c == BBG_FORWARD_MOTION_SIGNAL)
            {
                FORWARD();
//               xTaskNotifyGive(xForward_Motion);
            }
            else if(c == BBG_RIGHT_MOTION_SIGNAL)
            {
                RIGHT();
//               xTaskNotifyGive(xRight_Motion);
            }
            else if(c == BBG_LEFT_MOTION_SIGNAL)
            {
                LEFT();
//               xTaskNotifyGive(xLeft_Motion);
            }
            else if(c == BBG_BACKWARD_MOTION_SIGNAL)
            {
                BACKWARD();
//               xTaskNotifyGive(xBackward_Motion);
            }
            else if(c == BBG_MOTOR_STOP_SIGNAL)
            {
                STOP();
//               xTaskNotifyGive(xStop_Motion);
            }
        }
    }
}
