/*@Filename : ultrasonic_sensor_task.c
 * @Author  : Om Raheja & Sorabh Gandhi
 * @Course  : [PROJECT 2]Advanced Embedded Software Development Spring 2019
 * @Date    : 19th April 2019
 * @brief   :
 */

/****************************************************************************
 * USER DEFINED HEADER FILES                                                *
 ****************************************************************************/
#include "ultrasonic_sensor_task.h"


/****************************************************************************
 * EXPORTED GLOBAL VARIABLES                                                *
 ****************************************************************************/
extern uint32_t output_clock_rate_hz;

extern SemaphoreHandle_t xMutex;

extern QueueHandle_t xQueue;

/****************************************************************************
 * GLOBAL VARIABLES                                                         *
 ****************************************************************************/
float distance;
int pulse_sent = 0;
uint32_t time_start;
uint32_t time_end;
uint32_t time;

/****************************************************************************
 * vULTRASONIC TASK                                                         *
 ****************************************************************************/
void vUltraSonic_Task(void *pvParameters)
{
    UARTprintf("UltraSonic Sensor Task\n\r");

    ultrasonic_sensor_init();

    TaskData_t ultrasonic_data;
    while(1)
    {
        xSemaphoreTake(xMutex,( TickType_t )10);

        getDistance();

        while(pulse_sent != 0);

        time = time_end - time_start;

        distance = (((float)(1.0/(output_clock_rate_hz/1000000))*time));

        distance = distance/58;

        //UARTprintf("Distance = %d\n\r",time);

        strcpy(ultrasonic_data.msgID , "ULTRASONIC");
        ultrasonic_data.TaskData = time;
        if(xQueueSend(xQueue, (void *)&ultrasonic_data,(TickType_t)10) != pdPASS)
        {
            UARTprintf("Failed to post the message, even after 10 ticks\n\r");
        }

        xSemaphoreGive(xMutex);

        vTaskDelay(1000/portTICK_PERIOD_MS);

    }
}
