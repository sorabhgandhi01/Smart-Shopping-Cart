/*
 * gesture_sensor.c
 *
 *  Created on: Apr 18, 2019
 *      Author: omrah
 */
/* Header Files */
#include "gesture_sensor_task.h"


/* Global Variables */
volatile uint8_t isr_flag = 0;

extern SemaphoreHandle_t xMutex;
extern QueueHandle_t xQueue;
extern TaskHandle_t Gesture_Task;

/* Gesture sensor task */
void vGesture_Sensor_Task(void *pvParameters)
{
    UARTprintf("*****************GESTURE SENSOR TASK*****************\n\r");

    /* Initialize Gesture Sensor Task */
    if(SparkFun_APDS9960_Init()){
        UARTprintf("APDS-9960 initialization complete!\n\r");
    }
    else
    {
        UARTprintf("Something went wrong during APDS-9960 init!\n\r");
        //Kill Gesture Recognition Task
        UARTprintf("Gesture Task Killed\n\r");
        vTaskDelete(Gesture_Task);
    }

    /* Enable Gesture Sensor */
    if(enableGestureSensor(true))
    {
        UARTprintf("Gesture Sensor Enabled & is Now Running!\n\r");
    }
    else
    {
        UARTprintf("Something went wrong during gesture sensor init!\n\r");
        UARTprintf("KILL THE TASK (GESTURE)\n\r");
    }

    /* Initialize interrupt service routine */
    attachInterrupt();

    TIVA_MSG gesture_sensor_data;

    for(;;)
    {
            if(isGestureAvailable())
            {
                UARTprintf("Reading Gesture\n\r");
                switch(readGesture())
                {
                case DIR_UP:
                        gesture_sensor_data.msg_type = GESTURE_SENSOR_DATA;
                        gesture_sensor_data.sensor_data = GS_FORWARD;
                        gesture_sensor_data.log_level = INFO;
                        break;

                case DIR_DOWN:
                        gesture_sensor_data.msg_type = GESTURE_SENSOR_DATA;
                        gesture_sensor_data.sensor_data = GS_BACKWARD;
                        gesture_sensor_data.log_level = INFO;
                        break;

                case DIR_LEFT:
                        gesture_sensor_data.msg_type = GESTURE_SENSOR_DATA;
                        gesture_sensor_data.sensor_data = GS_LEFT;
                        gesture_sensor_data.log_level = INFO;
                        break;

                case DIR_RIGHT:
                        gesture_sensor_data.msg_type = GESTURE_SENSOR_DATA;
                        gesture_sensor_data.sensor_data = GS_RIGHT;
                        gesture_sensor_data.log_level = INFO;
                        break;

                case DIR_NEAR:
                        gesture_sensor_data.msg_type = GESTURE_SENSOR_DATA;
                        gesture_sensor_data.sensor_data = GS_NEAR;
                        gesture_sensor_data.log_level = INFO;

                        break;
                case DIR_FAR:
                        gesture_sensor_data.msg_type = GESTURE_SENSOR_DATA;
                        gesture_sensor_data.sensor_data = GS_FAR;
                        gesture_sensor_data.log_level = INFO;

                        break;
                default:
                        gesture_sensor_data.msg_type = GESTURE_SENSOR_DATA;
                        gesture_sensor_data.sensor_data = GS_NO_GESTURE;
                        gesture_sensor_data.log_level = INFO;

                        //UARTprintf("NONE\n\r");
                        break;
                }
                xSemaphoreTake(xMutex, ( TickType_t )10);
                if(xQueueSend(xQueue, (void *)&gesture_sensor_data,(TickType_t)10) != pdPASS)
                {
                    UARTprintf("Failed to post the message, even after 10 ticks\n\r");
                }
                xSemaphoreGive(xMutex);


            }
            GPIOIntEnable(GPIO_PORTA_BASE,GPIO_PIN_6);


        SysCtlDelay(1000000);
    }


}

