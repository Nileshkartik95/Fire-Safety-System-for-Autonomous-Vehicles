/** ------------------------------------------------------------------------
 * File Author name : NILESHKARTIK ASHOKKUMAR
 * ECEN 5613 - Fall 2022
 * University of Colorado Boulder
 * Revised 11/28/22
 * File name : ir_sensor.c
 * Project Topic : Fire Safety System for Autonomous vehicle
 *  ------------------------------------------------------------------------
 * In this file defining IR sensor initialization
   -----------------------------------------------------------------------**/

/** ------------------------------------------------------ /
                    INCLUDES
/ ------------------------------------------------------- **/
#include "msp432.h"

/** ------------------------------------------------------- /
                FUNCTION DEFINITIONS
/ -------------------------------------------------------- **/

/** init_ir_sensor function initializes the  port pins for fire sensor **/
void init_ir_sensor(void)
{
    /* Initialize P2.4 for IR sensor Input*/
    P2->DIR |= ~(uint8_t) BIT4;             /*setting the direction as input*/
    P2->OUT |= BIT4;
    P2->REN |= BIT4;                        /* Enable pull-up resistor (P2.4 output high)*/
    P2->SEL1 &= ~(1<<4);                    /* setting the control bit for I/O operation*/
    P2->SEL0 &= ~(1<<4);                    /* setting the control bit for I/O operation*/
}

