/** --------------------------------------------------------------------------
 * File Author name : NILESHKARTIK ASHOKKUMAR
 * ECEN 5613 - Fall 2022
 * University of Colorado Boulder
 * Revised 12/2/22
 * File name : command_process.c
 * Project Topic : Fire Safety System for Autonomous vehicle
 *  --------------------------------------------------------------------------
 * In this file defining process command function to tokenize the GPS data
   -----------------------------------------------------------------------**/
/** -------------------------------------------------------- /
                    INCLUDES
/ -------------------------------------------------------- **/
#include "command_process.h"

/** ------------------------------------------------------- /
                FUNCTION DEFINITIONS
/ -------------------------------------------------------- **/
void process_command(char *input,char *argv[])
{
    char *p = input;
    char *end;
    int flag = 0;
    int found_AN = 0;

    for (end = input; *end != '\0'; end++);                    // find end of string


    int argc = 0;
    memset(argv, 0, sizeof(argv));                             /* clearing the argv */


    for (p = input; p < end; p++)
    {
        if(*p == '$')
        {
            p++;
            while(*p != ',')
            {
                if(flag == 0)
                {
                    argv[argc] = p;                         /* stores the start address of the string for building the token */
                    argc++;
                    flag = 1;
                }
                p++;
            }
            flag = 0;
            *p = '\0';
        }
        else if((*p != 'A') && ((*p != 'N')) && (found_AN != 1) ) /* checks for AN Command in GPS data */
        {
            continue;
        }
        else if((*p == 'A') || (*p == 'N'))
        {
            found_AN = 1;
        }
        else if(found_AN == 1)
        {
            p++;
            while(*p != ',')
            {
                if(flag == 0)
                {
                    argv[argc] = p;                         /* stores the start address of the string for building the token */
                    argc++;
                    flag = 1;
                }
                p++;
            }
            *p = '\0';
            flag = 0;
            found_AN = 0;

            if(argc == 3)
            {
                return;
            }

        }
    }
}


