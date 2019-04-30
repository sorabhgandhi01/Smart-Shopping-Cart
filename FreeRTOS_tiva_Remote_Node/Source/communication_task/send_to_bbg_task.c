/*
 * send_to_bbg_task.c
 *
 *  Created on: Apr 24, 2019
 *      Author: omrah
 */
#include "send_to_bbg_task.h"
#include "FreeRTOS.h"
#include "queue.h"
#include "helper.h"
#include "semphr.h"
#include "my_uart.h"
#include "timers.h"
#include "task.h"
#include "Lcd_display.h"

extern QueueHandle_t xQueue;
extern SemaphoreHandle_t xMutex;
uint8_t toggle_flag = 0;

void vTimerCallback( TimerHandle_t xTimer );

void vTimerCallback( TimerHandle_t xTimer )
 {
    toggle_flag = 1;
 }

void send_to_bbg_task(void *pvParameters)
{
    UARTprintf("***********SEND_TO_BBG_TASK************\n\r");

    TIVA_MSG task_data;

    TIVA_MSG hb_send;
    hb_send.msg_type = 0;
    hb_send.log_level = 2;
    hb_send.sensor_data = 0;

    TimerHandle_t xTimers_hb = xTimerCreate
                    (
                    "Heart_Beat_Timer",
                    pdMS_TO_TICKS(5000),
                    pdTRUE,
                    ( void * ) 0,
                    vTimerCallback
                    );

    xTimerStart(xTimers_hb, 0);

    //display_lcd_row1("Ges Task");
    display_lcd_row3("PB Task");
//    display_lcd_row2("UL Task");
    display_lcd_row4("Control node");

    SysCtlDelay(100000);

    while(1)
    {
        if (toggle_flag == 1) {
            UART_send(&hb_send, sizeof(hb_send));
            toggle_flag = 0;
        }

        if(xQueueReceive( xQueue, &(task_data), ( TickType_t ) 10 ))
        {
//            display_lcd_row1("100");

            UARTprintf("LOG_LEVEL = %d\tMESSAGE TYPE = %d\tDATA = %d\n\r", task_data.log_level, task_data.msg_type, task_data.sensor_data);
            UART_send(&task_data, sizeof(task_data));
            vTaskDelay(500 / portTICK_PERIOD_MS);
//            display_lcd_row1("");
        }
    }
}

