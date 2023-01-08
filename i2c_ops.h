/** ------------------------------------------------------------------------
 * File Author name : NILESHKARTIK ASHOKKUMAR
 * ECEN 5613 - Fall 2022
 * University of Colorado Boulder
 * Revised 11/26/22
 * File name : i2c_ops.c
 * Project Topic : Fire Safety System for Autonomous vehicle
 *  ------------------------------------------------------------------------
 * In this file declaring i2c initialization, write, start and stop functions
   -----------------------------------------------------------------------**/
#ifndef I2C_OPS_H_
#define I2C_OPS_H_

/** ----------------------------------------------------- /
                FUNCTION DECLARATIONS
/ ------------------------------------------------------ **/
void i2c_init();
void i2c_send(unsigned char*, unsigned int);
static void i2c_write_txbuf(unsigned char);
static void enable_i2c();
static void disable_i2c();
static void generate_start();
static void generate_stop();
/** ------------------------------------------------------ /
                    MACROS
/ ------------------------------------------------------- **/
#define clock (30)

#endif /* I2C_OPS_H_ */
