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
 * NAME: usbLed.c
 *
 * PURPOSE: Initialize the Timers,
 *
 * GLOBAL VARIABLES:
 * *
 * Variable Type Description *
 * -------- ---- ----------- *
 * *
 * DEVELOPMENT HISTORY: *
 * *
 * Date        Author       Release Description Of Change *
 * ----        ------       ------- --------------------- *
 * 27/08/2018   Andrew T.   0.1.0    initial Release
 * *
 * *
 *******************************************************************/


//*****************************************************************************************************
//
//  INCLUDE
//
//*****************************************************************************************************
#include "usbLed.h"
#include "defines.c"


/**
 * Function to turn off all of LED's
 *
 */
void allOff() {

#ifdef ARDUMSP
    GPIO_setAsOutputPin(LED_PORT,LED_R);
    GPIO_setAsOutputPin(LED_PORT,LED_G);
    GPIO_setAsOutputPin(LED_PORT,LED_B);
    GPIO_setOutputLowOnPin(LED_PORT,LED_R);
    GPIO_setOutputLowOnPin(LED_PORT,LED_G);
    GPIO_setOutputLowOnPin(LED_PORT,LED_B);
#else

    GPIO_setAsPeripheralModuleFunctionInputPin(GPIO_PORT_P1, GPIO_ALL); // Input power off the RED led

#endif //ARDUMSP
}

/**
 * Function to turn on all of the LED's
 *
 */
void allOn() {
    GPIO_setAsOutputPin(LED_PORT,LED_R);
    GPIO_setOutputLowOnPin(LED_PORT,LED_R);
//    GPIO_setOutputHighOnPin(LED_PORT,LED_R);

    GPIO_setAsOutputPin(LED_PORT,LED_G);
    GPIO_setOutputLowOnPin(LED_PORT,LED_G);
//    GPIO_setOutputHighOnPin(LED_PORT,LED_G);

    GPIO_setAsOutputPin(LED_PORT,LED_B);
    GPIO_setOutputLowOnPin(LED_PORT,LED_B);
//    GPIO_setOutputHighOnPin(LED_PORT,LED_B);

}

/*
 * Power on LEDS based on the passed character
 */
void ledOn(char led) {
    allOff();                                                       // Initially turn off all of the LEDs

    switch(led) {
    case 'R' :
        GPIO_setAsOutputPin(LED_PORT,LED_R);

        #ifdef ARDUMSP
            GPIO_setOutputHighOnPin(LED_PORT,LED_R);
        #else
            GPIO_setOutputLowOnPin(LED_PORT,LED_R);
        #endif //ARDUMSP
        break;

    case 'G' :
        GPIO_setAsOutputPin(LED_PORT,LED_G);
        #ifdef ARDUMSP
            GPIO_setOutputHighOnPin(LED_PORT,LED_G);
        #else
            GPIO_setOutputLowOnPin(LED_PORT,LED_G);
        #endif //ARDUMSP
        break;

    case 'B' :
        GPIO_setAsOutputPin(LED_PORT,LED_B);
        #ifdef ARDUMSP
            GPIO_setOutputHighOnPin(LED_PORT,LED_B);
        #else
            GPIO_setOutputLowOnPin(LED_PORT,LED_B);
        #endif //ARDUMSP
        break;

    case 'S' : // SAGOL
        GPIO_setAsOutputPin(LED_PORT,LED_R);
        GPIO_setOutputLowOnPin(LED_PORT,LED_R);
        GPIO_setAsOutputPin(LED_PORT,LED_B);
        GPIO_setOutputLowOnPin(LED_PORT,LED_B);
        break;
    case 'Y' : //Yellow
        GPIO_setAsOutputPin(LED_PORT,LED_G);
        GPIO_setOutputLowOnPin(LED_PORT,LED_G);
        GPIO_setAsOutputPin(LED_PORT,LED_R);
        GPIO_setOutputLowOnPin(LED_PORT,LED_R);
        break;
    case 'T' : // Turkiz
        GPIO_setAsOutputPin(LED_PORT,LED_G);
        GPIO_setOutputLowOnPin(LED_PORT,LED_G);
        GPIO_setAsOutputPin(LED_PORT,LED_B);
        GPIO_setOutputLowOnPin(LED_PORT,LED_B);
        break;
    case 'W' :
        allOn();
        break;
    default :
        break;
    }
}

