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

/* Gesture sensor task */
void vGesture_Sensor_Task(void *pvParameters)
{
    UARTprintf("*****************GESTURE SENSOR TASK*****************\n\r");

    /* Initialize Gesture Sensor Task */
    if(SparkFun_APDS9960_Init()){
        UARTprintf("APDS-9960 initialization complete!s\n\r");
    }
    else
    {
        UARTprintf("Something went wrong during APDS-9960 init!\n\r");
        //Kill Gesture Recognition Task
    }

    /* Enable Gesture Sensor */
    if(enableGestureSensor(true))
    {
        UARTprintf("Gesture Sensor Enabled & is Now Running!\n\r");
    }
    else
    {
        UARTprintf("Something went wrong during gesture sensor init!\n\r");
    }

    /* Initialize interrupt service routine */
    attachInterrupt();

    TaskData_t gesture_sensor_data;

    for(;;)
    {
        xSemaphoreTake(xMutex, ( TickType_t )10);
            if(isGestureAvailable())
            {
                UARTprintf("Reading Gesture\n\r");
                switch(readGesture())
                {
                case DIR_UP:
                        strcpy(gesture_sensor_data.msgID , "GESTURE:[F]");
                        gesture_sensor_data.TaskData = 11;
                        if(xQueueSend(xQueue, (void *)&gesture_sensor_data,(TickType_t)10) != pdPASS)
                        {
                            UARTprintf("Failed to post the message, even after 10 ticks\n\r");
                        }

                        //UARTprintf("UP\n\r");
                        FORWARD();
                        vTaskDelay(5000/portTICK_PERIOD_MS);
                        STOP();
                        break;
                case DIR_DOWN:
                        strcpy(gesture_sensor_data.msgID , "GESTURE:[B]");
                        gesture_sensor_data.TaskData = 00;
                        if(xQueueSend(xQueue, (void *)&gesture_sensor_data,(TickType_t)10) != pdPASS)
                        {
                            UARTprintf("Failed to post the message, even after 10 ticks\n\r");
                        }

                        //UARTprintf("DOWN\n\r");
                        BACKWARD();
                        vTaskDelay(5000/portTICK_PERIOD_MS);
                        STOP();
                        break;
                case DIR_LEFT:
                        strcpy(gesture_sensor_data.msgID , "GESTURE:[L]");
                        gesture_sensor_data.TaskData = 01;
                        if(xQueueSend(xQueue, (void *)&gesture_sensor_data,(TickType_t)10) != pdPASS)
                        {
                            UARTprintf("Failed to post the message, even after 10 ticks\n\r");
                        }

                        //UARTprintf("LEFT\n\r");
                        LEFT();
                        vTaskDelay(5000/portTICK_PERIOD_MS);
                        STOP();
                        break;
                case DIR_RIGHT:
                        strcpy(gesture_sensor_data.msgID , "GESTURE:[R]");
                        gesture_sensor_data.TaskData = 10;
                        if(xQueueSend(xQueue, (void *)&gesture_sensor_data,(TickType_t)10) != pdPASS)
                        {
                            UARTprintf("Failed to post the message, even after 10 ticks\n\r");
                        }

                        //UARTprintf("RIGHT\n\r");
                        RIGHT();
                        vTaskDelay(5000/portTICK_PERIOD_MS);
                        STOP();
                        break;
                case DIR_NEAR:
                        strcpy(gesture_sensor_data.msgID , "GESTURE:[NEAR]");
                        gesture_sensor_data.TaskData = 999;
                        if(xQueueSend(xQueue, (void *)&gesture_sensor_data,(TickType_t)10) != pdPASS)
                        {
                            UARTprintf("Failed to post the message, even after 10 ticks\n\r");
                        }

                        //UARTprintf("NEAR\n\r");
                        break;
                case DIR_FAR:
                        strcpy(gesture_sensor_data.msgID , "GESTURE:[FAR]");
                        gesture_sensor_data.TaskData = 111;
                        if(xQueueSend(xQueue, (void *)&gesture_sensor_data,(TickType_t)10) != pdPASS)
                        {
                            UARTprintf("Failed to post the message, even after 10 ticks\n\r");
                        }

                        //UARTprintf("FAR\n\r");
                        break;
                default:
                        strcpy(gesture_sensor_data.msgID , "GESTURE:[NONE]");
                        gesture_sensor_data.TaskData = 1000;
                        if(xQueueSend(xQueue, (void *)&gesture_sensor_data,(TickType_t)10) != pdPASS)
                        {
                            UARTprintf("Failed to post the message, even after 10 ticks\n\r");
                        }

                        UARTprintf("NONE\n\r");
                        break;
                }
            }
            isr_flag = 0;
            GPIOIntEnable(GPIO_PORTA_BASE,GPIO_PIN_6);


//            /* Detach Interrupts */
//            detachInterrupt();
//
//            /* Handle Gesture */
//            handleGesture();
//
//            isr_flag = 0;
//
//            /* Attach Interrupts */
//            attachInterrupt();
//        }
        SysCtlDelay(1000000);
        xSemaphoreGive(xMutex);
    }


}

