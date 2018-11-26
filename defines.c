/*
 * globals.c
 *
 *  Created on: Jul 21, 2018
 *      Author: Andrew Tesler
 *
 */

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
    #define RIGHT_BUTTON_PIN        GPIO_PIN_P1

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
#define MAX_FADE_DECIMAL        5                   // Maximum fade decimal numbers, If increasing size check all related value size also

// TODO Check for some other method to store information or increase the code size using different MCU
#define MAX_SEQ_COLORS          20                  // Maximum Color in sequence that can accept from the user(limited by code size)




