/*
 * push_button_task.h
 *
 *  Created on: Apr 19, 2019
 *      Author: omrah
 */

#ifndef PUSH_BUTTON_TASK_H_
#define PUSH_BUTTON_TASK_H_

#include <stdint.h>
#include <stdbool.h>
#include "utils/uartstdio.h"
#include "driverlib/gpio.h"
#include "driverlib/sysctl.h"
#include "driverlib/inc/hw_memmap.h"
#include "FreeRTOS.h"
#include "queue.h"
#include "task.h"

typedef enum
{
    FORWARD_BUTTON_PRESSED,
    FORWARD_BUTTON_RELEASED,
    BACKWARD_BUTTON_PRESSED,
    BACKWARD_BUTTON_RELEASED,
    RIGHT_BUTTON_PRESSED,
    RIGHT_BUTTON_RELEASED,
    LEFT_BUTTON_PRESSED,
    LEFT_BUTTON_RELEASED
}button_status_t;


void vPush_Button_Task(void *pvParameters);

#endif /* PUSH_BUTTON_TASK_H_ */
