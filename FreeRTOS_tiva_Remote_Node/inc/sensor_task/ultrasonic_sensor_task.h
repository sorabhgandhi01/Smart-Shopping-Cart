/*@Filename : ultrasonic_sensor_task.h
 * @Author  : Om Raheja & Sorabh Gandhi
 * @Course  : [PROJECT 2]Advanced Embedded Software Development Spring 2019
 * @Date    : 19th April 2019
 * @brief   :
 */

#ifndef ULTRASONIC_SENSOR_TASK_H_
#define ULTRASONIC_SENSOR_TASK_H_

/****************************************************************************
 * HEADER FILES                                                             *
 ****************************************************************************/
#include <stdint.h>
#include <stdbool.h>
#include <string.h>
#include "utils/uartstdio.h"
#include "driverlib/uart.h"
#include "driverlib/sysctl.h"
#include "driverlib/rom.h"
#include "driverlib/pin_map.h"
#include "driverlib/timer.h"
#include "driverlib/interrupt.h"
#include "driverlib/inc/hw_timer.h"
#include "portMacro.h"
#include "driverlib/inc/hw_memmap.h"
#include "FreeRTOS.h"
#include "task.h"
#include "ultrasonic_sensor.h"
#include "semphr.h"
#include "helper.h"



/****************************************************************************
 * FUNCATION PROTOTYPES                                                     *
 ****************************************************************************/
void vUltraSonic_Task(void *pvParameters);
void UltraSoniC_IRQ_Handler();
void getDistance();
void ultrasonic_sensor_init();



#endif /* ULTRASONIC_SENSOR_TASK_H_ */
