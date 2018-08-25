/*
 * globals.c
 *
 *  Created on: Jul 21, 2018
 *      Author: tesle
 */
#include <msp430.h>
#include "driverlib.h"

#define SLAVE_ADDRESS 0x3C
//#define TXLENGTH  7;

#define BLACK 0
#define WHITE 1
#define INVERSE 2

#define LCDWIDTH            128
#define LCDHEIGHT           64
#define FONTHEADERSIZE      6

#define NORM                0
#define XOR                 1

#define PAGE                0
#define ALL                 1

#define WIDGETSTYLE0            0
#define WIDGETSTYLE1            1
#define WIDGETSTYLE2            2




uint8_t transmitData[40][2] = {
//                                  {0x00, 0xAE},
//                                  {0x00, 0xD5},
//                                  {0x48, 0x80},
//                                  {0x48, 0xA8},
//                                  {0x48, 0x00},
//                                  {0x48, 0x00},
//                                  {0x48, 0x00}


};


