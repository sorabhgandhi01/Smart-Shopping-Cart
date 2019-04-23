/*
 * motor_driver.h
 *
 *  Created on: Apr 22, 2019
 *      Author: omrah
 */

#ifndef MOTOR_DRIVER_H_
#define MOTOR_DRIVER_H_

#include "push_button_task.h"
#include "FreeRTOS.h"
#include "queue.h"
#include "utils/uartstdio.h"
#include "task.h"


void vMotor_Driver_Task(void *pvParameters);
void alert_task(void *pvParameters);
#endif /* MOTOR_DRIVER_H_ */
