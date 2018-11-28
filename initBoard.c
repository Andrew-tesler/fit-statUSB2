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
 * NAME: initBoard.c
 *
 * PURPOSE: Collect all functions that initialize the board to init state
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
 * 26/08/2018   Andrew T.   0.1.0    initial Release
 * *
 * *
 *******************************************************************/

//*****************************************************************************************************
//
//  INCLUDE
//
//*****************************************************************************************************
#include <defines.c>                                                                                    // Define file
#include <initBoard.h>                                                                                  // Header file of the initboard
#include "msp430.h"                                                                                     // Ti MSP430 header file
#include "driverlib.h"                                                                                  // Ti Driver library file
#include "USB_API/USB_Common/device.h"                                                                  // Ti USB deice init file
#include "USB_config/descriptors.h"                                                                     // Ti USB descriptor file


#if defined LAUNCH_PAD
    #define LF_CRYSTAL_FREQUENCY_IN_HZ     32768                                                        // 32KHz
    #define HF_CRYSTAL_FREQUENCY_IN_HZ     4000000                                                      // 4MHz
    #define MCLK_DESIRED_FREQUENCY_IN_KHZ  12000                                                        // 12MHz
    #define MCLK_FLLREF_RATIO              MCLK_DESIRED_FREQUENCY_IN_KHZ / ( UCS_REFOCLK_FREQUENCY / 1024 )    // Ratio = 250

#elif defined FITSTATUSB2_V1
    #error "initBoard.c - Write correct defines for clock" // TODO
#endif


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


    // Board specific GPIO defines
#if defined LAUNCH_PAD

    // Crystal
    // X2OUT-P5.3, XT2IN-5.2. Soldered on board XTAL
    GPIO_setAsPeripheralModuleFunctionInputPin(GPIO_PORT_P5,GPIO_PIN3 + GPIO_PIN2);
    // XIN-P5.4, XOUT-P5.5. Soldered on board LFXTAL
    GPIO_setAsPeripheralModuleFunctionInputPin(GPIO_PORT_P5,GPIO_PIN4 + GPIO_PIN5);

    // I2C
    //Assign I2C pins to USCI_B0 and set the alternative function for them
    GPIO_setAsPeripheralModuleFunctionInputPin(GPIO_PORT_P3,GPIO_PIN0 + GPIO_PIN1);

    // LED
    // Set the Board Left LED to Output, Placed here as this LEDS will greatly change in the final board
    GPIO_setAsOutputPin(RED_LED_PORT,RED_LED_PIN);
    GPIO_setOutputHighOnPin(RED_LED_PORT,RED_LED_PIN);
    // Set the board Right Green LED to output High
    GPIO_setAsOutputPin(GREEN_LED_PORT,GREEN_LED_PIN);
    GPIO_setOutputHighOnPin(GREEN_LED_PORT,GREEN_LED_PIN);

#elif defined FITSTATUSB2_V1
    #error "initBoard.c - Write correct defines for GPIO"
    // TODO - XTAL Pins
    // TODO - I2C pins
    // TODO - buttons
#endif

    // Set the left button on the lunch pad as input high
    GPIO_setAsInputPinWithPullUpResistor(LEFT_BUTTON_PORT, LEFT_BUTTON_PIN);

    // Set the Right button on the lunch pad as input high
    GPIO_setAsInputPinWithPullUpResistor(RIGHT_BUTTON_PORT, RIGHT_BUTTON_PIN);

    // Set the RGB LED GPIO to alternative function to power the LEDS directly from timer
    GPIO_setAsPeripheralModuleFunctionOutputPin(LED_PORT,LED_R + LED_G + LED_B);





}


void USBHAL_initClocks(uint32_t mclkFreq)
{

#if defined LAUNCH_PAD
    // Initiate the HFXTAL
    UCS_turnOnXT2( UCS_XT2_DRIVE_8MHZ_16MHZ );
    // Initiate the LFXTAL
    UCS_turnOnLFXT1(UCS_XCAP_0,UCS_XT1_DRIVE_0);
    // Set the frequency to the external xtal
    UCS_setExternalClockSource( LF_CRYSTAL_FREQUENCY_IN_HZ,HF_CRYSTAL_FREQUENCY_IN_HZ);

    // Set the fll reference as the XT1 CLK
    UCS_initClockSignal(UCS_FLLREF,UCS_XT1CLK_SELECT,UCS_CLOCK_DIVIDER_1);
    // Select XT2 as oscillator source for SMCLK with divider 2
    UCS_initClockSignal(UCS_SMCLK,UCS_XT2CLK_SELECT,UCS_CLOCK_DIVIDER_2);
    // Select XT2 as oscillator source for the MCLK
    UCS_initClockSignal(UCS_MCLK,UCS_XT2CLK_SELECT,UCS_CLOCK_DIVIDER_1);

#elif defined FITSTATUSB2_V1
    #error "initBoard.c - Write correct defines Clock"
    // TODO - Clock

#endif


    // Store Clock freq for debugging
    myACLK = UCS_getACLK();
    mySMCLK =  UCS_getSMCLK();
    myMCLK = UCS_getMCLK();
    // Needed for setting break point
    __no_operation();
}

/*
 * Init I2C As master for controlling the LCD
 *
 */
void initI2C() {

    //Initialize Master
    USCI_B_I2C_initMasterParam param = {0};

    param.selectClockSource = USCI_B_I2C_CLOCKSOURCE_SMCLK;                                             // Set SMCLK as SPI Clock source
    param.i2cClk = UCS_getSMCLK();                                                                      // Get the SPI clock the same as SMCLK
    param.dataRate = USCI_B_I2C_SET_DATA_RATE_400KBPS;                                                  // Set Data rate to 400KBS

    USCI_B_I2C_initMaster(USCI_B0_BASE, &param);                                                        // Init I2C based on the parameters provided

    USCI_B_I2C_setSlaveAddress(USCI_B0_BASE,SLAVE_ADDRESS);                                             // Set the I2C to communicate using slave address
    USCI_B_I2C_setMode(USCI_B0_BASE,USCI_B_I2C_TRANSMIT_MODE);                                          // Set I2C to Transmit mode
    USCI_B_I2C_enable(USCI_B0_BASE);                                                                    //Enable I2C Module to start operations
}

/*
 * Init The two attached Buttons, Used for User Feedback to the System.
 * The complete User Interface and reporting not defined Yet(Keyboard?)
 */
void initButton() {

    GPIO_selectInterruptEdge(LEFT_BUTTON_PORT, LEFT_BUTTON_PIN,GPIO_HIGH_TO_LOW_TRANSITION);            // Set Interrupt edge from high to low
    GPIO_clearInterrupt(LEFT_BUTTON_PORT, LEFT_BUTTON_PIN);                                             // Clear interrupt
    GPIO_enableInterrupt(LEFT_BUTTON_PORT, LEFT_BUTTON_PIN);                                            // Enable interrupt

    GPIO_selectInterruptEdge(RIGHT_BUTTON_PORT, RIGHT_BUTTON_PIN,GPIO_HIGH_TO_LOW_TRANSITION);          // Set Interrupt edge from high to low
    GPIO_clearInterrupt(RIGHT_BUTTON_PORT, RIGHT_BUTTON_PIN);                                           // Clear interrupt
    GPIO_enableInterrupt(RIGHT_BUTTON_PORT, RIGHT_BUTTON_PIN);                                          // Enable interrupt
}

// ISR for the 2 buttons
#pragma vector=PORT1_VECTOR
__interrupt void Port_1(void)
{
    __no_operation();
    GPIO_clearInterrupt(RIGHT_BUTTON_PORT, RIGHT_BUTTON_PIN);
}

#pragma vector=PORT2_VECTOR
__interrupt void Port_2(void)
{
    __no_operation();
    GPIO_clearInterrupt(LEFT_BUTTON_PORT, LEFT_BUTTON_PIN);
}
