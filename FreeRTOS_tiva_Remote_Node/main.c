/*@Filename : main.c
 * @Author  : Om Raheja & Sorabh Gandhi
 * @Course  : [PROJECT 2]Advanced Embedded Software Development Spring 2019
 * @Date    : 24th April 2019
 * @brief   : Initializes system clock, GPIO pins for LaunchPad, I2C. Set up UART
 *            and create all tasks.
 */

/****************************************************************************
 * HEADER FILES                                                             *
 ****************************************************************************/
#include <stdint.h>
#include <stdbool.h>
#include "main.h"
#include "drivers/pinout.h"
#include "utils/uartstdio.h"


/****************************************************************************
 * TIVAWARE INCLUDES                                                        *
 ****************************************************************************/
#include "driverlib/sysctl.h"
#include "driverlib/debug.h"
#include "driverlib/rom.h"
#include "driverlib/rom_map.h"


/****************************************************************************
 * FREERTOS INCLUDES                                                        *
 ****************************************************************************/
#include "FreeRTOSConfig.h"
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "semphr.h"
#include "helper.h"

/****************************************************************************
 * USER DEFINED HEADER FILES                                                *
 ****************************************************************************/
#include "gesture_sensor_task.h"
#include "push_button_task.h"
#include "ultrasonic_sensor_task.h"
#include "motor_driver_task.h"
#include "send_to_bbg_task.h"

/****************************************************************************
 * GLOBAL VARIABLES                                                         *
 ****************************************************************************/
uint32_t output_clock_rate_hz;
TaskHandle_t Gesture_Task;
TaskHandle_t xAlert = NULL;

SemaphoreHandle_t xMutex;
QueueHandle_t xQueue;
/****************************************************************************
 * FUNCTION NAME : MAIN                                                     *
 ****************************************************************************/
int main(void)
{
    /* Initialize system clock to 120 MHz */
    output_clock_rate_hz = ROM_SysCtlClockFreqSet((SYSCTL_XTAL_25MHZ | SYSCTL_OSC_MAIN | SYSCTL_USE_PLL | SYSCTL_CFG_VCO_480),SYSTEM_CLOCK);
    ASSERT(output_clock_rate_hz == SYSTEM_CLOCK);

    // Initialize the GPIO pins for the Launchpad
    PinoutSet(false, false);

    /* Initialize I2C */
    I2C_Init();

    /* Set up the UART which is connected to the virtual COM port */
    UARTStdioConfig(0, 115200, SYSTEM_CLOCK);

    xMutex = xSemaphoreCreateMutex();

    /* Create Message Queue */
    xQueue = xQueueCreate(30,sizeof(TaskData_t));

    /* Check if Queue has been created */
    if( xQueue == NULL )
    {
       UARTprintf("\r\nQueue was not created!");
    }


    /* Create Alert Task */
    xTaskCreate(send_to_bbg_task, (const portCHAR *)"SENDER TASK",
                configMINIMAL_STACK_SIZE, NULL, 1, NULL);


    /* Create Alert Task */
    xTaskCreate(alert_task, (const portCHAR *)"ALERT TASK",
                configMINIMAL_STACK_SIZE, NULL, 1, &xAlert);


    /* Create Push Button Task */
    xTaskCreate(vPush_Button_Task, (const portCHAR *)"Push Button",
                configMINIMAL_STACK_SIZE, NULL, 1, NULL);

    /* Create Motor Driver Task */
    xTaskCreate(vMotor_Driver_Task, (const portCHAR *)"Motor Driver Task",
                configMINIMAL_STACK_SIZE, NULL, 1, NULL);


    /* Create Ultrasonic Distance Sensor Task */
    xTaskCreate(vUltraSonic_Task, (const portCHAR *)"Distance",
                configMINIMAL_STACK_SIZE, NULL, 1, NULL);

    /* Create Gesture Sensor Task */
    xTaskCreate(vGesture_Sensor_Task, (const portCHAR *)"Gesture",
                configMINIMAL_STACK_SIZE, NULL, 1, &Gesture_Task);

    vTaskStartScheduler();
    return 0;
}


/****************************************************************************
 * ASSERT() ERROR FUNCTION                                                  *
 ****************************************************************************/
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
/****************************************************************************
 * EOF                                                                      *
 ****************************************************************************/
