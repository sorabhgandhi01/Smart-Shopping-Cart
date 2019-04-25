/*@Filename : push_button_task.h
 * @Author  : Om Raheja & Sorabh Gandhi
 * @Course  : [PROJECT 2]Advanced Embedded Software Development Spring 2019
 * @Date    : 19th April 2019
 * @brief   :
 *@References : https://e2e.ti.com/support/microcontrollers/other/f/908/t/332605
 */


#ifndef PUSH_BUTTON_TASK_H_
#define PUSH_BUTTON_TASK_H_


/****************************************************************************
 * HEADER FILES                                                             *
 ****************************************************************************/
#include <stdint.h>
#include <stdbool.h>
#include "utils/uartstdio.h"
#include "driverlib/sysctl.h"
#include "FreeRTOS.h"
#include "queue.h"
#include "push_button.h"

/****************************************************************************
 * FUNCTION PROTOTYPES                                                      *
 ****************************************************************************/

/********************************************
 * vPUSH_BUTTON_TASK                        *
 * ******************************************/
/*@brief: Handles Push Button events.
 *
 *@param: void *pvParameters
 *
 *@return: none
 * */
void vPush_Button_Task(void *pvParameters);

#endif /* PUSH_BUTTON_TASK_H_ */
