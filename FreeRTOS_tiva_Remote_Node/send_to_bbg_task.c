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

extern QueueHandle_t xQueue;
extern SemaphoreHandle_t xMutex;

void send_to_bbg_task(void *pvParameters)
{
    UARTprintf("***********SEND_TO_BBG_TASK************\n\r");

    TaskData_t task_data;

    while(1)
    {
        if(xQueueReceive( xQueue, &(task_data), ( TickType_t ) 10 ))
        {
            UARTprintf("[SEND_TO_BBG]:\tMessage ID:%s\tData:%d\n\r",task_data.msgID,task_data.TaskData);
        }

    }

}

