/*
 * Lcd_display.c
 *
 *  Created on: Apr 29, 2019
 *      Author: omrah
 * @Reference : https://e2e.ti.com/support/microcontrollers/other/f/908/t/631032
 */

#include "Lcd_display.h"

//#define ROW1 0x80
//#define ROW2 0XC0
//#define ROW3 0X94
//#define ROW4 0XD4

void Initialize_LCD(void);
void string_to_lcd(unsigned char *s);
void LCD_write(unsigned char,unsigned int);


void display()
{
SysCtlClockFreqSet((SYSCTL_XTAL_25MHZ | SYSCTL_OSC_MAIN | SYSCTL_USE_PLL | SYSCTL_CFG_VCO_480), 120000000);
SysCtlDelay(100000);//2ms
SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOE);
SysCtlDelay(100000);
SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOB);
SysCtlDelay(100000);
GPIOPinTypeGPIOOutput(GPIO_PORTE_BASE, GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3);
SysCtlDelay(100000);
GPIOPinTypeGPIOOutput(GPIO_PORTB_BASE, GPIO_PIN_4|GPIO_PIN_5);
SysCtlDelay(100000);

GPIOPinWrite(GPIO_PORTE_BASE, GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3, 0x00);
SysCtlDelay(2000000);//20ms
Initialize_LCD();

/*
LCD_write(0X80,0);
string_to_lcd("Hello");
LCD_write(0XC0,0);
string_to_lcd("TI E2E COMMUNITY");
LCD_write(0X94,0);
string_to_lcd("HI cb1 & Charles");
LCD_write(0XD4,0);
string_to_lcd("THANK YOU !!");
*/
//SysCtlDelay(0XFFFFFF00);


//while(1){
//}
}

void Initialize_LCD(void)
{
GPIOPinWrite(GPIO_PORTB_BASE, GPIO_PIN_4, 0xEF); //RS PIN LOW
SysCtlDelay(5000);
GPIOPinWrite(GPIO_PORTB_BASE, GPIO_PIN_5, 0xDF); //EN PIN LOW
SysCtlDelay(5000);

LCD_write(0x33,0);
SysCtlDelay(5000);
LCD_write(0x32,0);
SysCtlDelay(5000);
LCD_write(0x06,0);
SysCtlDelay(5000);
LCD_write(0x0E,0);
SysCtlDelay(5000);
LCD_write(0x28,0);
SysCtlDelay(5000);
LCD_write(0X01,0);
SysCtlDelay(10000000);
}

void LCD_write(unsigned char data,unsigned int RS)
{
if(RS==0)
GPIOPinWrite(GPIO_PORTB_BASE, GPIO_PIN_4, 0xEF); //Command
else
GPIOPinWrite(GPIO_PORTB_BASE, GPIO_PIN_4, 0xFF); //Data

SysCtlDelay(5000);
GPIOPinWrite(GPIO_PORTB_BASE, GPIO_PIN_5, 0xFF);
SysCtlDelay(5000);

GPIOPinWrite(GPIO_PORTE_BASE, GPIO_PIN_3|GPIO_PIN_2|GPIO_PIN_1|GPIO_PIN_0, ((data & 0XF0)>>4));
SysCtlDelay(5000);
GPIOPinWrite(GPIO_PORTB_BASE, GPIO_PIN_5, 0xDF);
SysCtlDelay(5000);

SysCtlDelay(5000);
GPIOPinWrite(GPIO_PORTB_BASE, GPIO_PIN_5, 0xFF);
SysCtlDelay(5000);

GPIOPinWrite(GPIO_PORTE_BASE, GPIO_PIN_3|GPIO_PIN_2|GPIO_PIN_1|GPIO_PIN_0, (data & 0X0F));
SysCtlDelay(5000);
GPIOPinWrite(GPIO_PORTB_BASE, GPIO_PIN_5, 0xDF);
SysCtlDelay(5000);
}

void string_to_lcd(unsigned char *s)
{
    unsigned int slen;
    slen=strlen(s);
    while(slen>0)
    {
        unsigned char D=*s;
        LCD_write(*s,1);
        SysCtlDelay(1000000);
        slen--;
        s++;
    }
}


void display_lcd_row1(unsigned char *s)
{
    LCD_write(0X80,0);
    string_to_lcd(s);
//    SysCtlDelay(0XFFFFFF00);
}

void display_lcd_row2(unsigned char *s)
{
    LCD_write(0XC0,0);
    string_to_lcd(s);
//    SysCtlDelay(0XFFFFFF00);

}

void display_lcd_row3(unsigned char *s)
{
    LCD_write(0X90,0);
    string_to_lcd(s);
//    SysCtlDelay(0XFFFFFF00);
}

void display_lcd_row4(unsigned char *s)
{
    LCD_write(0XD0,0);
    string_to_lcd(s);
//    SysCtlDelay(0XFFFFFF00);
}
