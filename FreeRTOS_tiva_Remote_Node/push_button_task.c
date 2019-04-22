/*
 * push_button_task.c
 *
 *  Created on: Apr 19, 2019
 *      Author: omrah
 *@References :https://e2e.ti.com/support/microcontrollers/other/f/908/t/332605
 */

#include "push_button_task.h"

void onButtonDown(void);
void onButtonUp(void);

void onButtonDown(void) {
    if (GPIOIntStatus(GPIO_PORTJ_BASE, false) & GPIO_PIN_0) {
        // PJ0 was interrupt cause
        UARTprintf("PJ0 Button Down\n");
        GPIOIntRegister(GPIO_PORTJ_BASE, onButtonUp);   // Register our handler function for port J
        GPIOIntTypeSet(GPIO_PORTJ_BASE, GPIO_PIN_0,
        GPIO_RISING_EDGE);          // Configure PJ0 for rising edge trigger
        GPIOIntClear(GPIO_PORTJ_BASE, GPIO_PIN_0);  // Clear interrupt flag
    }

    if (GPIOIntStatus(GPIO_PORTJ_BASE, false) & GPIO_PIN_1) {
            // PJ1 was interrupt cause
            UARTprintf("PJ1 Button Down\n");
            GPIOIntRegister(GPIO_PORTJ_BASE, onButtonUp);   // Register our handler function for port J
            GPIOIntTypeSet(GPIO_PORTJ_BASE, GPIO_PIN_1,
            GPIO_RISING_EDGE);          // Configure PJ1 for rising edge trigger
            GPIOIntClear(GPIO_PORTJ_BASE, GPIO_PIN_1);  // Clear interrupt flag
        }


    if (GPIOIntStatus(GPIO_PORTL_BASE, false) & GPIO_PIN_0) {
            // PL0 was interrupt cause
            UARTprintf("PL0 Button Down\n");
            GPIOIntRegister(GPIO_PORTL_BASE, onButtonUp);   // Register our handler function for port A
            GPIOIntTypeSet(GPIO_PORTL_BASE, GPIO_PIN_0,
            GPIO_RISING_EDGE);          // Configure PL0 for rising edge trigger
            GPIOIntClear(GPIO_PORTL_BASE, GPIO_PIN_0);  // Clear interrupt flag
        }

    if (GPIOIntStatus(GPIO_PORTL_BASE, false) & GPIO_PIN_1) {
        // PL1 was interrupt cause
        UARTprintf("PL1 Button Down\n");
        GPIOIntRegister(GPIO_PORTL_BASE, onButtonUp);   // Register our handler function for port A
        GPIOIntTypeSet(GPIO_PORTL_BASE, GPIO_PIN_1,
        GPIO_RISING_EDGE);          // Configure PL1 for rising edge trigger
        GPIOIntClear(GPIO_PORTL_BASE, GPIO_PIN_1);  // Clear interrupt flag
    }

}

void onButtonUp(void) {
    if (GPIOIntStatus(GPIO_PORTJ_BASE, false) & GPIO_PIN_0) {
        // PJ0 was interrupt cause
        UARTprintf("PJ0 Button Up\n");
        GPIOIntRegister(GPIO_PORTJ_BASE, onButtonDown); // Register our handler function for port J
        GPIOIntTypeSet(GPIO_PORTJ_BASE, GPIO_PIN_0,
            GPIO_FALLING_EDGE);         // Configure PJ0 for falling edge trigger
        GPIOIntClear(GPIO_PORTJ_BASE, GPIO_PIN_0);  // Clear interrupt flag
    }

    if (GPIOIntStatus(GPIO_PORTJ_BASE, false) & GPIO_PIN_1) {
        // PJ1 was interrupt cause
        UARTprintf("PJ1 Button Up\n");
        GPIOIntRegister(GPIO_PORTJ_BASE, onButtonDown); // Register our handler function for port J
        GPIOIntTypeSet(GPIO_PORTJ_BASE, GPIO_PIN_1,
            GPIO_FALLING_EDGE);         // Configure PJ1 for falling edge trigger
        GPIOIntClear(GPIO_PORTJ_BASE, GPIO_PIN_1);  // Clear interrupt flag
    }

    if (GPIOIntStatus(GPIO_PORTL_BASE, false) & GPIO_PIN_0) {
            // PL0 was interrupt cause
            UARTprintf("PL0 Button Up\n");
            GPIOIntRegister(GPIO_PORTL_BASE, onButtonDown); // Register our handler function for port A
            GPIOIntTypeSet(GPIO_PORTL_BASE, GPIO_PIN_0,
                GPIO_FALLING_EDGE);         // Configure PL0 for falling edge trigger
            GPIOIntClear(GPIO_PORTL_BASE, GPIO_PIN_0);  // Clear interrupt flag
        }

    if (GPIOIntStatus(GPIO_PORTL_BASE, false) & GPIO_PIN_1) {
        // PL1 was interrupt cause
        UARTprintf("PL1 Button Up\n");
        GPIOIntRegister(GPIO_PORTL_BASE, onButtonDown); // Register our handler function for port L
        GPIOIntTypeSet(GPIO_PORTL_BASE, GPIO_PIN_1,
            GPIO_FALLING_EDGE);         // Configure PL1 for falling edge trigger
        GPIOIntClear(GPIO_PORTL_BASE, GPIO_PIN_1);  // Clear interrupt flag
    }


}

/* Push Button task */
void vPush_Button_Task(void *pvParameters)
{
    UARTprintf("Push Button Task!\n\r");

    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOJ);        //enable port J
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOL);        //enable port L


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
