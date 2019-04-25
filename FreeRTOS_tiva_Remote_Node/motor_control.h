/*@Filename : motor_driver.h
 * @Author  : Om Raheja & Sorabh Gandhi
 * @Course  : [PROJECT 2]Advanced Embedded Software Development Spring 2019
 * @Date    : 19th April 2019
 * @brief   :
 */

#ifndef MOTOR_CONTROL_H_
#define MOTOR_CONTROL_H_

#include <stdbool.h>
#include "utils/uartstdio.h"
#include "driverlib/gpio.h"
#include "driverlib/inc/hw_memmap.h"



void FORWARD();
void BACKWARD();
void RIGHT();
void LEFT();
void STOP();

#endif /* MOTOR_CONTROL_H_ */
