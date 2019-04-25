/*@Filename : motor_driver_task.h
 * @Author  : Om Raheja & Sorabh Gandhi
 * @Course  : [PROJECT 2]Advanced Embedded Software Development Spring 2019
 * @Date    : 19th April 2019
 * @brief   :
 */

#ifndef MOTOR_CONTROL_TASK_H_
#define MOTOR_CONTROL_TASK_H_

#include <motor_control.h>
#include <string.h>
#include "push_button_task.h"
#include "FreeRTOS.h"
#include "queue.h"
#include "utils/uartstdio.h"
#include "task.h"
#include "push_button.h"
#include "semphr.h"


void vMotor_Driver_Task(void *pvParameters);
void vDegraded_Motor_Operation_Task(void *pvParameters);
void vForward_Motion_Task(void *pvParameters);
void vBackward_Motion_Task(void *pvParameters);
void vLeft_Motion_Task(void *pvParameters);
void vRight_Motion_Task(void *pvParameters);
void vStop_Motion_Task(void *pvParameters);

#endif /* MOTOR_CONTROL_TASK_H_ */
