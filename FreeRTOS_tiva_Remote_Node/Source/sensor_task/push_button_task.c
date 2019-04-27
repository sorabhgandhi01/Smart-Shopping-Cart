/*@Filename : push_button_task.c
 * @Author  : Om Raheja & Sorabh Gandhi
 * @Course  : [PROJECT 2]Advanced Embedded Software Development Spring 2019
 * @Date    : 19th April 2019
 * @brief   :
 *@References : https://e2e.ti.com/support/microcontrollers/other/f/908/t/332605
 */


#include "push_button_task.h"

/* Push Button task */
void vPush_Button_Task(void *pvParameters)
{
    UARTprintf("\n\r************Push Button Task!************\n\r");

    Enable_Push_Button_Peripherals();

    Configure_Motor_Driver_GPIO();

    Configure_External_Push_Buttons();

    while(1)
    {
    }
}
