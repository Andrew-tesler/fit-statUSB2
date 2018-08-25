/*
 * globals.c
 *
 *  Created on: Jul 21, 2018
 *      Author: tesle
 */
#include <msp430.h>
#include "driverlib.h"

// There is difference in fitStatuSB2 device and the debugging platform
#define LAUNCH_PAD
//#define FITSTATUSB

#if defined LAUNCH_PAD && defined FITSTATUSB
  #error "Only one HW platform can be defined"
#endif


// Slave Address of I2C LCD
#define SLAVE_ADDRESS           0x3C
//#define TXLENGTH  7;

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




//uint8_t transmitData[40][2] = {
////                                  {0x00, 0xAE},
////                                  {0x00, 0xD5},
////                                  {0x48, 0x80},
////                                  {0x48, 0xA8},
////                                  {0x48, 0x00},
////                                  {0x48, 0x00},
////                                  {0x48, 0x00}
//
//
//};


#define GPIO_ALL    GPIO_PIN0|GPIO_PIN1|GPIO_PIN2|GPIO_PIN3| \
        GPIO_PIN4|GPIO_PIN5|GPIO_PIN6|GPIO_PIN7

// TODO change to the correct GPIO on the platform
#define LED_PORT    GPIO_PORT_P1
#define LED_G       GPIO_PIN4
#define LED_B       GPIO_PIN3
#define LED_R       GPIO_PIN2

#define MAX_FADE_DECIMAL 5                                                                              // Maximum fade decimal numbers, If increasing size check all related value size also
#define MAX_SEQ_COLORS   20

