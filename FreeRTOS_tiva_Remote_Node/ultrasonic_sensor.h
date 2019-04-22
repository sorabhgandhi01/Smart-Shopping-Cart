/*
 * ultrasonic_sensor.h
 *
 *  Created on: Apr 20, 2019
 *      Author: omrah
 */

#ifndef ULTRASONIC_SENSOR_H_
#define ULTRASONIC_SENSOR_H_


#include <stdint.h>
#include <stdbool.h>
#include "utils/uartstdio.h"
#include "driverlib/gpio.h"
#include "driverlib/uart.h"
#include "driverlib/sysctl.h"
#include "driverlib/rom.h"
#include "driverlib/pin_map.h"
#include "driverlib/inc/hw_memmap.h"
#include "driverlib/timer.h"
#include "driverlib/interrupt.h"
#include "driverlib/inc/hw_timer.h"
#include "portMacro.h"
#include "driverlib/inc/hw_types.h"
#include "driverlib/inc/hw_memmap.h"
#include "FreeRTOS.h"
#include "task.h"

void vUltraSonic_Task(void *pvParameters);
void UltraSoniC_IRQ_Handler();
void getDistance();
void ultrasonic_sensor_init();

#endif /* ULTRASONIC_SENSOR_H_ */
