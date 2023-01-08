/** --------------------------------------------------------------------------------------------------
 * File Author name : NILESHKARTIK ASHOKKUMAR
 * ECEN 5613 - Fall 2022
 * University of Colorado Boulder
 * Revised 11/26/22
 * File name : i2c_ops.c
 * Project Topic : Fire Safety System for Autonomous vehicle
 * Reference code : https://github.com/johrirj88/msp432_i2c_oledssd1306/blob/master/i2c_oled/i2c_ops.c
 *  --------------------------------------------------------------------------------------------------
 * In this file defining i2c initialization, write, start and stop functions
   -----------------------------------------------------------------------**/

/** -------------------------------------------------------- /
                    INCLUDES
/ -------------------------------------------------------- **/
#include "msp.h"
#include "oled.h"
#include "i2c_ops.h"

/** ------------------------------------------------------- /
                FUNCTION DEFINITIONS
/ -------------------------------------------------------- **/

/** i2c_init function initializes the I2C communication **/
void i2c_init()
{
    /* make sure module is disabled */
    disable_i2c();

    /* change P1.6 and P1.7 as primary function */
    P1SEL0 |= BIT6;
    P1SEL1 &= ~(BIT6);

    P1SEL0 |= BIT7;
    P1SEL1 &= ~(BIT7);

    /* modes selected:
     * master, i2c, synchronous, SMCLK, transmitter */
    UCB0CTLW0 |= 0x0FD0;

    /* clock: 100 KHz */
    UCB0BRW = clock;

    /* initialize slave address */
    UCB0I2CSA = SLAVE_ADDR;

    /* enable module only when transmission is required */
}

/** i2c_send function writes number of bytes to be sent to slave    /
/   enable auto stop generation in UCBxCTLW1                      **/
void i2c_send(unsigned char *data, unsigned int len)
{

    /* enable i2c module */
    enable_i2c();

    /* generate start condition and wait for the bus */
    generate_start();
    while((UCB0IFG & UCTXIFG0) == 0);

    /* write data byte by byte to buffer */
    while(len--)
    {
        i2c_write_txbuf(*data);
        data++;
    }

    /* force stop and check if stop is generated or not */
    generate_stop();
    while((UCB0IFG & UCSTPIFG) == 0);

    /* transmission completed, disable the module */
    disable_i2c();
}

/** write data on i2c bus **/
static void i2c_write_txbuf(unsigned char byte)
{
    UCB0TXBUF = byte;
    while((UCB0IFG & UCTXIFG0) == 0);
}

/** enable i2c bus **/
static void enable_i2c()
{
    UCB0CTLW0 &= ~(0x01);

}

/** disable i2c bus **/
static void disable_i2c()
{
    UCB0CTLW0 |= 0x01;
}

/** This function performs the start operation to initiate the communication **/
static void generate_start()
{
    UCB0CTLW0 |= 0x0002;
}

/**  Whenever master want to stop the communication then it will assert the stop condition to the i2c bus **/
static void generate_stop()
{
    UCB0CTLW0 |= 0x0004;
}
