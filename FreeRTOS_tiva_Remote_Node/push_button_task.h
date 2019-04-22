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

void vPush_Button_Task(void *pvParameters);

#endif /* PUSH_BUTTON_TASK_H_ */
