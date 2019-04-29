/*
 * uart.c
 *
 *  Created on: 19-Apr-2019
 *      Author: Sorabh
 */


#include "my_uart.h"
#include "main.h"

void init_RX_serial(void)
{
    ROM_SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOB);
    ROM_SysCtlPeripheralEnable(SYSCTL_PERIPH_UART1);

    ROM_GPIOPinConfigure(GPIO_PB0_U1RX);
    ROM_GPIOPinConfigure(GPIO_PB1_U1TX);

    ROM_GPIOPinTypeUART(GPIO_PORTB_BASE, GPIO_PIN_0 | GPIO_PIN_1);
    ROM_UARTConfigSetExpClk(UART1_BASE, SYSTEM_CLOCK, 115200,
                            (UART_CONFIG_WLEN_8 |
                                    UART_CONFIG_STOP_ONE |
                                        UART_CONFIG_PAR_NONE));
}


void init_TX_serial(void)
{
    ROM_SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOA);
    ROM_SysCtlPeripheralEnable(SYSCTL_PERIPH_UART2);

    ROM_GPIOPinConfigure(GPIO_PA6_U2RX);
    ROM_GPIOPinConfigure(GPIO_PA7_U2TX);

    ROM_GPIOPinTypeUART(GPIO_PORTA_BASE, GPIO_PIN_6 | GPIO_PIN_7);
    ROM_UARTConfigSetExpClk(UART2_BASE, SYSTEM_CLOCK, 115200,
                                (UART_CONFIG_WLEN_8 |
                                        UART_CONFIG_STOP_ONE |
                                            UART_CONFIG_PAR_NONE));

//    ROM_IntMasterEnable();
//    ROM_IntEnable(INT_UART2);
//    ROM_UARTIntEnable(UART2_BASE, UART_INT_RX | UART_INT_RT);
}


void UART_send(char* ptr, int len)
{
    while(len != 0)
    {
        UARTCharPut(UART2_BASE, *ptr);
        ptr++;
        len--;
    }
}


//*****************************************************************************
//
// The UART interrupt handler.
//
//*****************************************************************************
void UARTIntHandler(void)
{
    uint32_t ui32Status;

    //
    // Get the interrrupt status.
    //
    ui32Status = ROM_UARTIntStatus(UART2_BASE, true);

    //
    // Clear the asserted interrupts.
    //
    ROM_UARTIntClear(UART2_BASE, ui32Status);

    //
    // Loop while there are characters in the receive FIFO.
    //
    while(ROM_UARTCharsAvail(UART2_BASE))
    {
        //
        // Read the next character from the UART and write it back to the UART.
        //
        uint8_t data = ROM_UARTCharGetNonBlocking(UART2_BASE);

        //
        // Delay for 1 millisecond.  Each SysCtlDelay is about 3 clocks.
        //
        SysCtlDelay(SYSTEM_CLOCK / (1000 * 3));

        UARTprintf("Data = %x\r\n", data);

    }
}
