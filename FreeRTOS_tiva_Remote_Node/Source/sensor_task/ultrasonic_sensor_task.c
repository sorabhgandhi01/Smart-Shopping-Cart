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
#include "Lcd_display.h"

/****************************************************************************
 * EXPORTED GLOBAL VARIABLES                                                *
 ****************************************************************************/
extern uint32_t output_clock_rate_hz;

extern SemaphoreHandle_t xMutex;

extern QueueHandle_t xQueue;

extern TaskHandle_t Ultrasonic_Task;

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
    int dead = 0;
    ultrasonic_sensor_init();
    TIVA_MSG ultrasonic_sensor_data;

    while(1)
    {
        xSemaphoreTake(xMutex,( TickType_t )10);
        getDistance();

        if (pulse_sent != 0)
        {
            time = time_end - time_start;
            dead = 0;
            pulse_sent = 0;

            distance = (((float)(1.0/(output_clock_rate_hz/1000000))*time));
            distance = distance/58;

            ultrasonic_sensor_data.msg_type = DISTANCE_SENSOR_DATA;
            ultrasonic_sensor_data.sensor_data = (uint32_t)distance;
            ultrasonic_sensor_data.log_level = INFO;

            if(xQueueSend(xQueue, (void *)&ultrasonic_sensor_data,(TickType_t)10) != pdPASS)
            {
                UARTprintf("Failed to post the message, even after 10 ticks\n\r");
            }


            xSemaphoreGive(xMutex);

            vTaskDelay(1000/portTICK_PERIOD_MS);
        }
        else
        {
            dead++;
        }

        if (dead > 1) {
            UARTprintf("Distance Sensor Inactive\n");

        if(xQueueSend(xQueue, (void *)&ultrasonic_sensor_data,(TickType_t)10) != pdPASS)
        {
            UARTprintf("Failed to post the message, even after 10 ticks\n\r");
        }



            vTaskDelay(1000/portTICK_PERIOD_MS);
        }

    }
}
