/*@Filename : ultrasonic_sensor.c
 * @Author  : Om Raheja & Sorabh Gandhi
 * @Course  : [PROJECT 2]Advanced Embedded Software Development Spring 2019
 * @Date    : 19th April 2019
 * @brief   :
 */

/****************************************************************************
 * USER DEFINED HEADER FILES                                                *
 ****************************************************************************/
#include "ultrasonic_sensor.h"

/****************************************************************************
 * EXPORTED GLOBAL VARIABLES                                                *
 ****************************************************************************/
extern int pulse_sent;
extern uint32_t time_start;
extern uint32_t time_end;

/****************************************************************************
 * ULTRASONIC SENSOR INIT                                                   *
 ****************************************************************************/
void ultrasonic_sensor_init()
{
    UARTprintf("Configuring Ultrasonic Sensor................\n\r");
    /* Configure Timer 2 */
    SysCtlPeripheralEnable(SYSCTL_PERIPH_TIMER2);
    TimerConfigure(TIMER2_BASE, TIMER_CFG_PERIODIC_UP);


    /* Configure Echo Pin */
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOK);
    GPIOPinTypeGPIOInput(GPIO_PORTK_BASE, GPIO_PIN_1);

    GPIOIntEnable(GPIO_PORTK_BASE, GPIO_INT_PIN_1);
    GPIOIntTypeSet(GPIO_PORTK_BASE,GPIO_PIN_1,GPIO_BOTH_EDGES );
    GPIOIntRegister(GPIO_PORTK_BASE,UltraSoniC_IRQ_Handler);
    GPIOIntClear(GPIO_PORTK_BASE, GPIO_INT_PIN_1);


    /* Configure Trigger pin */
    GPIOPinTypeGPIOOutput(GPIO_PORTK_BASE, GPIO_PIN_0);
    GPIOPadConfigSet(GPIO_PORTK_BASE,GPIO_PIN_0,GPIO_STRENGTH_2MA,GPIO_PIN_TYPE_STD_WPU);

    UARTprintf("Ultrasonic Sensor Configured Successfully\n\r");
}

/****************************************************************************
 * GET DISTANCE                                                             *
 ****************************************************************************/
void getDistance()
{
    GPIOPinWrite(GPIO_PORTK_BASE,GPIO_PIN_0,GPIO_PIN_0);
    //vTaskDelay(pdMS_TO_TICKS(10));
    SysCtlDelay(100);
    GPIOPinWrite(GPIO_PORTK_BASE,GPIO_PIN_0,0);
}


/****************************************************************************
 * ULTRASONIC IRQ HANDLER                                                   *
 ****************************************************************************/
void UltraSoniC_IRQ_Handler()
{
    IntMasterDisable();

    //clear interrupt flag
    GPIOIntClear(GPIO_PORTK_BASE,GPIO_PIN_1);

    //Echo pulse - rising edge
    if(GPIOPinRead(GPIO_PORTK_BASE,GPIO_PIN_1) == GPIO_PIN_1)
    {
        HWREG(TIMER2_BASE + TIMER_O_TAV) = 0;
        TimerEnable(TIMER2_BASE,TIMER_A);
        time_start = TimerValueGet(TIMER2_BASE,TIMER_A);
        pulse_sent = 0;
    }
    else
    {
        time_end = TimerValueGet(TIMER2_BASE,TIMER_A);
        TimerDisable(TIMER2_BASE,TIMER_A);
        pulse_sent = 1;
    }

    IntMasterEnable();
}

