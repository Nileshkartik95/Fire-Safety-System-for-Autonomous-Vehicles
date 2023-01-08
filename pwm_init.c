/** ----------------------------------------------------------
 * File Author name : MALOLA SIMMAN SRINIVASAN KANNAN
 * ECEN 5613 - Fall 2022
 * University of Colorado Boulder
 * Revised 12/02/22
 * File name : pwm_init.c
 * Project Topic : Fire Safety System for Autonomous vehicle
 * Reference code : http://www.microdigitaled.com/EduPad/MSP432-EduPad/16_pwm_motor.txt
 *  ----------------------------------------------------------
 * In this file Initializing PWM and GPIO Port Pins
   ---------------------------------------------------------**/

/** -------------------------------------------------------- /
                    INCLUDES
/ -------------------------------------------------------- **/
#include "motor.h"

/** ------------------------------------------------------- /
                FUNCTION DEFINITIONS
/ -------------------------------------------------------- **/

/** pwm_init function initializes the pins and configures timer **/
void pwm_init()
{
    P2->SEL0 |= 0x80;               /* Configure P2.7 as Timer A0 pin4 output */
    P2->SEL1 &= ~0x80;
    P2->DIR |= 0x80;
    P3->DIR |=0x0C;
    portRemap();                    /* remap output to P2.1 green LED */

    /* configure TimerA0.4 as PWM */
    TIMER_A0->CCR[0] = PWM_period-1;     /* PWM Period */
    TIMER_A0->CCR[4] = one_percent_dutycycle;         /* begin from 1% */
    TIMER_A0->CCTL[4] = 0xE0;       /* CCR4 reset/set mode */
    TIMER_A0->CTL = 0x0214;         /* use SMCLK, count up, clear TA0R register */
}


/** portRemap function maps the port pins **/
void portRemap(void) {
    PMAP->KEYID = 0x2D52;           /* unlock PMAP */

    P2MAP->PMAP_REGISTER1 = 23;     /* remap P2.1 to 23 (TPM0.4) */
    P2->DIR |= 2;
    P2->SEL0 |= 2;
    P2->SEL1 &= ~2;

    PMAP->CTL = 1;                  /* lock PMAP */
    PMAP->KEYID = 0;
}

/** delay milliseconds when system clock is at 3 MHz **/
void delayMs(int n)
{
    int i, j;

    for (j = 0; j < n; j++)
        for (i = 750; i > 0; i--);      /* Delay */
}
