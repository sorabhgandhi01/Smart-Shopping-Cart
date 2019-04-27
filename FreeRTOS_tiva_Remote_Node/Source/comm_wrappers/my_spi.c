/*
 * my_spi.c
 *
 *  Created on: 14-Apr-2019
 *      Author: Sorabh
 */

#include "my_spi.h"
#include <stdint.h>


void SPI_Pin_Configure(uint32_t clk, uint32_t ss, uint32_t rx, uint32_t tx)
{
    GPIOPinConfigure(clk);
    GPIOPinConfigure(ss);
    GPIOPinConfigure(rx);
    GPIOPinConfigure(tx);
}


/*
 * For Port SSI0_BASE, the pins on board are,
 * PA2 - CLK
 * PA3 - SS
 * PA4 - Rx
 * PA5 - Tx
 *
 * For Port SSI1_BASE, the pins on board are,
 * PB5 - CLK
 * PB4 - SS
 * PE5 - Rx
 * PE4 - Tx
 *
 * For Port SSI2_BASE, the pins on board are,
 * PD3 - CLK
 * PD2 - SS
 * PD0 - Rx
 * PD1 - Tx
 */
void SPI_Pin_Init(uint32_t SPI_port)
{
    if (SPI_port == SSI0_BASE) {
        MAP_SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOA);

        SPI_Pin_Configure(GPIO_PA2_SSI0CLK,
                          GPIO_PA3_SSI0FSS,
                          GPIO_PA4_SSI0XDAT0,
                          GPIO_PA5_SSI0XDAT1);

        GPIOPinTypeGPIOOutput(GPIO_PORTC_BASE, GPIO_PIN_6);

        GPIOPinTypeSSI(GPIO_PORTA_BASE,
                       GPIO_PIN_2 | GPIO_PIN_3 | GPIO_PIN_4 | GPIO_PIN_5);
    }
    else if (SPI_port == SSI1_BASE) {
        MAP_SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOB);
        MAP_SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOE);

        SPI_Pin_Configure(GPIO_PB5_SSI1CLK,
                          GPIO_PB4_SSI1FSS,
                          GPIO_PE5_SSI1XDAT1,
                          GPIO_PE4_SSI1XDAT0);

        GPIOPinTypeSSI(GPIO_PORTB_BASE,
                       GPIO_PIN_4 | GPIO_PIN_5);

        GPIOPinTypeSSI(GPIO_PORTE_BASE,
                               GPIO_PIN_4 | GPIO_PIN_5);
    }
    else if (SPI_port == SSI2_BASE) {
        MAP_SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOD);

        SPI_Pin_Configure(GPIO_PD3_SSI2CLK,
                          GPIO_PD2_SSI2FSS,
                          GPIO_PD0_SSI2XDAT1,
                          GPIO_PD1_SSI2XDAT0);

        GPIOPinTypeSSI(GPIO_PORTD_BASE,
                       GPIO_PIN_0 | GPIO_PIN_1 | GPIO_PIN_2 | GPIO_PIN_3);
    }
}


void SPI_Clock_Init(uint32_t SPI_port, uint32_t SPI_clock, uint32_t sysclock)
{
    MAP_SysCtlPeripheralEnable(SPI_clock);
    SSIClockSourceGet(SPI_port);

    SSIConfigSetExpClk(SPI_port, sysclock, SSI_FRF_MOTO_MODE_0,
                       SSI_MODE_MASTER, 1000000, 8);
}


void SPI_Clock_deinit(uint32_t SPI_clock)
{
    MAP_SysCtlPeripheralDisable(SPI_clock);
}


void SPI_enable(uint32_t SPI_port)
{
    SPI_Pin_Init(SPI_port);
    SSIEnable(SPI_port);
}


void SPI_disable(uint32_t SPI_port, uint32_t SPI_clock)
{
    SSIDisable(SPI_port);
    SPI_Clock_deinit(SPI_clock);
}


//void SPI_clear_pending_RxTransaction(uint32_t SPI_port)
//{
//    uint8_t data;
//    while(SSIDataGetNonBlocking(SPI_port, &data));
//}


void SPI_clear_pending_TxTransaction(uint32_t SPI_port)
{
    while(SSIBusy(SPI_port));
}


void SPI_Blocking_write_byte(uint32_t SPI_port, uint8_t data)
{
    uint32_t wr_data = ((uint32_t)data & 0x000000FF);
    SPI_clear_pending_TxTransaction(SPI_port);
    SSIDataPut(SPI_port, wr_data);
    SPI_clear_pending_TxTransaction(SPI_port);
}


void SPI_NonBlocking_write_byte(uint32_t SPI_port, uint8_t data)
{
    uint32_t wr_data = ((uint32_t)data & 0x000000FF);
    SPI_clear_pending_TxTransaction(SPI_port);
    SSIDataPutNonBlocking(SPI_port, wr_data);
    SPI_clear_pending_TxTransaction(SPI_port);
}


void SPI_Blocking_write_bytes(uint32_t SPI_port, uint8_t *data, size_t length)
{
    int i = 0;
    for (i = 0; i < length; i++)
    {
        SPI_Blocking_write_byte(SPI_port, *(data + i));
    }
}


void SPI_Blocking_read_byte(uint32_t SPI_port, uint8_t *data)
{
    uint32_t rd_data;
    SSIDataGet(SPI_port, &rd_data);
    *data = ((uint8_t)(rd_data & 0xFF));
}


void SPI_NonBlocking_read_byte(uint32_t SPI_port, uint8_t *data)
{
    uint32_t rd_data;
    SSIDataGetNonBlocking(SPI_port, &rd_data);
    *data = ((uint8_t)(rd_data & 0xFF));
}


//void SPI_Blocking_read_bytes(uint32_t SPI_port, uint8_t *data, size_t length)
//{
//
//}
