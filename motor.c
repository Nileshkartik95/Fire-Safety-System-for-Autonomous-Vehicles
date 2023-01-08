/** ----------------------------------------------------------------------------
 * File Author name : MALOLA SIMMAN SRINIVASAN KANNAN
 * ECEN 5613 - Fall 2022
 * University of Colorado Boulder
 * Revised 12/2/22
 * File name : motor.c
 * Project Topic : Fire Safety System for Autonomous vehicle
 * Reference code : http://www.microdigitaled.com/EduPad/MSP432-EduPad/16_pwm_motor.txt
 *  -----------------------------------------------------------------------------
 * This file defining Motor start, stop functions
   ---------------------------------------------------------------------------**/

/** ------------------------------------------------------ /
                    INCLUDES
/ ------------------------------------------------------- **/
#include "motor.h"

/** ------------------------------------------------------- /
                FUNCTION DEFINITIONS
/ -------------------------------------------------------- **/
/** start_motor starts the motor **/
void start_motor(void)
{
    int pwm = 0;
    // sets direction
    P3->OUT &= 0x80;
    P3->OUT |= 0x08;
    //running PWM with increase in duty cycle by  1 percent
    for( pwm=start_pwm;pwm<PWM_period;pwm+=one_percent_dutycycle)
    {
        TIMER_A0->CCR[4] = pwm;
        delayMs(50);
    }
}

/** stop_motor stops the motor **/
void stop_motor(void)
{
    int pwm = 0;
    // sets direction
    P3->OUT &= 0x80;
    P3->OUT |= 0x08;
    // running down PWM with decreasing duty cycle by 1 percent
    for( pwm=PWM_period;pwm>0;pwm-=one_percent_dutycycle){
        TIMER_A0->CCR[4] = pwm;
        delayMs(50);
    }
}
