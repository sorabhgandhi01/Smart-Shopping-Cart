/*
 * motor_driver.c
 *
 *  Created on: Apr 22, 2019
 *      Author: omrah
 */

#include "motor_driver.h"

extern QueueHandle_t xQueue;
extern button_status_t button_status;
extern TaskHandle_t xAlert;

/* Motor Driver task */
void vMotor_Driver_Task(void *pvParameters)
{
    UARTprintf("Motor Driver Task...!\n\r");
    while(1)
    {
//        UARTprintf("Inside While(1)\n\r");
//        if(FLAG == 1)
//        {
//            UARTprintf("Receiving motor status\n\r");
////            xQueueReceive(xQueue, &(motor_status), (TickType_t)10);
//            UARTprintf("MOTOR STATUS =  %d\n\r",motor_status);
//            if(motor_status == BUTTON_PRESSED)
//            {
//                UARTprintf("Motor Moving forward\n\r");
//            }
//            else if(motor_status == BUTTON_RELEASED)
//            {
//                UARTprintf("Motor STOPPED!\n\r");
//            }
//            FLAG = 0;
        }
}


/* Alert Task */
void alert_task(void *pvParameters)
{
//    QueueData_t alert_data;
    for(;;)
    {
        ulTaskNotifyTake( pdTRUE, portMAX_DELAY );
        if(button_status == FORWARD_BUTTON_PRESSED)
        {
            UARTprintf("FORWARD\n\r");
            //Enable
            GPIOPinWrite(GPIO_PORTP_BASE,GPIO_PIN_3,GPIO_PIN_3);    //PP3 = 1
            GPIOPinWrite(GPIO_PORTH_BASE,GPIO_PIN_1,GPIO_PIN_1);    //PH1 = 1

            //Forward
            GPIOPinWrite(GPIO_PORTM_BASE,GPIO_PIN_6,GPIO_PIN_6);    //PM6 = 1
            GPIOPinWrite(GPIO_PORTK_BASE,GPIO_PIN_7,GPIO_PIN_7);    //PK7 = 1
            GPIOPinWrite(GPIO_PORTQ_BASE,GPIO_PIN_1,0);             //PQ1 = 0
            GPIOPinWrite(GPIO_PORTK_BASE,GPIO_PIN_6,0);             //PK6 = 0

        }
        else if((button_status == FORWARD_BUTTON_RELEASED)  ||
               (button_status == BACKWARD_BUTTON_RELEASED)  ||
               (button_status == LEFT_BUTTON_RELEASED)      ||
               (button_status == RIGHT_BUTTON_RELEASED))
        {
            UARTprintf("STOPPED!\n\r");
            //Enable
            GPIOPinWrite(GPIO_PORTP_BASE,GPIO_PIN_3,0);    //PP3 = 0
            GPIOPinWrite(GPIO_PORTH_BASE,GPIO_PIN_1,0);    //PH1 = 0

            //Stop
            GPIOPinWrite(GPIO_PORTM_BASE,GPIO_PIN_6,0);  //PM6 = 0
            GPIOPinWrite(GPIO_PORTK_BASE,GPIO_PIN_7,0);  //PK7 = 0
            GPIOPinWrite(GPIO_PORTQ_BASE,GPIO_PIN_1,0);  //PQ1 = 0
            GPIOPinWrite(GPIO_PORTK_BASE,GPIO_PIN_6,0);  //PK6 = 0

        }
        else if(button_status == LEFT_BUTTON_PRESSED)
        {
            UARTprintf("LEFT!\n\r");
            //Enable
            GPIOPinWrite(GPIO_PORTP_BASE,GPIO_PIN_3,0);             //PP3 = 0
            GPIOPinWrite(GPIO_PORTH_BASE,GPIO_PIN_1,GPIO_PIN_1);    //PH1 = 1

            //Left
            GPIOPinWrite(GPIO_PORTK_BASE,GPIO_PIN_7,GPIO_PIN_7);    //PK7 = 1
            GPIOPinWrite(GPIO_PORTM_BASE,GPIO_PIN_6,0);             //PM6 = 0
            GPIOPinWrite(GPIO_PORTQ_BASE,GPIO_PIN_1,0);             //PQ1 = 0
            GPIOPinWrite(GPIO_PORTK_BASE,GPIO_PIN_6,0);             //PK6 = 0
        }
        else if(button_status == RIGHT_BUTTON_PRESSED)
        {
            UARTprintf("RIGHT!\n\r");
            //Enable
            GPIOPinWrite(GPIO_PORTP_BASE,GPIO_PIN_3,GPIO_PIN_3);    //PP3 = 1
            GPIOPinWrite(GPIO_PORTH_BASE,GPIO_PIN_1,0);             //PH1 = 0

            GPIOPinWrite(GPIO_PORTK_BASE,GPIO_PIN_7,0);             //PK7 = 0
            GPIOPinWrite(GPIO_PORTM_BASE,GPIO_PIN_6,GPIO_PIN_6);    //PM6 = 1
            GPIOPinWrite(GPIO_PORTQ_BASE,GPIO_PIN_1,0);             //PQ1 = 0
            GPIOPinWrite(GPIO_PORTK_BASE,GPIO_PIN_6,0);             //PK6 = 0
        }
        else if(button_status == BACKWARD_BUTTON_PRESSED)
        {
            UARTprintf("BACKWARD!\n\r");
            //Enable
            GPIOPinWrite(GPIO_PORTP_BASE,GPIO_PIN_3,GPIO_PIN_3);    //PP3 = 1
            GPIOPinWrite(GPIO_PORTH_BASE,GPIO_PIN_1,GPIO_PIN_1);    //PH1 = 1

            //Backward
            GPIOPinWrite(GPIO_PORTK_BASE,GPIO_PIN_7,0);             //PK7 = 0
            GPIOPinWrite(GPIO_PORTM_BASE,GPIO_PIN_6,0);             //PM6 = 0
            GPIOPinWrite(GPIO_PORTQ_BASE,GPIO_PIN_1,GPIO_PIN_1);    //PQ1 = 1
            GPIOPinWrite(GPIO_PORTK_BASE,GPIO_PIN_6,GPIO_PIN_6);    //PK6 = 1

        }
    }
}
