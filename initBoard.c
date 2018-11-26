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
/*
 * ======== hal.c ========
 *  Created on: Jul 21, 2018
 *      Author: Andrew Tesler
 *
 */
#include <defines.c>
#include <initBoard.h>
#include "msp430.h"

#include "driverlib.h"

#include "USB_API/USB_Common/device.h"
#include "USB_config/descriptors.h"

#if defined LAUNCH_PAD
    #define LF_CRYSTAL_FREQUENCY_IN_HZ     32768                                    // 32KHz
    #define HF_CRYSTAL_FREQUENCY_IN_HZ     4000000                                  // 12MHz // Launch pad
#endif

//#define LF_CRYSTAL_FREQUENCY_IN_HZ     32768                                    // 32KHz
//#define HF_CRYSTAL_FREQUENCY_IN_HZ     12000000                                  // 12MHz
//#define HF_CRYSTAL_FREQUENCY_IN_HZ     4000000                                  // 12MHz // Launch pad

#define MCLK_DESIRED_FREQUENCY_IN_KHZ  12000                                     // 26MHz
#define MCLK_FLLREF_RATIO              MCLK_DESIRED_FREQUENCY_IN_KHZ / ( UCS_REFOCLK_FREQUENCY / 1024 )    // Ratio = 250



//#define GPIO_ALL  GPIO_PIN0|GPIO_PIN1|GPIO_PIN2|GPIO_PIN3| \
//        GPIO_PIN4|GPIO_PIN5|GPIO_PIN6|GPIO_PIN7

uint32_t myACLK;
uint32_t mySMCLK;
uint32_t myMCLK;

/*
 * This function drives all the I/O's as output-low, to avoid floating inputs
 * (which cause extra power to be consumed).  This setting is compatible with
 * TI FET target boards, the F5529 Launchpad, and F5529 Experimenters Board;  
 * but may not be compatible with custom hardware, which may have components  
 * attached to the I/Os that could be affected by these settings.  So if using
 * other boards, this function may need to be modified.
 */
void USBHAL_initPorts(void)
{
#ifdef __MSP430_HAS_PORT1_R__
    GPIO_setOutputLowOnPin(GPIO_PORT_P1, GPIO_ALL);
    GPIO_setAsOutputPin(GPIO_PORT_P1, GPIO_ALL);
#endif

#ifdef __MSP430_HAS_PORT2_R__
    GPIO_setOutputLowOnPin(GPIO_PORT_P2, GPIO_ALL);
    GPIO_setAsOutputPin(GPIO_PORT_P2, GPIO_ALL);
#endif

#ifdef __MSP430_HAS_PORT3_R__
    GPIO_setOutputLowOnPin(GPIO_PORT_P3, GPIO_ALL);
    GPIO_setAsOutputPin(GPIO_PORT_P3, GPIO_ALL);
#endif

#ifdef __MSP430_HAS_PORT4_R__
    GPIO_setOutputLowOnPin(GPIO_PORT_P4, GPIO_ALL);
    GPIO_setAsOutputPin(GPIO_PORT_P4, GPIO_ALL);
#endif

#ifdef __MSP430_HAS_PORT5_R__
    GPIO_setOutputLowOnPin(GPIO_PORT_P5, GPIO_ALL);
    GPIO_setAsOutputPin(GPIO_PORT_P5, GPIO_ALL);
#endif

#ifdef __MSP430_HAS_PORT6_R__
    GPIO_setOutputLowOnPin(GPIO_PORT_P6, GPIO_ALL);
    GPIO_setAsOutputPin(GPIO_PORT_P6, GPIO_ALL);
#endif

#ifdef __MSP430_HAS_PORT7_R__
    GPIO_setOutputLowOnPin(GPIO_PORT_P7, GPIO_ALL);
    GPIO_setAsOutputPin(GPIO_PORT_P7, GPIO_ALL);
#endif

#ifdef __MSP430_HAS_PORT8_R__
    GPIO_setOutputLowOnPin(GPIO_PORT_P8, GPIO_ALL);
    GPIO_setAsOutputPin(GPIO_PORT_P8, GPIO_ALL);
#endif

#ifdef __MSP430_HAS_PORT9_R__
    GPIO_setOutputLowOnPin(GPIO_PORT_P9, GPIO_ALL);
    GPIO_setAsOutputPin(GPIO_PORT_P9, GPIO_ALL);
#endif

#ifdef __MSP430_HAS_PORTJ_R__
    GPIO_setOutputLowOnPin(GPIO_PORT_PJ, GPIO_ALL);
    GPIO_setAsOutputPin(GPIO_PORT_PJ, GPIO_ALL);
#endif

    GPIO_setOutputHighOnPin(GPIO_PORT_P1, GPIO_ALL);
    GPIO_setAsOutputPin(GPIO_PORT_P1, GPIO_ALL);


    // Init GPIO alternative function directly from timer
//    GPIO_setAsPeripheralModuleFunctionOutputPin(LED_PORT,LED_R + LED_G + LED_B);// Set the RGB LED GPIO to alternative function to power the LEDS directly from timer

}


void USBHAL_initClocks(uint32_t mclkFreq)
{

#if defined LAUNCH_PAD
    // Defined Clocks
#else
    #error "Validate clock and add if statement"
#endif

    myACLK = UCS_getACLK();
    mySMCLK =  UCS_getSMCLK();
    myMCLK = UCS_getMCLK();

    __no_operation();

    // Crystal Alternative function pins
    GPIO_setAsPeripheralModuleFunctionInputPin(
            GPIO_PORT_P5,                                // XIN  on P5.4
            GPIO_PIN3 +                                  // XT2OUT on P5.3
            GPIO_PIN2                                    // XT2IN  on P5.2
    );

    GPIO_setAsPeripheralModuleFunctionInputPin(
            GPIO_PORT_P5,
            GPIO_PIN4 +                                  // XIN on P5.4
            GPIO_PIN5                                    // XOUT  on P5.5
    );


    //       PMM_setVCore( PMM_CORE_LEVEL_3 );

    UCS_turnOnXT2( UCS_XT2_DRIVE_8MHZ_16MHZ );

    UCS_turnOnLFXT1(UCS_XCAP_0,UCS_XT1_DRIVE_0);

    UCS_setExternalClockSource(
            LF_CRYSTAL_FREQUENCY_IN_HZ,                                         // XT1CLK input
            HF_CRYSTAL_FREQUENCY_IN_HZ                                          // XT2CLK input
    );



    UCS_initClockSignal(
            UCS_FLLREF,
            UCS_REFOCLK_SELECT,
            UCS_CLOCK_DIVIDER_1);

    // Select XT2 as oscillator source for SMCLK
    UCS_initClockSignal(
            UCS_SMCLK,                                   // Clock you're configuring
            UCS_XT2CLK_SELECT,                           // Clock source
            UCS_CLOCK_DIVIDER_2                          // Divide down clock source by this much
    );

    UCS_initClockSignal(
            UCS_MCLK,
            UCS_XT2CLK_SELECT,
            UCS_CLOCK_DIVIDER_1
    );


    UCS_initClockSignal(
            UCS_ACLK,
            UCS_XT1CLK_SELECT,
            UCS_CLOCK_DIVIDER_1);

    //       UCS_initFLLSettle(
    //               mclkFreq/1000,
    //               mclkFreq/32768);


    myACLK = UCS_getACLK();
    mySMCLK =  UCS_getSMCLK();
    myMCLK = UCS_getMCLK();

    __no_operation();
    //    UCS_initClockSignal(
    //            UCS_FLLREF,
    //            UCS_REFOCLK_SELECT,
    //            UCS_CLOCK_DIVIDER_1);
    //
    //    UCS_initClockSignal(
    //            UCS_ACLK,
    //            UCS_REFOCLK_SELECT,
    //            UCS_CLOCK_DIVIDER_1);
    //
    //    UCS_initFLLSettle(
    //            mclkFreq/1000,
    //            mclkFreq/32768);

}

/*
 * Init I2C device for the LCD device
 */
void initI2C() {
    //Assign I2C pins to USCI_B0
    GPIO_setAsPeripheralModuleFunctionInputPin(
            GPIO_PORT_P3,
            GPIO_PIN0 + GPIO_PIN1
    );

    //Initialize Master
    USCI_B_I2C_initMasterParam param = {0};
    param.selectClockSource = USCI_B_I2C_CLOCKSOURCE_SMCLK;
    param.i2cClk = UCS_getSMCLK();
    param.dataRate = USCI_B_I2C_SET_DATA_RATE_400KBPS;
    USCI_B_I2C_initMaster(USCI_B0_BASE, &param);

    //Specify slave address
    USCI_B_I2C_setSlaveAddress(USCI_B0_BASE,
                               SLAVE_ADDRESS
    );

    //Set Transmit mode
    USCI_B_I2C_setMode(USCI_B0_BASE,
                       USCI_B_I2C_TRANSMIT_MODE
    );

    //Enable I2C Module to start operations
    USCI_B_I2C_enable(USCI_B0_BASE);
}

/*
 * Init The two attached Buttons, Used for User Feedback to the System.
 * The complete User Interface and reporting not defined Yet(Keyboard?)
 */
void initButton() {
    // Left button on the launch Pad
    GPIO_setAsInputPinWithPullUpResistor(GPIO_PORT_P2, GPIO_PIN1);
    GPIO_selectInterruptEdge(GPIO_PORT_P2, GPIO_PIN1,GPIO_HIGH_TO_LOW_TRANSITION);
    GPIO_clearInterrupt(GPIO_PORT_P2, GPIO_PIN1);
    GPIO_enableInterrupt(GPIO_PORT_P2, GPIO_PIN1);

    // Right button on the launch pad
    GPIO_setAsInputPinWithPullUpResistor(GPIO_PORT_P1, GPIO_PIN1);
    GPIO_selectInterruptEdge(GPIO_PORT_P1, GPIO_PIN1,GPIO_HIGH_TO_LOW_TRANSITION);
    GPIO_clearInterrupt(GPIO_PORT_P1, GPIO_PIN1);
    GPIO_enableInterrupt(GPIO_PORT_P1, GPIO_PIN1);



}


#pragma vector=PORT1_VECTOR
__interrupt void Port_1(void)
{
    __no_operation();
    GPIO_clearInterrupt(GPIO_PORT_P1, GPIO_PIN1);
}

#pragma vector=PORT2_VECTOR
__interrupt void Port_2(void)
{
    __no_operation();
    GPIO_clearInterrupt(GPIO_PORT_P2, GPIO_PIN1);
}
