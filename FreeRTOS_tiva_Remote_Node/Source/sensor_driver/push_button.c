/*@Filename : push_button.c
 * @Author  : Om Raheja & Sorabh Gandhi
 * @Course  : [PROJECT 2]Advanced Embedded Software Development Spring 2019
 * @Date    : 24th April 2019
 * @brief   : Contains all the Functions related to Push Button Events
 *
 */

/****************************************************************************
 * USER DEFINED HEADER FILES                                                *
 ****************************************************************************/
#include "push_button.h"
#include <stdbool.h>

extern bool DEGRADED_MODE;


/****************************************************************************
 * GLOBAL VARIABLES                                                         *
 ****************************************************************************/
static TIVA_MSG Button_Status;
PB_DATA button_status;
extern QueueHandle_t xQueue;
/****************************************************************************
 * ON BUTTON DOWN                                                           *
 ****************************************************************************/
void onButtonDown(void)
{
    if (GPIOIntStatus(GPIO_PORTJ_BASE, false) & GPIO_PIN_0)
    {
        forward_button_pressed();
    }

    if (GPIOIntStatus(GPIO_PORTJ_BASE, false) & GPIO_PIN_1)
    {
         backward_button_pressed();
    }

    if (GPIOIntStatus(GPIO_PORTL_BASE, false) & GPIO_PIN_0)
    {
        right_button_pressed();
    }

    if (GPIOIntStatus(GPIO_PORTL_BASE, false) & GPIO_PIN_1)
    {
        left_button_pressed();
    }
}


/****************************************************************************
 * ON BUTTON UP                                                             *
 ****************************************************************************/
void onButtonUp(void)
{
    if (GPIOIntStatus(GPIO_PORTJ_BASE, false) & GPIO_PIN_0)
    {
        forward_button_released();
    }

    if (GPIOIntStatus(GPIO_PORTJ_BASE, false) & GPIO_PIN_1)
    {
        backward_button_released();
    }

    if (GPIOIntStatus(GPIO_PORTL_BASE, false) & GPIO_PIN_0)
    {
        right_button_released();
    }

    if (GPIOIntStatus(GPIO_PORTL_BASE, false) & GPIO_PIN_1)
    {
        left_button_released();
    }
}


/****************************************************************************
 * FORWARD BUTTON PRESSED                                                   *
 ****************************************************************************/
void forward_button_pressed()
{
    UARTprintf("FORWARD  DEGRADED MODE -> %d\n\r",DEGRADED_MODE);
    if(DEGRADED_MODE)
    {
        xTaskNotifyGive(xForward_Motion);
    }
    else
    {
        Button_Status.msg_type = PUSH_BUTTON_SENSOR_DATA;
        Button_Status.sensor_data = FORWARD_BUTTON_PRESSED;
        Button_Status.log_level = INFO;
        UARTprintf("Cart->FORWARD\n\r");
        if(xQueueSend(xQueue, (void *)&Button_Status,(TickType_t)10) != pdPASS)
        {
            UARTprintf("Failed to post the message, even after 10 ticks\n\r");
        }


    }

    GPIOIntRegister(GPIO_PORTJ_BASE, onButtonUp);           // Register our handler function for port J
    GPIOIntTypeSet(GPIO_PORTJ_BASE, GPIO_PIN_0,
                   GPIO_RISING_EDGE);                       // Configure PJ0 for rising edge trigger
    GPIOIntClear(GPIO_PORTJ_BASE, GPIO_PIN_0);              // Clear interrupt flag
}

/****************************************************************************
 * BACKWARD BUTTON PRESSED                                                  *
 ****************************************************************************/
void backward_button_pressed()
{
    UARTprintf("BACKWARD  DEGRADED MODE -> %d\n\r",DEGRADED_MODE);
    button_status = BACKWARD_BUTTON_PRESSED;

    if(DEGRADED_MODE)
    {
        xTaskNotifyGive(xBackward_Motion);
    }
    else
    {
        Button_Status.msg_type = PUSH_BUTTON_SENSOR_DATA;
        Button_Status.sensor_data = BACKWARD_BUTTON_PRESSED;
        Button_Status.log_level = INFO;
        UARTprintf("Cart->BACKWARD\n\r");
        if(xQueueSend(xQueue, (void *)&Button_Status,(TickType_t)10) != pdPASS)
        {
            UARTprintf("Failed to post the message, even after 10 ticks\n\r");
        }

    }


    GPIOIntRegister(GPIO_PORTJ_BASE, onButtonUp);       // Register our handler function for port J
    GPIOIntTypeSet(GPIO_PORTJ_BASE, GPIO_PIN_1,
                   GPIO_RISING_EDGE);                   // Configure PJ1 for rising edge trigger
    GPIOIntClear(GPIO_PORTJ_BASE, GPIO_PIN_1);          // Clear interrupt flag
}

/****************************************************************************
 * RIGHT BUTTON PRESSED                                                     *
 ****************************************************************************/
void right_button_pressed()
{
    UARTprintf("RIGHT  DEGRADED MODE -> %d\n\r",DEGRADED_MODE);
    button_status = RIGHT_BUTTON_PRESSED;

    if(DEGRADED_MODE)
    {
        xTaskNotifyGive(xRight_Motion);
    }
    else
    {
        Button_Status.msg_type = PUSH_BUTTON_SENSOR_DATA;
        Button_Status.sensor_data = RIGHT_BUTTON_PRESSED;
        Button_Status.log_level = INFO;
        UARTprintf("Cart->RIGHT\n\r");
        if(xQueueSend(xQueue, (void *)&Button_Status,(TickType_t)10) != pdPASS)
        {
            UARTprintf("Failed to post the message, even after 10 ticks\n\r");
        }

    }

    GPIOIntRegister(GPIO_PORTL_BASE, onButtonUp);       // Register our handler function for port A
    GPIOIntTypeSet(GPIO_PORTL_BASE, GPIO_PIN_0,
                   GPIO_RISING_EDGE);                   // Configure PL0 for rising edge trigger
    GPIOIntClear(GPIO_PORTL_BASE, GPIO_PIN_0);          // Clear interrupt flag
}


/****************************************************************************
 * LEFT BUTTON PRESSED                                                      *
 ****************************************************************************/
void left_button_pressed()
{
    UARTprintf("LEFT  DEGRADED MODE -> %d\n\r",DEGRADED_MODE);
    button_status = LEFT_BUTTON_PRESSED;

    if(DEGRADED_MODE)
    {
        xTaskNotifyGive(xLeft_Motion);
    }
    else
    {
        Button_Status.msg_type = PUSH_BUTTON_SENSOR_DATA;
        Button_Status.sensor_data = LEFT_BUTTON_PRESSED;
        Button_Status.log_level = INFO;
        UARTprintf("Cart->LEFT\n\r");
        if(xQueueSend(xQueue, (void *)&Button_Status,(TickType_t)10) != pdPASS)
        {
            UARTprintf("Failed to post the message, even after 10 ticks\n\r");
        }

    }


    GPIOIntRegister(GPIO_PORTL_BASE, onButtonUp);           // Register our handler function for port A
    GPIOIntTypeSet(GPIO_PORTL_BASE, GPIO_PIN_1,
                   GPIO_RISING_EDGE);                       // Configure PL1 for rising edge trigger
    GPIOIntClear(GPIO_PORTL_BASE, GPIO_PIN_1);              // Clear interrupt flag
}


/****************************************************************************
 * FORWARD BUTTON RELEASED                                                  *
 ****************************************************************************/
void forward_button_released()
{
    button_status = FORWARD_BUTTON_RELEASED;

    if(DEGRADED_MODE)
    {
        xTaskNotifyGive(xStop_Motion);
    }
    else
    {
        Button_Status.msg_type = PUSH_BUTTON_SENSOR_DATA;
        Button_Status.sensor_data = FORWARD_BUTTON_RELEASED;
        Button_Status.log_level = INFO;

        if(xQueueSend(xQueue, (void *)&Button_Status,(TickType_t)10) != pdPASS)
        {
            UARTprintf("Failed to post the message, even after 10 ticks\n\r");
        }

    }

    GPIOIntRegister(GPIO_PORTJ_BASE, onButtonDown);         // Register our handler function for port J
    GPIOIntTypeSet(GPIO_PORTJ_BASE, GPIO_PIN_0,
                   GPIO_FALLING_EDGE);                      // Configure PJ0 for falling edge trigger
    GPIOIntClear(GPIO_PORTJ_BASE, GPIO_PIN_0);              // Clear interrupt flag
}

/****************************************************************************
 * BACKWARD BUTTON RELEASED                                                 *
 ****************************************************************************/
void backward_button_released()
{
    button_status = BACKWARD_BUTTON_RELEASED;

    if(DEGRADED_MODE)
    {
        xTaskNotifyGive(xStop_Motion);
    }
    else
    {
        Button_Status.msg_type = PUSH_BUTTON_SENSOR_DATA;
        Button_Status.sensor_data = BACKWARD_BUTTON_RELEASED;
        Button_Status.log_level = INFO;

        if(xQueueSend(xQueue, (void *)&Button_Status,(TickType_t)10) != pdPASS)
        {
            UARTprintf("Failed to post the message, even after 10 ticks\n\r");
        }

    }

    GPIOIntRegister(GPIO_PORTJ_BASE, onButtonDown);         // Register our handler function for port J
    GPIOIntTypeSet(GPIO_PORTJ_BASE, GPIO_PIN_1,
                   GPIO_FALLING_EDGE);                      // Configure PJ1 for falling edge trigger
    GPIOIntClear(GPIO_PORTJ_BASE, GPIO_PIN_1);              // Clear interrupt flag
}

/****************************************************************************
 * RIGHT BUTTON RELEASED                                                    *
 ****************************************************************************/
void right_button_released()
{
    // PL0 was interrupt cause
    //UARTprintf("PL0 Button Up\n");
    button_status = RIGHT_BUTTON_RELEASED;

    if(DEGRADED_MODE)
    {
        xTaskNotifyGive(xStop_Motion);
    }
    else
    {
        Button_Status.msg_type = PUSH_BUTTON_SENSOR_DATA;
        Button_Status.sensor_data = RIGHT_BUTTON_RELEASED;
        Button_Status.log_level = INFO;

//        strcpy(task_data.msgID , "MOTOR DRIVER:[F]");
//        task_data.TaskData = 11;
        if(xQueueSend(xQueue, (void *)&Button_Status,(TickType_t)10) != pdPASS)
        {
            UARTprintf("Failed to post the message, even after 10 ticks\n\r");
        }

    }

    GPIOIntRegister(GPIO_PORTL_BASE, onButtonDown);     // Register our handler function for port A
    GPIOIntTypeSet(GPIO_PORTL_BASE, GPIO_PIN_0,
                   GPIO_FALLING_EDGE);                  // Configure PL0 for falling edge trigger
    GPIOIntClear(GPIO_PORTL_BASE, GPIO_PIN_0);          // Clear interrupt flag
}

/****************************************************************************
 * LEFT BUTTON RELEASED                                                     *
 ****************************************************************************/
void left_button_released()
{
    // PL1 was interrupt cause
    //UARTprintf("PL1 Button Up\n");
    button_status = LEFT_BUTTON_RELEASED;

    if(DEGRADED_MODE)
    {
        xTaskNotifyGive(xStop_Motion);
    }
    else
    {
        Button_Status.msg_type = PUSH_BUTTON_SENSOR_DATA;
        Button_Status.sensor_data = LEFT_BUTTON_RELEASED;
        Button_Status.log_level = INFO;

        if(xQueueSend(xQueue, (void *)&Button_Status,(TickType_t)10) != pdPASS)
        {
            UARTprintf("Failed to post the message, even after 10 ticks\n\r");
        }

    }

    GPIOIntRegister(GPIO_PORTL_BASE, onButtonDown);         // Register our handler function for port L
    GPIOIntTypeSet(GPIO_PORTL_BASE, GPIO_PIN_1,
                   GPIO_FALLING_EDGE);                      // Configure PL1 for falling edge trigger
    GPIOIntClear(GPIO_PORTL_BASE, GPIO_PIN_1);              // Clear interrupt flag
}


/****************************************************************************
 * ENABLE PUSH BUTTON PERIPHERALS                                           *
 ****************************************************************************/
void Enable_Push_Button_Peripherals()
{
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOJ);        //enable port J
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOL);        //enable port L
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOM);        //enable port M
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOK);        //enable port K
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOQ);        //enable port Q
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOP);        //enable port P
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOH);        //enable port H
}

/****************************************************************************
 * CONFIGURE EXTERNAL PUSH BUTTONS                                          *
 ****************************************************************************/
void Configure_External_Push_Buttons()
{
    GPIOPinTypeGPIOInput(GPIO_PORTJ_BASE,GPIO_PIN_0);   //Init PJ0 as input
    GPIOPinTypeGPIOInput(GPIO_PORTJ_BASE,GPIO_PIN_1);   //Init PJ1 as input
    GPIOPinTypeGPIOInput(GPIO_PORTL_BASE,GPIO_PIN_0);   //Init PL0 as input
    GPIOPinTypeGPIOInput(GPIO_PORTL_BASE,GPIO_PIN_1);   //Init PL1 as input

    GPIOPadConfigSet(GPIO_PORTJ_BASE,GPIO_PIN_0,
      GPIO_STRENGTH_2MA, GPIO_PIN_TYPE_STD_WPU);        //Enable weak pullup resistor for PJ0
    GPIOPadConfigSet(GPIO_PORTJ_BASE,GPIO_PIN_1,
      GPIO_STRENGTH_2MA, GPIO_PIN_TYPE_STD_WPU);        //Enable weak pullup resistor for PJ1
    GPIOPadConfigSet(GPIO_PORTL_BASE,GPIO_PIN_0,
      GPIO_STRENGTH_2MA, GPIO_PIN_TYPE_STD_WPU);        //Enable weak pullup resistor for PL0
    GPIOPadConfigSet(GPIO_PORTL_BASE,GPIO_PIN_1,
      GPIO_STRENGTH_2MA, GPIO_PIN_TYPE_STD_WPU);        //Enable weak pullup resistor for PL1

    GPIOIntDisable(GPIO_PORTJ_BASE, GPIO_PIN_0);        // Disable interrupt for PJ0 (in case it was enabled)
    GPIOIntDisable(GPIO_PORTJ_BASE, GPIO_PIN_1);        // Disable interrupt for PJ1 (in case it was enabled)
    GPIOIntDisable(GPIO_PORTL_BASE, GPIO_PIN_0);        // Disable interrupt for PL0 (in case it was enabled)
    GPIOIntDisable(GPIO_PORTL_BASE, GPIO_PIN_1);        // Disable interrupt for PL1 (in case it was enabled)

    GPIOIntClear(GPIO_PORTJ_BASE, GPIO_PIN_0);          // Clear pending interrupts for PJ0
    GPIOIntClear(GPIO_PORTJ_BASE, GPIO_PIN_1);          // Clear pending interrupts for PJ1
    GPIOIntClear(GPIO_PORTL_BASE, GPIO_PIN_0);          // Clear pending interrupts for PL0
    GPIOIntClear(GPIO_PORTL_BASE, GPIO_PIN_1);          // Clear pending interrupts for PL1


    GPIOIntRegister(GPIO_PORTJ_BASE, onButtonDown);     // Register our handler function for port J
    GPIOIntRegister(GPIO_PORTL_BASE, onButtonDown);     // Register our handler function for port L


    GPIOIntTypeSet(GPIO_PORTJ_BASE, GPIO_PIN_0,
                   GPIO_FALLING_EDGE);                  // Configure PJ0 for falling edge trigger
    GPIOIntTypeSet(GPIO_PORTJ_BASE, GPIO_PIN_1,
                       GPIO_FALLING_EDGE);              // Configure PJ1 for falling edge trigger
    GPIOIntTypeSet(GPIO_PORTL_BASE, GPIO_PIN_0,
                   GPIO_FALLING_EDGE);                  // Configure PL0 for falling edge trigger
    GPIOIntTypeSet(GPIO_PORTL_BASE, GPIO_PIN_1,
                       GPIO_FALLING_EDGE);              // Configure PL1 for falling edge trigger



    GPIOIntEnable(GPIO_PORTJ_BASE, GPIO_PIN_0);         // Enable interrupt for PJ0
    GPIOIntEnable(GPIO_PORTJ_BASE, GPIO_PIN_1);         // Enable interrupt for PJ1
    GPIOIntEnable(GPIO_PORTL_BASE, GPIO_PIN_0);         // Enable interrupt for PL0
    GPIOIntEnable(GPIO_PORTL_BASE, GPIO_PIN_1);         // Enable interrupt for PL1
}

/****************************************************************************
 * CONFIGURE MOTOR DRIVER GPIO                                              *
 ****************************************************************************/
void Configure_Motor_Driver_GPIO()
{
    GPIOPinTypeGPIOOutput(GPIO_PORTM_BASE,GPIO_PIN_6);   //Init PM6 as input [FORWARD].
    GPIOPinTypeGPIOOutput(GPIO_PORTK_BASE,GPIO_PIN_7);   //Init PK7 as input [BACKWARD].
    GPIOPinTypeGPIOOutput(GPIO_PORTQ_BASE,GPIO_PIN_1);   //Init PQ1 as input [LEFT].
    GPIOPinTypeGPIOOutput(GPIO_PORTK_BASE,GPIO_PIN_6);   //Init PK6 as input [RIGHT].
    GPIOPinTypeGPIOOutput(GPIO_PORTP_BASE,GPIO_PIN_3);   //Init PP3 as input [ENABLE 1].
    GPIOPinTypeGPIOOutput(GPIO_PORTH_BASE,GPIO_PIN_1);   //Init PH1 as input [ENABLE 2].
}
