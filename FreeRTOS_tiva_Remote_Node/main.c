/* FreeRTOS 8.2 Tiva Demo
 *
 * main.c
 *
 * Om Raheja
 *
 * This is a simple demonstration project of FreeRTOS 8.2 on the Tiva Launchpad
 * EK-TM4C1294XL.  TivaWare driverlib sourcecode is included.
 */

#include <stdint.h>
#include <stdbool.h>
#include "main.h"
#include "drivers/pinout.h"
#include "utils/uartstdio.h"


// TivaWare includes
#include "driverlib/sysctl.h"
#include "driverlib/debug.h"
#include "driverlib/rom.h"
#include "driverlib/rom_map.h"

// FreeRTOS includes
#include "FreeRTOSConfig.h"
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"

/* My Headers */
#include "gesture_sensor.h"
#include "push_button_task.h"
#include "ultrasonic_sensor.h"


/* Global variables */
uint32_t output_clock_rate_hz;

TaskHandle_t Gesture_Task;

// Main function
int main(void)
{
    // Initialize system clock to 120 MHz
    //uint32_t output_clock_rate_hz;
    output_clock_rate_hz = ROM_SysCtlClockFreqSet((SYSCTL_XTAL_25MHZ | SYSCTL_OSC_MAIN | SYSCTL_USE_PLL | SYSCTL_CFG_VCO_480),SYSTEM_CLOCK);
    ASSERT(output_clock_rate_hz == SYSTEM_CLOCK);

    // Initialize the GPIO pins for the Launchpad
    PinoutSet(false, false);


    /* Initialize I2C */
        I2C_Init();

    // Set up the UART which is connected to the virtual COM port
    UARTStdioConfig(0, 115200, SYSTEM_CLOCK);


//    // Create Push Button Task
//    xTaskCreate(vPush_Button_Task, (const portCHAR *)"Push Button",
//                    configMINIMAL_STACK_SIZE, NULL, 1, NULL);

    // Create Ultrasonic Distance Sensor Task
    xTaskCreate(vUltraSonic_Task, (const portCHAR *)"Distance",
                        configMINIMAL_STACK_SIZE, NULL, 1, NULL);

//    // Create Gesture Sensor Task
//    xTaskCreate(vGesture_Sensor_Task, (const portCHAR *)"Gesture",
//                configMINIMAL_STACK_SIZE, NULL, 1, &Gesture_Task);

    vTaskStartScheduler();
    return 0;
}


/*  ASSERT() Error function
 *
 *  failed ASSERTS() from driverlib/debug.h are executed in this function
 */
void __error__(char *pcFilename, uint32_t ui32Line)
{
    // Place a breakpoint here to capture errors until logging routine is finished
    while (1)
    {
    }
}
