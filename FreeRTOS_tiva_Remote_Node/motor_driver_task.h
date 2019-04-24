/*@Filename : motor_driver_task.h
 * @Author  : Om Raheja & Sorabh Gandhi
 * @Course  : [PROJECT 2]Advanced Embedded Software Development Spring 2019
 * @Date    : 19th April 2019
 * @brief   :
 */

#ifndef MOTOR_DRIVER_TASK_H_
#define MOTOR_DRIVER_TASK_H_


#include "push_button_task.h"
#include "FreeRTOS.h"
#include "queue.h"
#include "utils/uartstdio.h"
#include "task.h"
#include "push_button.h"


void vMotor_Driver_Task(void *pvParameters);
void alert_task(void *pvParameters);



#endif /* MOTOR_DRIVER_TASK_H_ */
