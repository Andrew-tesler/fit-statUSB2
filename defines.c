/* --COPYRIGHT--,BSD
 * Copyright (c) 2016, Texas Instruments Incorporated
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * *  Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *
 * *  Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * *  Neither the name of Texas Instruments Incorporated nor the names of
 *    its contributors may be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 * THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
 * OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
 * OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
 * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 * --/COPYRIGHT--*/

/**********************************************************
 * NAME: *
 * defines.c
 *
 * PURPOSE: Main define and global virables for the file
 *
 *
 * *
 * Variable Type Description *
 * -------- ---- ----------- *
 * *
 * DEVELOPMENT HISTORY: *
 * *
 * Date        Author       Release Description Of Change *
 * ----        ------       ------- --------------------- *
 * 26/11/2018  Andrew T.     0.1.0     initial Release
 *
 * *
 *******************************************************************/

//*****************************************************************************************************
//
//  INCLUDE FILES
//
//*****************************************************************************************************
#include <msp430.h>
#include "driverlib.h"

// Defines that control different code segment depending the platform
// Only one platform can be defined at a time
//
// LAUNCH_PAD  - debug platform based on MSP40f5529 Ti MCU
// FITSTATUSB2_V1 - Initial revision of fit-statUSB2 platform will based on the final MCU device may not be finalized completely

#define LAUNCH_PAD
//#define FITSTATUSB2_V1


#if defined LAUNCH_PAD && defined FITSTATUSB2_V1
#error "Only one HW platform can be defined"
#endif

//*****************************************************************************************************
//
//  LCD DEFINES
//
//*****************************************************************************************************

// Slave I2C LCD Address
#define SLAVE_ADDRESS           0x3C

// Misc Defines for LCD driver
#define BLACK                   0
#define WHITE                   1
#define INVERSE                 2

#define LCDWIDTH                128
#define LCDHEIGHT               64
#define FONTHEADERSIZE          6

#define NORM                    0
#define XOR                     1

#define PAGE                    0
#define ALL                     1

#define WIDGETSTYLE0            0
#define WIDGETSTYLE1            1
#define WIDGETSTYLE2            2

//*****************************************************************************************************
//
//  GPIO DEFINES
//
//*****************************************************************************************************
// TODO change to the correct GPIO on the platform
#ifdef LAUNCH_PAD
    #define LED_PORT                GPIO_PORT_P1
    #define LED_G                   GPIO_PIN2
    #define LED_B                   GPIO_PIN3
    #define LED_R                   GPIO_PIN4

    #define RED_LED_PORT            GPIO_PORT_P1                                                        // Unboard red LED port
    #define RED_LED_PIN             GPIO_PIN0                                                           // Unboard Red LED Pin

    #define GREEN_LED_PORT          GPIO_PORT_P4                                                        // Unboard Green LED port
    #define GREEN_LED_PIN           GPIO_PIN7                                                           // Unboard Green LED pin

    #define LEFT_BUTTON_PORT        GPIO_PORT_P2
    #define LEFT_BUTTON_PIN         GPIO_PIN1

    #define RIGHT_BUTTON_PORT       GPIO_PORT_P1
    #define RIGHT_BUTTON_PIN        GPIO_PIN1

    #define GPIO_ALL    GPIO_PIN0|GPIO_PIN1|GPIO_PIN2|GPIO_PIN3| \
        GPIO_PIN4|GPIO_PIN5|GPIO_PIN6|GPIO_PIN7

#elif defined FITSTATUSB2_V1
    #error "defines.c - Write correct defines for GPIO in" // TODO
#endif

//*****************************************************************************************************
//
//  DEFINES FOR led GPIO TIMINNGS
//
//*****************************************************************************************************
#define MAX_FADE_DECIMAL        5                                                                       // Maximum fade decimal numbers, If increasing size check all related value size also

// TODO Check for some other method to store information or increase the code size using different MCU
#define MAX_SEQ_COLORS          20                                                                      // Maximum Color in sequence that can accept from the user(limited by code size)

//*****************************************************************************************************
//
//  Board Globals
//
//*****************************************************************************************************
uint32_t myACLK;                                                                                        // Board Temp ACLK
uint32_t mySMCLK;                                                                                       // Board Temp SMCLK
uint32_t myMCLK;                                                                                        // Board Temp MCLK


