/*@Filename : ultrasonic_sensor.h
 * @Author  : Om Raheja & Sorabh Gandhi
 * @Course  : [PROJECT 2]Advanced Embedded Software Development Spring 2019
 * @Date    : 19th April 2019
 * @brief   :
 */

#ifndef ULTRASONIC_SENSOR_H_
#define ULTRASONIC_SENSOR_H_


/****************************************************************************
 * HEADER FILES                                                             *
 ****************************************************************************/
#include <stdbool.h>
#include "utils/uartstdio.h"
#include "driverlib/gpio.h"
#include "driverlib/inc/hw_memmap.h"
#include "sysctl.h"
#include "driverlib/inc/hw_timer.h"
#include "driverlib/timer.h"
#include "driverlib/inc/hw_types.h"
#include "driverlib/interrupt.h"


/****************************************************************************
 * FUNCTION PROTOTYPES                                                      *
 ****************************************************************************/
void UltraSoniC_IRQ_Handler();
void getDistance();
void ultrasonic_sensor_init();

#endif /* ULTRASONIC_SENSOR_H_ */
