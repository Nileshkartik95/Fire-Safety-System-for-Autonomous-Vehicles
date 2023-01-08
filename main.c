/** -----------------------------------------------------------------------------------------------------
 * File Author 1 name : NILESHKARTIK ASHOKKUMAR
 * File Author 2 name : MALOLA SIMMAN SRINIVASAN KANNAN
 * ECEN 5613 - Fall 2022
 * University of Colorado Boulder
 * Revised 11/26/22
 * File name : main.c
 * Project Topic : Fire Safety System for Autonomous vehicle
 *  ----------------------------------------------------------------------------------------------------
 * This source file demonstrates the working flow model of the Fire Safety System for Autonomous vehicle
 * which includes various API calls to perform initialization of different module to read IR sensor,
 * read the GPS Data, Display OLED, and motor actuation.
   ---------------------------------------------------------------------------------------------------**/

/** -------------------------------------------------------- /
                    INCLUDES
/ -------------------------------------------------------- **/
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stddef.h>
#include <strings.h>
#include "msp.h"
#include "i2c_ops.h"
#include "oled.h"
#include "uart_gps.h"
#include "ir_sensor.h"
#include "motor.h"
#include "command_process.h"

/** ----------------------------------------------------- /
                GLOBAL VARIABLES
/ ------------------------------------------------------ **/
unsigned char TEXT_ARR[1024];
unsigned char LOGO_ARR[1024];
char recd_rxchar = 0;                   /*contains the data from the RX buffer*/

/** ------------------------------------------------------ /
                        MACROS
/ ------------------------------------------------------- **/
#define GPS


/** ----------------------------------------------------- /
                    MAIN FUNCTION
/ ------------------------------------------------------ **/
void main(void)
{
    unsigned char str[16] = "               ";
    char str_gpsdata[1024];
    char buffer_N[16];
    char buffer_W[16];
    char *argv[10];
    char gprmc_str[] = "GPRMC";
    int i = 0;
    int st_gps = 0;

    oled_init();                            /*OLED initialization */
    init_ir_sensor();                       /*initializing the IR sensor as GPIO input*/

    CS_Config();
    uart0_init();                           /*initializing the UART 0 for serial terminal communication*/
    uart2_init();                           /*initializing the UART 2 for GPS communication with msp 432*/
    pwm_init();                             /*pwm initialization for the motor */

    draw_line(1,1,"Dashboard");             /*Display dash board on the line 1 of the OLED*/
    draw_line(2,1,"Drive Mode");            /*Display drive mode on the line 2 of the OLED*/

    int start_motor_st = 1;                 /*start motor flag variable*/
    int stop_motor_st = 1;                  /*stop motor flag variable to be stop the motor once in the stop sequence when read from the ir sesnor*/
    P3->OUT=0xff;
    while(1)
    {
        /*Check is the input on the pin 4 is high*/
        if((P2->IN & 0x10) == 0x10)
        {
            /*custom define if the GPS feature is no more needed*/
#ifdef GPS
            /*poll until the character is received*/
            while(!(EUSCI_A2->IFG & EUSCI_A_IFG_RXIFG));

            /*check if the received buffer contains $ which is the starting sequence for a string in GPS module*/
            while(EUSCI_A2->RXBUF != '$');

            /*store the rx buffer data to the received rx character*/
            recd_rxchar = EUSCI_A2->RXBUF;


            if(st_gps != 1)
            {
                /*check if the start sequence is $ for the GPS data received from the UART*/
                while(recd_rxchar == '$')
                {
                    /*poll until the received character is new line*/
                    while(recd_rxchar != '\r')
                    {
                        /*store each character to an array */
                        str_gpsdata[i]= recd_rxchar;                 /* stores the current character to the string stream */
                        i++;
                        /*poll for the next character while the received character is not carriage return */
                        while(!(EUSCI_A2->IFG & EUSCI_A_IFG_RXIFG));
                        recd_rxchar = EUSCI_A2->RXBUF;
                    }
                    /*stringify the received character input by null termination*/
                    str_gpsdata[i] = '\0';
                    /*tokenize the string input*/
                    process_command(str_gpsdata,argv);

                }

                i = 0;              /*reset the counter variable*/
                recd_rxchar= 0;     /*reset the received character buffer*/
                /*check if the received string is GPRMC for the latitude and longitude*/
                if(strcasecmp(argv[0],gprmc_str) == 0)
                {
                    st_gps = 1;
                    sprintf(buffer_N, "Lat:%sN", argv[1]);      /*store the latitude information */
                    sprintf(buffer_W, "Lo:%sW", argv[2]);       /*store the longitude information */
                }
                else
                {
                    memset(buffer_N,0,16);                     /*clearing the buffer in case if the string GPRMC doesn't match */
                    memset(buffer_W,0,16);                     /*clearing the buffer in case if the string GPRMC doesn't match */
                }
            }
#endif
            draw_line(2,1,"Fire Alert");                        /*displaying the fire alert when IR sensor GPIO pin is high*/
            draw_line(3,1,buffer_N);                            /*displaying the latitude*/
            draw_line(4,1,buffer_W);                            /*displaying the longitude*/
            Display_Logo(1,1,0);                                /*displaying the alert symbol*/

            write_display(LOGO_ARR);                            /*writing data to the i2C bus*/
            write_display(TEXT_ARR);                            /*writing data to the i2C bus*/
            start_motor_st = 1;
            if(stop_motor_st == 1)
            {
                stop_motor();                                   /* stop the motor */
                stop_motor_st = 0;
            }
        }
        else
        {
            draw_line(2,1,"Drive Mode");                        /* if the ir sensor GPIO pin value is low then print the Drive mode*/
            draw_line(3,1,str);
            draw_line(4,1,str);
            memset(LOGO_ARR,0,1024);                            /*clear the alert logo during the drive mode*/
            write_display(TEXT_ARR);                            /*write the oled with the text array*/

            stop_motor_st = 1;
            if(start_motor_st == 1)
            {
                start_motor();                                  /* start the motor and remain in that PWM state*/
                start_motor_st = 0;
            }
        }
        memset(argv,0,sizeof(argv));                            /*reset the argv for next string input*/
    }
}
