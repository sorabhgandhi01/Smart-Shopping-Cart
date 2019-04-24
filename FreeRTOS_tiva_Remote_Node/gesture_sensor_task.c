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

    for(;;)
    {
//        if(isr_flag == 1)
//        {
//            UARTprintf("In ISR\n\r");
            if(isGestureAvailable())
            {
                UARTprintf("Reading Gesture\n\r");
                switch(readGesture())
                {
                case DIR_UP:
                        UARTprintf("UP\n\r");
                        FORWARD();
                        vTaskDelay(5000/portTICK_PERIOD_MS);
                        STOP();
                        break;
                case DIR_DOWN:
                        UARTprintf("DOWN\n\r");
                        BACKWARD();
                        vTaskDelay(5000/portTICK_PERIOD_MS);
                        STOP();
                        break;
                case DIR_LEFT:
                        UARTprintf("LEFT\n\r");
                        LEFT();
                        vTaskDelay(5000/portTICK_PERIOD_MS);
                        STOP();
                        break;
                case DIR_RIGHT:
                        UARTprintf("RIGHT\n\r");
                        RIGHT();
                        vTaskDelay(5000/portTICK_PERIOD_MS);
                        STOP();
                        break;
                case DIR_NEAR:
                        UARTprintf("NEAR\n\r");
                        break;
                case DIR_FAR:
                        UARTprintf("FAR\n\r");
                        break;
                default:
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
    }


}

