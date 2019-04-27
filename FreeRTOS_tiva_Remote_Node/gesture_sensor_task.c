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
        if(SparkFun_APDS9960_Available() == -1)
        {
            UARTprintf("Gesture Sensor Down\n\rGesture Task Killed\n\r");
            vTaskDelete(Gesture_Task);
        }
        else
        {

//        xSemaphoreTake(xMutex, ( TickType_t )10);
//        UARTprintf("CHECKING IF GES SEN IS AVAILABLE OR NOT!\n\r");
            if(isGestureAvailable())
            {
                UARTprintf("Reading Gesture\n\r");
                switch(readGesture())
                {
                case DIR_UP:
//                        strcpy(gesture_sensor_data.msgID , "GESTURE:[F]");
//                        gesture_sensor_data.TaskData = 11;
                        gesture_sensor_data.msg_type = GESTURE_SENSOR_DATA;
                        gesture_sensor_data.data.gesture_data = GS_FORWARD;

//                        if(xQueueSend(xQueue, (void *)&gesture_sensor_data,(TickType_t)10) != pdPASS)
//                        {
//                            UARTprintf("Failed to post the message, even after 10 ticks\n\r");
//                        }

//                        if(xQueueSend(xQueue, (void *)&gesture_sensor_data,(TickType_t)10) != pdPASS)
//                        {
//                            UARTprintf("Failed to post the message, even after 10 ticks\n\r");
//                        }

                        //UARTprintf("UP\n\r");
//                        FORWARD();
//                        vTaskDelay(5000/portTICK_PERIOD_MS);
//                        STOP();
                        break;
                case DIR_DOWN:
//                        strcpy(gesture_sensor_data.msgID , "GESTURE:[B]");
//                        gesture_sensor_data.TaskData = 00;
//                        if(xQueueSend(xQueue, (void *)&gesture_sensor_data,(TickType_t)10) != pdPASS)
//                        {
//                            UARTprintf("Failed to post the message, even after 10 ticks\n\r");
//                        }
                        gesture_sensor_data.msg_type = GESTURE_SENSOR_DATA;
                        gesture_sensor_data.data.gesture_data = GS_BACKWARD;

//                        if(xQueueSend(xQueue, (void *)&gesture_sensor_data,(TickType_t)10) != pdPASS)
//                        {
//                            UARTprintf("Failed to post the message, even after 10 ticks\n\r");
//                        }


                        //UARTprintf("DOWN\n\r");
//                        BACKWARD();
//                        vTaskDelay(5000/portTICK_PERIOD_MS);
//                        STOP();
                        break;
                case DIR_LEFT:
//                        strcpy(gesture_sensor_data.msgID , "GESTURE:[L]");
//                        gesture_sensor_data.TaskData = 01;
//                        if(xQueueSend(xQueue, (void *)&gesture_sensor_data,(TickType_t)10) != pdPASS)
//                        {
//                            UARTprintf("Failed to post the message, even after 10 ticks\n\r");
//                        }
                        gesture_sensor_data.msg_type = GESTURE_SENSOR_DATA;
                        gesture_sensor_data.data.gesture_data = GS_LEFT;

//                        if(xQueueSend(xQueue, (void *)&gesture_sensor_data,(TickType_t)10) != pdPASS)
//                        {
//                            UARTprintf("Failed to post the message, even after 10 ticks\n\r");
//                        }


                        //UARTprintf("LEFT\n\r");
//                        LEFT();
//                        vTaskDelay(5000/portTICK_PERIOD_MS);
//                        STOP();
                        break;
                case DIR_RIGHT:
//                        strcpy(gesture_sensor_data.msgID , "GESTURE:[R]");
//                        gesture_sensor_data.TaskData = 10;
//                        if(xQueueSend(xQueue, (void *)&gesture_sensor_data,(TickType_t)10) != pdPASS)
//                        {
//                            UARTprintf("Failed to post the message, even after 10 ticks\n\r");
//                        }

                        gesture_sensor_data.msg_type = GESTURE_SENSOR_DATA;
                        gesture_sensor_data.data.gesture_data = GS_RIGHT;

//                        if(xQueueSend(xQueue, (void *)&gesture_sensor_data,(TickType_t)10) != pdPASS)
//                        {
//                            UARTprintf("Failed to post the message, even after 10 ticks\n\r");
//                        }

                        //UARTprintf("RIGHT\n\r");
//                        RIGHT();
//                        vTaskDelay(5000/portTICK_PERIOD_MS);
//                        STOP();
                        break;
                case DIR_NEAR:
//                        strcpy(gesture_sensor_data.msgID , "GESTURE:[NEAR]");
//                        gesture_sensor_data.TaskData = 999;
//                        if(xQueueSend(xQueue, (void *)&gesture_sensor_data,(TickType_t)10) != pdPASS)
//                        {
//                            UARTprintf("Failed to post the message, even after 10 ticks\n\r");
//                        }

                        gesture_sensor_data.msg_type = GESTURE_SENSOR_DATA;
                        gesture_sensor_data.data.gesture_data = GS_NEAR;

//                        if(xQueueSend(xQueue, (void *)&gesture_sensor_data,(TickType_t)10) != pdPASS)
//                        {
//                            UARTprintf("Failed to post the message, even after 10 ticks\n\r");
//                        }

                        //UARTprintf("NEAR\n\r");
                        break;
                case DIR_FAR:
//                        strcpy(gesture_sensor_data.msgID , "GESTURE:[FAR]");
//                        gesture_sensor_data.TaskData = 111;
//                        if(xQueueSend(xQueue, (void *)&gesture_sensor_data,(TickType_t)10) != pdPASS)
//                        {
//                            UARTprintf("Failed to post the message, even after 10 ticks\n\r");
//                        }
                        gesture_sensor_data.msg_type = GESTURE_SENSOR_DATA;
                        gesture_sensor_data.data.gesture_data = GS_FAR;

//                        if(xQueueSend(xQueue, (void *)&gesture_sensor_data,(TickType_t)10) != pdPASS)
//                        {
//                            UARTprintf("Failed to post the message, even after 10 ticks\n\r");
//                        }


                        //UARTprintf("FAR\n\r");
                        break;
                default:
//                        strcpy(gesture_sensor_data.msgID , "GESTURE:[NONE]");
//                        gesture_sensor_data.TaskData = 1000;
//                        if(xQueueSend(xQueue, (void *)&gesture_sensor_data,(TickType_t)10) != pdPASS)
//                        {
//                            UARTprintf("Failed to post the message, even after 10 ticks\n\r");
//                        }
                        gesture_sensor_data.msg_type = GESTURE_SENSOR_DATA;
                        gesture_sensor_data.data.gesture_data = GS_NO_GESTURE;

//                        if(xQueueSend(xQueue, (void *)&gesture_sensor_data,(TickType_t)10) != pdPASS)
//                        {
//                            UARTprintf("Failed to post the message, even after 10 ticks\n\r");
//                        }


                        UARTprintf("NONE\n\r");
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
//        xSemaphoreGive(xMutex);
        }
    }

}

