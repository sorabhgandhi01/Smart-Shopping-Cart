/*
 * Lcd_display.h
 *
 *  Created on: Apr 29, 2019
 *      Author: omrah
 */

#ifndef LCD_DISPLAY_H_
#define LCD_DISPLAY_H_

#include <stdint.h>
#include <stdbool.h>
#include <string.h>
#include "inc/hw_memmap.h"
#include "inc/hw_types.h"
#include "driverlib/debug.h"
#include "driverlib/sysctl.h"
#include "driverlib/gpio.h"


void Initialize_LCD(void);
void string_to_lcd(unsigned char *s);
void LCD_write(unsigned char,unsigned int);
void display();

void display_lcd_row1(unsigned char *s);
void display_lcd_row2(unsigned char *s);
void display_lcd_row3(unsigned char *s);
void display_lcd_row4(unsigned char *s);

#endif /* LCD_DISPLAY_H_ */
