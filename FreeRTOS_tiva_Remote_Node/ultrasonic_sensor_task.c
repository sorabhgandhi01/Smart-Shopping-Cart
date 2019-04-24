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

    while(1)
    {
        getDistance();

        while(pulse_sent != 0);

        time = time_end - time_start;

        distance = (((float)(1.0/(output_clock_rate_hz/1000000))*time));

        distance = distance/58;

        UARTprintf("Distance = %d\n\r",time);

        vTaskDelay(1000/portTICK_PERIOD_MS);
    }
}
