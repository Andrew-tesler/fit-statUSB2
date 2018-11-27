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
 * NAME: initTimers.c
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
#include <driverlib.h>
#include <initBoard.h>
#include "initTimers.h"
#include "defines.c"

//*****************************************************************************************************
//
//  Local variables for the timers
//
//*****************************************************************************************************
int justCounter;                                                                                        // Counter for the for loop
int smallerCounter;                                                                                     // Counter for the for loop used for RGB iteration
int colorsNumber;                                                                                       // Number of colors transition
int test;                                                                                               // Test int // TODO Check if can be removed
int fadeArrayLocation;                                                                                  // Location in fadeArrayDiff array

// Init the timers for RGB Led
void initTimers(int red,int green,int blue) {

    uint8_t Red,Green,Blue;                                                                             // Initialize local variables for the RGB

    // Check for Correct color numbers and pass only them
    // Need to check why the else is setting alterantive function for the GPIO
    // Test for value correctness
    if (red > 0 & red <= 255){
        Red = red;
    }
    else {
        GPIO_setAsPeripheralModuleFunctionInputPin(LED_PORT, LED_R);                                    // Set the Pin to input thus powering off the LED
    }
    if (green > 0 & green <= 255){
        Green = green;
    }
    else {
        GPIO_setAsPeripheralModuleFunctionInputPin(LED_PORT, LED_G);                                    // Set the Pin to input thus powering off the LED
    }
    if (blue > 0 & blue <= 255){
        Blue = blue;
    }
    else {
        GPIO_setAsPeripheralModuleFunctionInputPin(LED_PORT, LED_B);                                    // Set the Pin to input thus powering off the LED
    }


    Timer_A_initUpModeParam initParam2 = {0};
    //
    initParam2.clockSource              = TIMER_A_CLOCKSOURCE_SMCLK;
    initParam2.clockSourceDivider       = TIMER_A_CLOCKSOURCE_DIVIDER_6;
    initParam2.timerInterruptEnable_TAIE = TIMER_A_TAIE_INTERRUPT_DISABLE;
    initParam2.captureCompareInterruptEnable_CCR0_CCIE  = TIMER_A_CCIE_CCR0_INTERRUPT_DISABLE;
    initParam2.timerPeriod              = 0xFF;
    initParam2.timerClear               = TIMER_A_DO_CLEAR;
    initParam2.startTimer               = false;


    Timer_A_initUpMode(TIMER_A0_BASE,&initParam2);

    // Red
    Timer_A_initCompareModeParam initCompareParamcc1 = {0};
    initCompareParamcc1.compareRegister         = TIMER_A_CAPTURECOMPARE_REGISTER_1;
    initCompareParamcc1.compareInterruptEnable  = TIMER_A_CAPTURECOMPARE_INTERRUPT_DISABLE;
    initCompareParamcc1.compareOutputMode       = TIMER_A_OUTPUTMODE_SET_RESET;
    initCompareParamcc1.compareValue            = Red;

    // Blue
    Timer_A_initCompareModeParam initCompareParamcc2 = {0};
    initCompareParamcc2.compareRegister         = TIMER_A_CAPTURECOMPARE_REGISTER_2;
    initCompareParamcc2.compareInterruptEnable  = TIMER_A_CAPTURECOMPARE_INTERRUPT_DISABLE;
    initCompareParamcc2.compareOutputMode       = TIMER_A_OUTPUTMODE_SET_RESET;
    initCompareParamcc2.compareValue            = Blue;

    // Green
    Timer_A_initCompareModeParam initCompareParamcc3 = {0};
    initCompareParamcc3.compareRegister         = TIMER_A_CAPTURECOMPARE_REGISTER_3;
    initCompareParamcc3.compareInterruptEnable  = TIMER_A_CAPTURECOMPARE_INTERRUPT_DISABLE;
    initCompareParamcc3.compareOutputMode       = TIMER_A_OUTPUTMODE_SET_RESET;
    initCompareParamcc3.compareValue            = Green;

    // Init The timers
    Timer_A_initCompareMode(TIMER_A0_BASE, &initCompareParamcc1);
    Timer_A_initCompareMode(TIMER_A0_BASE, &initCompareParamcc2);
    Timer_A_initCompareMode(TIMER_A0_BASE, &initCompareParamcc3);


    Timer_A_clearTimerInterrupt( TIMER_A0_BASE );                                    // Clear TAxIFG

    //Initiate compare mode
    Timer_A_clearCaptureCompareInterrupt(TIMER_A0_BASE,TIMER_A_CAPTURECOMPARE_REGISTER_1 + TIMER_A_CAPTURECOMPARE_REGISTER_2 + TIMER_A_CAPTURECOMPARE_REGISTER_3);

    // Start Timer A counter
    Timer_A_startCounter(TIMER_A0_BASE,TIMER_A_UP_MODE);
}


// Fade the leds from given color to given color by the time given
void initfadeClock() {

    Timer_B_initUpModeParam initTimer_b = {0};
    //    0xDCD;
    initTimer_b.clockSource                             = TIMER_B_CLOCKSOURCE_SMCLK;
    initTimer_b.clockSourceDivider                      = TIMER_B_CLOCKSOURCE_DIVIDER_2;
    initTimer_b.timerPeriod                             = 0xDCD;
    initTimer_b.timerInterruptEnable_TBIE               = TIMER_B_TBIE_INTERRUPT_DISABLE;
    initTimer_b.captureCompareInterruptEnable_CCR0_CCIE = TIMER_B_CCIE_CCR0_INTERRUPT_ENABLE;
    initTimer_b.timerClear                              = TIMER_B_DO_CLEAR;
    initTimer_b.startTimer                              = false;

    Timer_B_initUpMode(TIMER_B0_BASE, &initTimer_b);

    Timer_B_startCounter(TIMER_B0_BASE,TIMER_B_UP_MODE);

}


// calculate  the time for the fade function
void updateFadeTime(uint32_t totalTime) {

    fadeTimer = totalTime;
    initFade(colorsNumber);
}

// Get the colors sequence and sequence number and initialize the fade command
void initFade(uint8_t colorNum) {
    colorsNumber = colorNum;
    colortick = 0;                                                                                                                          // Clear time tick number
    fadeArrayLocation = 0;
    direction = 0;
    //    fadeArrayDirection = 0;
    initTimers(colorSeq[0][0], colorSeq[0][1], colorSeq[0][2]);                                                                             // Start the LED with the first color
    colorLocation = 0;
    currentRGBColor[0] = colorSeq[0][0];
    currentRGBColor[1] = colorSeq[0][1];
    currentRGBColor[2] = colorSeq[0][2];

    for (justCounter = 0 ; justCounter < colorsNumber-1 ; justCounter++) {                                                                    // The last run of the loop calculates the time from the last element to first element
        for (smallerCounter = 0 ; smallerCounter < 3 ; smallerCounter++) {                                                                  // Each R,G,B color calculation
            colorFadeDiff[justCounter][smallerCounter] = (colorSeq[justCounter+1][smallerCounter] - colorSeq[justCounter][smallerCounter]);
        }
    }
    // Calculate the last transition
    for (smallerCounter = 0 ; smallerCounter < 3 ; smallerCounter++) {
        colorFadeDiff[colorsNumber-1][smallerCounter] = (colorSeq[0][smallerCounter] - colorSeq[colorsNumber-1][smallerCounter]);
    }
    initfadeClock();                                                                                                                        // Start Timer_B0
}


// Function to be called by TIMER0_B0 that will update the current color according to calculated values
// Stop the timers and run the init timers again with the updated values
void updateFadeColor(){
    Timer_A_stop(TIMER_A0_BASE);// Stop Timer
    initTimers(currentRGBColor[0],currentRGBColor[1],currentRGBColor[2]);


}

//*****************************************************************************
// Interrupt Service Routine
//*****************************************************************************
//
#pragma vector=TIMER0_B0_VECTOR
__interrupt void timer_ISRB0 (void) {
    // the timer should run and update the PWM clock(TIMERA0) if any change needed
    // Because of several fade values present the script will also need to iterate on the array of colors
    currentRGBColor[2] =   ((colorLocation * colorFadeDiff[fadeArrayLocation][2]) /  colorFadeTimer[fadeArrayLocation]) + colorSeq[fadeArrayLocation][2];

    colorLocation++;

    if (colorLocation > colorFadeTimer[fadeArrayLocation] ) {
        currentRGBColor[0] =   (((colorLocation-colorFadeTimer[fadeArrayLocation]) * colorFadeDiff[fadeArrayLocation][0]) /  fadeTimer) + colorSeq[fadeArrayLocation][0];
        currentRGBColor[1] =   (((colorLocation-colorFadeTimer[fadeArrayLocation]) * colorFadeDiff[fadeArrayLocation][1]) /  fadeTimer) + colorSeq[fadeArrayLocation][1];
        currentRGBColor[2] =   (((colorLocation-colorFadeTimer[fadeArrayLocation]) * colorFadeDiff[fadeArrayLocation][2]) /  fadeTimer) + colorSeq[fadeArrayLocation][2];
    }
    // Update fade color
    updateFadeColor();

    if (colorLocation >= colorFadeTimer[fadeArrayLocation]+ fadeTimer){   // Test if the array of the color reached its limits
        //
        if (disableDirection == 1) {
            Timer_B_stop(TIMER_B0_BASE);
        }

        if (fadeArrayLocation == colorsNumber-1) {
            fadeArrayLocation = 0;
            //colorLocation=0;
        }
        else if (fadeArrayLocation < colorsNumber-1){
            fadeArrayLocation++;
        }
        colorLocation=0;

    }
    Timer_B_clearCaptureCompareInterrupt(TIMER_B0_BASE, TIMER_B_CAPTURECOMPARE_REGISTER_0);
}
