/*@Filename : motor_driver_task.c
 * @Author  : Om Raheja & Sorabh Gandhi
 * @Course  : [PROJECT 2]Advanced Embedded Software Development Spring 2019
 * @Date    : 19th April 2019
 * @brief   :
 */


#include "motor_driver_task.h"


extern button_status_t button_status;
extern TaskHandle_t xAlert;

/* Motor Driver task */
void vMotor_Driver_Task(void *pvParameters)
{
    UARTprintf("Motor Driver Task!\n\r");
    while(1)
    {
    }
}


/* Alert Task */
void alert_task(void *pvParameters)
{

    for(;;)
    {
        ulTaskNotifyTake( pdTRUE, portMAX_DELAY );
        if(button_status == FORWARD_BUTTON_PRESSED)
        {
            FORWARD();

        }
        else if((button_status == FORWARD_BUTTON_RELEASED)  ||
               (button_status == BACKWARD_BUTTON_RELEASED)  ||
               (button_status == LEFT_BUTTON_RELEASED)      ||
               (button_status == RIGHT_BUTTON_RELEASED))
        {
            STOP();
        }
        else if(button_status == LEFT_BUTTON_PRESSED)
        {
            LEFT();
        }
        else if(button_status == RIGHT_BUTTON_PRESSED)
        {
            RIGHT();
        }
        else if(button_status == BACKWARD_BUTTON_PRESSED)
        {
            BACKWARD();
        }
    }
}
