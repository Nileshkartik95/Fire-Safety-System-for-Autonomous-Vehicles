/** ------------------------------------------------------
 * File Author name : MALOLA SIMMAN SRINIVASAN KANNAN
 * ECEN 5613 - Fall 2022
 * University of Colorado Boulder
 * Revised 12/02/22
 * File name : motor.h
 * Project Topic : Fire Safety System for Autonomous vehicle
 * Reference code : http://www.microdigitaled.com/EduPad/MSP432-EduPad/16_pwm_motor.txt
 *  -------------------------------------------------------
 * In this file Declaring PWM functions and motor function
   ------------------------------------------------------**/

#ifndef MOTOR_H_
#define MOTOR_H_

/** ------------------------------------------------------ /
                    INCLUDES
/ ------------------------------------------------------- **/
#include "msp432.h"

/** ----------------------------------------------------- /
                FUNCTION DECLARATIONS
/ ------------------------------------------------------ **/
void pwm_init(void);
void delayMs(int n);
void portRemap(void);
void start_motor(void);
void stop_motor(void);

/** ------------------------------------------------------ /
                    MACROS
/ ------------------------------------------------------- **/

#define PWM_period             (50000)
#define one_percent_dutycycle  (500)
#define start_pwm              (1000)

#endif /* MOTOR_H_ */
