/*@Filename : motor_driver.c
 * @Author  : Om Raheja & Sorabh Gandhi
 * @Course  : [PROJECT 2]Advanced Embedded Software Development Spring 2019
 * @Date    : 19th April 2019
 * @brief   :
 */

#include <motor_control.h>

void FORWARD()
{
    UARTprintf("FORWARD\n\r");
    //Enable
    GPIOPinWrite(GPIO_PORTP_BASE,GPIO_PIN_3,GPIO_PIN_3);    //PP3 = 1 [EN1]
    GPIOPinWrite(GPIO_PORTH_BASE,GPIO_PIN_1,GPIO_PIN_1);    //PH1 = 1 [EN2]

    //Forward
    GPIOPinWrite(GPIO_PORTM_BASE,GPIO_PIN_6,GPIO_PIN_6);    //PM6 = 1
    GPIOPinWrite(GPIO_PORTK_BASE,GPIO_PIN_7,GPIO_PIN_7);    //PK7 = 1
    GPIOPinWrite(GPIO_PORTQ_BASE,GPIO_PIN_1,0);             //PQ1 = 0
    GPIOPinWrite(GPIO_PORTK_BASE,GPIO_PIN_6,0);             //PK6 = 0
}

void STOP()
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

void RIGHT()
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


void LEFT()
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

void BACKWARD()
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
