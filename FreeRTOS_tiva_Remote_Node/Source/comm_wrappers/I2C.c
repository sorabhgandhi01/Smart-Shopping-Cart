/*
 * I2C.c
 *
 *  Created on: Apr 18, 2019
 *      Author: omrah
 */

#include "../../inc/comm_wrappers/I2C.h"


/* Exported Global variables */
extern uint32_t output_clock_rate_hz;

/* I2C Initialization Function */
void I2C_Init(void)
{
    /* enable GPIO peripheral that contains I2C 0 */
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOB);
    while(!SysCtlPeripheralReady(SYSCTL_PERIPH_GPIOB));

    /* enable I2C module 0 */
        SysCtlPeripheralDisable(SYSCTL_PERIPH_I2C0);

        /* reset module */
        SysCtlPeripheralReset(SYSCTL_PERIPH_I2C0);

        SysCtlPeripheralEnable(SYSCTL_PERIPH_I2C0);

        while(!SysCtlPeripheralReady(SYSCTL_PERIPH_I2C0));

    /* Configure the pin muxing for I2C0 functions on port PB2 and PB3 */
    GPIOPinConfigure(GPIO_PB2_I2C0SCL);
    GPIOPinConfigure(GPIO_PB3_I2C0SDA);

    /* Select the I2C function for these pins. */
    GPIOPinTypeI2CSCL(GPIO_PORTB_BASE, GPIO_PIN_2);
    GPIOPinTypeI2C(GPIO_PORTB_BASE, GPIO_PIN_3);

    /* Enable and initialize the I2C0 master module.  Use the system clock for
     * the I2C0 module.  The last parameter sets the I2C data transfer rate.
     * If false the data rate is set to 100kbps and if true the data rate will
     * be set to 400kbps. */
    I2CMasterInitExpClk(I2C0_BASE, output_clock_rate_hz , true);

    /* clear I2C FIFOs */
    //HWREG(I2C0_BASE + I2C_O_FIFOCTL) = 80008000;
}


/* I2C Write Function [writes 1 byte of data] */
bool I2C_WriteDataByte(uint8_t reg, uint8_t val)
{
    /* Sets the address that the I2C Master places on the bus  */
    I2CMasterSlaveAddrSet(I2C0_BASE, APDS9960_I2C_ADDRESS, false);

    /* Transmits a byte from the I2C Master*/
    I2CMasterDataPut(I2C0_BASE, reg);

    /* Controls the state of the I2C master */
    I2CMasterControl(I2C0_BASE, I2C_MASTER_CMD_BURST_SEND_START);

    /* Wait here till the transaction is completed */
    while(I2CMasterBusy(I2C0_BASE));

    /* Transmits a byte from the I2C Master*/
    I2CMasterDataPut(I2C0_BASE, val);

    /* Controls the state of the I2C master */
    I2CMasterControl(I2C0_BASE, I2C_MASTER_CMD_BURST_SEND_FINISH);

    /* Wait here till the transaction is completed */
    while(I2CMasterBusy(I2C0_BASE));

    return true;
}

/* I2C Read Function [Reads 1 byte of data] */
bool I2C_ReadDataByte(uint8_t reg, uint8_t *val)
{
    /* Sets the address that the I2C Master places on the bus  */
    I2CMasterSlaveAddrSet(I2C0_BASE, APDS9960_I2C_ADDRESS, false);

    /* Transmits a byte from the I2C Master */
    I2CMasterDataPut(I2C0_BASE, reg);

    /* Controls the state of the I2C master */
    I2CMasterControl(I2C0_BASE, I2C_MASTER_CMD_SINGLE_SEND);

    /* Wait here till the transaction is completed */
//    while (!I2CMasterBusy(I2C0_BASE));
    while(I2CMasterBusy(I2C0_BASE));

    /* Sets the address that the I2C Master places on the bus  */
    I2CMasterSlaveAddrSet(I2C0_BASE, APDS9960_I2C_ADDRESS, true);

    /* Controls the state of the I2C master */
    I2CMasterControl(I2C0_BASE, I2C_MASTER_CMD_SINGLE_RECEIVE);

    /* Wait here till the transaction is completed */
//    while (!I2CMasterBusy(I2C0_BASE));
    while(I2CMasterBusy(I2C0_BASE));

    /* Receive a byte that has been sent to the I2C Master */
    *val = (uint8_t)I2CMasterDataGet(I2C0_BASE);

    /* Wait here till the transaction is completed */
    while(I2CMasterBusy(I2C0_BASE));

    return true;
}

int I2C_ReadDataBlock(uint8_t reg, uint8_t *val, unsigned int length)
{
    unsigned char i = 0, j=0;
    while(i<length)
    {
        for(j=0; j<4; j++)
        {
        I2CMasterSlaveAddrSet(I2C0_BASE, APDS9960_I2C_ADDRESS, false);
        I2CMasterDataPut(I2C0_BASE, (0xFC+j));
        I2CMasterControl(I2C0_BASE, I2C_MASTER_CMD_SINGLE_SEND);
        while(I2CMasterBusy(I2C0_BASE));

        I2CMasterSlaveAddrSet(I2C0_BASE, APDS9960_I2C_ADDRESS, true);

        I2CMasterControl(I2C0_BASE, I2C_MASTER_CMD_SINGLE_RECEIVE);
        while(I2CMasterBusy(I2C0_BASE));
        val[i] = (uint8_t)I2CMasterDataGet(I2C0_BASE);
        while(I2CMasterBusy(I2C0_BASE));
        i++;
        }
        j=0;
    }
    return i;
}

