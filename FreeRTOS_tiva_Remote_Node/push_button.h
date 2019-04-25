/*@Filename : push_button.h
 * @Author  : Om Raheja & Sorabh Gandhi
 * @Course  : [PROJECT 2]Advanced Embedded Software Development Spring 2019
 * @Date    : 24th April 2019
 */

#ifndef PUSH_BUTTON_H_
#define PUSH_BUTTON_H_

/****************************************************************************
 * HEADER FILES                                                             *
 ****************************************************************************/
#include <stdbool.h>
#include "driverlib/gpio.h"
#include "driverlib/inc/hw_memmap.h"
//#include "driverlib/gpio.h"
#include "utils/uartstdio.h"
#include "driverlib/sysctl.h"
#include "FreeRTOS.h"
#include "task.h"

/****************************************************************************
 * EXPORTED GLOBAL VARIBALES                                                *
 ****************************************************************************/
extern TaskHandle_t xAlert;
extern TaskHandle_t xLeft_Motion;
extern TaskHandle_t xStop_Motion;
extern TaskHandle_t xRight_Motion;
extern TaskHandle_t xForward_Motion;
extern TaskHandle_t xBackward_Motion;

/****************************************************************************
 * ENUMERATIONS                                                             *
 ****************************************************************************/
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


/****************************************************************************
 * FUNCTION PROTOTYPES                                                      *
 ****************************************************************************/
void onButtonDown(void);
void onButtonUp(void);
void forward_button_pressed();
void forward_button_released();
void backward_button_pressed();
void backward_button_released();
void left_button_pressed();
void left_button_released();
void right_button_pressed();
void right_button_released();
void Enable_Push_Button_Peripherals();
void Configure_External_Push_Buttons();
void Configure_Motor_Driver_GPIO();


#endif /* PUSH_BUTTON_H_ */
