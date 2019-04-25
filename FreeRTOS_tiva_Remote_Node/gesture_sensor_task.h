/*
 * gesture_sensor_task.h
 *
 *  Created on: Apr 24, 2019
 *      Author: omrah
 */

#ifndef GESTURE_SENSOR_TASK_H_
#define GESTURE_SENSOR_TASK_H_

/* Header Files */
#include <stdbool.h>
#include <string.h>
#include "utils/uartstdio.h"
#include "I2C.h"
#include "FreeRTOS.h"
#include "task.h"
#include "portmacro.h"
#include "motor_driver.h"
#include "gesture_sensor.h"
#include "semphr.h"
#include "helper.h"

/* Gesture sensor task */
void vGesture_Sensor_Task(void *pvParameters);

#endif /* GESTURE_SENSOR_TASK_H_ */
