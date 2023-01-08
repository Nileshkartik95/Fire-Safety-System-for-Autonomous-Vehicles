/** ------------------------------------------------------------------------
 * File Author name : NILESHKARTIK ASHOKKUMAR
 * ECEN 5613 - Fall 2022
 * University of Colorado Boulder
 * Revised 12/2/22
 * File name : uart_gps.c
 * Project Topic : Fire Safety System for Autonomous vehicle
 *  ------------------------------------------------------------------------
 * In this file defining UART initialization, and clock configuration functions
   -----------------------------------------------------------------------**/

/** -------------------------------------------------------- /
                    INCLUDES
/ -------------------------------------------------------- **/
#include "msp432.h"


/** ------------------------------------------------------ /
                    MACROS
/ ------------------------------------------------------- **/
#define BAUD_RATE    78        /*baud rate defined for the uart communication*/


/** ----------------------------------------------------- /
                FUNCTION DEFINITIONS
/ ------------------------------------------------------ **/

/** CS_Config function configures the clock for UART communication **/
void CS_Config(void)
{
    CS->KEY = CS_KEY_VAL;                   // Unlock CS module for register access
    CS->CTL0 = 0;                           // Reset tuning parameters
    CS->CTL0 = CS_CTL0_DCORSEL_3;           // Set DCO to 12MHz (nominal, center of 8-16MHz range)
    CS->CTL1 = CS_CTL1_SELA_2 |             // Select ACLK = REFO
            CS_CTL1_SELS_3 |                // SMCLK = DCO
            CS_CTL1_SELM_3;                 // MCLK = DCO
    CS->KEY = 0;                            // Lock CS module from unintended accesses
}

/** uart0_init function initializes the pins and configures UART communication **/
void uart0_init(void)
{
    // Configure UART pins
    P1->SEL0 |= BIT2 | BIT3;                // set 2-UART pin as secondary function

    // Configure UART
    EUSCI_A0->CTLW0 |= EUSCI_A_CTLW0_SWRST; // Put eUSCI in reset
    EUSCI_A0->CTLW0 = EUSCI_A_CTLW0_SWRST | // Remain eUSCI in reset
                      EUSCI_B_CTLW0_SSEL__SMCLK;      // Configure eUSCI clock source for SMCLK

    // Baud Rate calculation
    // 12000000/(16*9600) = 78.125
    // Fractional portion = 0.125
    // User's Guide Table 21-4: UCBRSx = 0x10
    // UCBRFx = int ( (78.125-78)*16) = 2

    EUSCI_A0->BRW = BAUD_RATE;                     // 12000000/16/9600
    EUSCI_A0->MCTLW = (2 << EUSCI_A_MCTLW_BRF_OFS) |
                      EUSCI_A_MCTLW_OS16;

    EUSCI_A0->CTLW0 &= ~EUSCI_A_CTLW0_SWRST; // Initialize eUSCI
}

/** uart2_init function initializes UART communication **/
void uart2_init(void)
{
    // Configure UART pins
    P3->SEL0 |=  BIT2;                                      // set 2-UART pin as secondary function

    // Configure UART
    EUSCI_A2->CTLW0 |= EUSCI_A_CTLW0_SWRST;                 // Put eUSCI in reset
    EUSCI_A2->CTLW0 = EUSCI_A_CTLW0_SWRST |                 // Remain eUSCI in reset
            EUSCI_B_CTLW0_SSEL__SMCLK;                      // Configure eUSCI clock source for SMCLK

    // Baud Rate calculation
    // 12000000/(16*9600) = 78.125
    // Fractional portion = 0.125
    // User's Guide Table 21-4: UCBRSx = 0x10
    // UCBRFx = int ( (78.125-78)*16) = 2

    EUSCI_A2->BRW = BAUD_RATE;                                       // 12000000/16/9600
    EUSCI_A2->MCTLW = (2 << EUSCI_A_MCTLW_BRF_OFS) |
            EUSCI_A_MCTLW_OS16;

    EUSCI_A2->CTLW0 &= ~EUSCI_A_CTLW0_SWRST;                  // Initialize eUSCI
    EUSCI_A2->IFG &= ~EUSCI_A_IFG_RXIFG;                      // Clear eUSCI RX interrupt flag
}




