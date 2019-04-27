/*@Filename : motor_driver_task.c
 * @Author  : Om Raheja & Sorabh Gandhi
 * @Course  : [PROJECT 2]Advanced Embedded Software Development Spring 2019
 * @Date    : 19th April 2019
 * @brief   :
 */


#include <motor_control_task.h>
#include "helper.h"

extern PB_DATA button_status;
extern TaskHandle_t xAlert;
extern QueueHandle_t xQueue;

extern SemaphoreHandle_t xMutex;

/* Motor Driver task */
void vMotor_Driver_Task(void *pvParameters)
{
    UARTprintf("Motor Driver Task!\n\r");
    while(1)
    {
    }
}


/* Degraded Motor Operation Task */
void vDegraded_Motor_Operation_Task(void *pvParameters)
{
    TaskData_t task_data;
    for(;;)
    {
        xSemaphoreTake(xMutex, ( TickType_t )10);
        ulTaskNotifyTake( pdTRUE, portMAX_DELAY );
        if(button_status == FORWARD_BUTTON_PRESSED)
        {
            //strcpy(task_data.msgID , "MOTOR DRIVER:[F]");
            //task_data.TaskData = 11;
            //if(xQueueSend(xQueue, (void *)&task_data,(TickType_t)10) != pdPASS)
            //{
            //    UARTprintf("Failed to post the message, even after 10 ticks\n\r");
            //}
            FORWARD();

        }
        else if((button_status == FORWARD_BUTTON_RELEASED)  ||
               (button_status == BACKWARD_BUTTON_RELEASED)  ||
               (button_status == LEFT_BUTTON_RELEASED)      ||
               (button_status == RIGHT_BUTTON_RELEASED))
        {
            //strcpy(task_data.msgID , "MOTOR DRIVER:[STOP]");
            //task_data.TaskData = 55;
            //if(xQueueSend(xQueue, (void *)&task_data,(TickType_t)10) != pdPASS)
            //{
            //    UARTprintf("Failed to post the message, even after 10 ticks\n\r");
            //}

            STOP();
        }
        else if(button_status == LEFT_BUTTON_PRESSED)
        {
            //strcpy(task_data.msgID , "MOTOR DRIVER:[L]");
            //task_data.TaskData = 01;
            //if(xQueueSend(xQueue, (void *)&task_data,(TickType_t)10) != pdPASS)
            //{
            //   UARTprintf("Failed to post the message, even after 10 ticks\n\r");
            //}

            LEFT();
        }
        else if(button_status == RIGHT_BUTTON_PRESSED)
        {
            //strcpy(task_data.msgID , "MOTOR DRIVER:[R]");
            //task_data.TaskData = 10;
            //if(xQueueSend(xQueue, (void *)&task_data,(TickType_t)10) != pdPASS)
            //{
            //    UARTprintf("Failed to post the message, even after 10 ticks\n\r");
            //}

            RIGHT();
        }
        else if(button_status == BACKWARD_BUTTON_PRESSED)
        {
            //strcpy(task_data.msgID , "MOTOR DRIVER:[B]");
            //task_data.TaskData = 00;
            //if(xQueueSend(xQueue, (void *)&task_data,(TickType_t)10) != pdPASS)
            //{
            //    UARTprintf("Failed to post the message, even after 10 ticks\n\r");
            //}
            BACKWARD();
        }
        xSemaphoreGive(xMutex);
    }
}


void vForward_Motion_Task(void *pvParameters)
{
    ulTaskNotifyTake( pdTRUE, portMAX_DELAY );
    FORWARD();

}
void vBackward_Motion_Task(void *pvParameters)
{
    ulTaskNotifyTake( pdTRUE, portMAX_DELAY );
    BACKWARD();

}
void vLeft_Motion_Task(void *pvParameters)
{
    ulTaskNotifyTake( pdTRUE, portMAX_DELAY );
    LEFT();

}
void vRight_Motion_Task(void *pvParameters)
{
    ulTaskNotifyTake( pdTRUE, portMAX_DELAY );
    RIGHT();

}
void vStop_Motion_Task(void *pvParameters)
{
    ulTaskNotifyTake( pdTRUE, portMAX_DELAY );
    STOP();

}
