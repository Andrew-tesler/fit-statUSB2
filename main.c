/**********************************************************
 * NAME: *
 * main.c
 *
 * PURPOSE: *
 * Main Program script
 *
 * GLOBAL VARIABLES: *
 * *
 * Variable Type Description *
 * -------- ---- ----------- *
 * *
 * DEVELOPMENT HISTORY: *
 * *
 * Date        Author       Release Description Of Change *
 * ----        ------       ------- --------------------- *
 * 26/08/2018   Andrew T.   1.0     initial Release
 * *
 *******************************************************************/


// General board libraries
#include <msp430.h>                                                                                     // General board file
#include <defines.c>                                                                                    // Project globals defines
#include <initBoard.h>                                                                                  // Ti Board specific functions
#include <string.h>                                                                                     // String library to handle the String
#include <stdlib.h>                                                                                     // atoi
#include "driverlib.h"                                                                                  // Ti Driver library for MSP430 Devices
#include "initTimers.h"                                                                                 // Timer specific functions
#include <stdio.h>

// LCD related
#include <Lcd_Driver/ssd1306_Driver.h>                                                                  // SSD1306 Driver
#include "images/images.h"                                                                              // Images file for LCD driver
#include "grlib.h"                                                                                      // TI Graphics library

// USB Related
#include "USB_config/descriptors.h"                                                                     // USB descriptors
#include "USB_API/USB_Common/device.h"                                                                  // Part of TI USP API library
#include "USB_API/USB_Common/usb.h"                                                                     // Part of TI USP API library
#include "USB_API/USB_CDC_API/UsbCdc.h"                                                                 // Part of TI USP API library USB CDC
#include "USB_app/usbConstructs.h"                                                                      // Part of TI USP API library
// LED related
#include "usbLed.h"                                                                                     // Help functions for the LED's



//*****************************************************************************************************
//
//  DEFINES
//
//*****************************************************************************************************
#define MAX_STR_LENGTH 64
#define BUFFER_SIZE 256
#define INFOB_START   (0x1900)


//*****************************************************************************************************
//
//   Function declarations
//
//*****************************************************************************************************
void printHelp(void);
void converIncomingColor(void);

uint8_t retInString (char* string);
uint8_t retInString (char* string);
char chrToHx(uint8_t);
uint32_t parseFadeTimer(uint8_t unformated[],uint8_t fadeCounter);
// Convert incoming color to formated color
Timer_A_initUpModeParam Timer_A_params = {0};     // TODO remove this


//*****************************************************************************************************
//
//   Parameters Initialization
//
//*****************************************************************************************************
//volatile uint8_t bCDCDataReceived_event = FALSE; // Indicates data has been rx'ed
//char wholeString[MAX_STR_LENGTH] = ""; // Entire input str from last 'return'
uint8_t i;                                                                                              // General counter value
uint8_t incomingColor[6];                                                                               // Array for incoming color data
uint8_t formatedColor[3];                                                                               // Formated array color data
uint8_t unformatedFade[MAX_FADE_DECIMAL] = "";                                                          // Unformatted Fade tempt storage
uint8_t transmitCounter = 0;
char dataBuffer[BUFFER_SIZE] = "";
char nl[2] = "\n";
char wholeString[MAX_STR_LENGTH] = "";                                                                  // Entire input str from last 'return'
char pieceOfString[MAX_STR_LENGTH] = "";                                                                // Holds the new addition to the string
char outString[MAX_STR_LENGTH] = "";                                                                    // Holds the outgoing string
char deviceSN[12];

// TODO probably can remove this values after adding the fitstatUSB code
uint16_t SlowToggle_Period = 20000 - 1;
uint16_t FastToggle_Period = 1000 - 1;

uint32_t decimals;

volatile uint8_t bCDCDataReceived_event = FALSE;                                                        // Flag set by event handler to indicate data has been received into USB buffer
volatile uint16_t led;

long wholeStringCounter;
long formated;

int seqCounter = 0;
int counterFade;
int fadeTimeCounter;
int n = 0;

// https://git-server/Andrew/fit-statUSB/wikis/Internal-Flash-Mapping                                   // Compulab Wiki page for memory mapping
// Revision information from Flash
char *MAJOR1_ptrB = (char *)INFOB_START;                                                                // Major Revision Start
char *MINOR1_ptrB = (char *)INFOB_START+2;                                                              // Minor Revision start
char *SERIAL_ptrB = (char *)INFOB_START+4;                                                              // Serial Number Start


void main(void)
{

    // USB
    PMM_setVCore(PMM_CORE_LEVEL_3);
    USBHAL_initPorts();           // Config GPIOS for low-power (output low)



    USBHAL_initClocks(12000000);   // Config clocks. MCLK=SMCLK=FLL=8MHz; ACLK=REFO=32kHz

    initI2C();
    // Init LCD i2c
    //    initTimer();           // Prepare timer for LED toggling
    USB_setup(TRUE, TRUE); // Init USB & events; if a host is present, connect

    __enable_interrupt();  // Enable interrupts globally

    // Set up the LCD
    Template_DriverInit();
    ssd1306_display(logo);
    ssd1306_startscrollright(0x00,0x0F);

    strncat(deviceSN,(char *)SERIAL_ptrB,10);
    strcat(deviceSN,"\r\n\r\n");
    fadeTimer = 300;                                                                                    // Default timer 300ms

    colorFadeTimer[MAX_SEQ_COLORS] = 500;                                                                // Last element initialization

    for (n=0;n < MAX_SEQ_COLORS;n++) {
        colorSeq[n][0] = 0;
        colorSeq[n][1] = 0;
        colorSeq[n][2] = 0;
        colorFadeTimer[n] = 300;

    }

    for (n = 0 ; n < MAX_FADE_DECIMAL ; n++) {
        unformatedFade[n] = 0x00;
    }
    __bis_SR_register( GIE );                                                                           // Enable interrupts globally


    __enable_interrupt();  // Enable interrupts globally

    // Gather information from the card
    //strcpy(deviceSN,"Serial No:\t\t\t1234567890\n\r");
    //  strcpy(deviceSN,"Device SN: 56987\t Rev.1.0\r\n\r\n");

    allOff();
    initTimers(0,10,10);
    currentRGBColor[2] = 5;


    //
    //    ssd1306_command(0x21);
    //    ssd1306_command(0x00);
    //    ssd1306_command(0x7F);
    //    ssd1306_command(0x00);
    //    ssd1306_command(0x22);
    //    ssd1306_command(0x00);
    //    ssd1306_command(0x07);





    //    ssd1306_drawPixel(1,5,1);
    //    ssd1306_drawPixel(2,5,1);
    //    ssd1306_drawPixel(3,5,1);
    //    ssd1306_drawPixel(4,5,1);
    //    ssd1306_drawPixel(5,5,1);


    //      __delay_cycles(500000);
    //      ssd1306_dim(0xFF);
    //      uint8_t i = 0;
    //      ssd1306_startscrollright(0x00,0x0F);
    //      ssd1306_invertDisplay(1);
    //      __delay_cycles(5000000);
    //      ssd1306_dim(0xAA);
    //      ssd1306_startscrollleft(0x00,0x0F);
    //
    //      __delay_cycles(5000000);
    //
    //
    //      ssd1306_stopscroll();
    //      //   clearDisplay();
    //      __delay_cycles(50000);
    //
    //      ssd1306_invertDisplay(1);
    //
    //      for (i = 0 ; i < 0xFF ; i++) {
    //          ssd1306_dim(i);
    //          __delay_cycles(50000);
    //      }
    //      ssd1306_dim(0x00);
    //
    //
    //
    //      ssd1306_invertDisplay(0);
    //
    //      ssd1306_drawPixel(0,0,1);
    //      ssd1306_drawPixel(125,50,1);
    //      ssd1306_drawPixel(128,64,1);
    //
    //      ssd1306_display(buffer);
    //      //    ssd1306_command(SSD1306_DISPLAYON);//--turn on oled panel
    //    Template_DriverInit();
    //Enter LPM0 with interrupts enabled

    while (1)
    {
        uint8_t i;

        // Check the USB state and directly main loop accordingly
        switch (USB_getConnectionState())
        {
        // This case is executed while your device is enumerated on the
        // USB host
        case ST_ENUM_ACTIVE:

            // Enter LPM0 (can't do LPM3 when active)
            __bis_SR_register(LPM0_bits + GIE);
            _NOP();
            // Exit LPM on USB receive and perform a receive operation
            ssd1306_display(logo);

            // If true, some data is in the buffer; begin receiving a cmd
            if (bCDCDataReceived_event){

                // Holds the new addition to the string
                char pieceOfString[MAX_STR_LENGTH] = "";

                // Holds the outgoing string
                char outString[MAX_STR_LENGTH] = "";

                // Add bytes in USB buffer to the string
                USBCDC_receiveDataInBuffer((uint8_t*)pieceOfString,
                                           MAX_STR_LENGTH,
                                           CDC0_INTFNUM); // Get the next piece of the string

                // Append new piece to the whole
                strcat(wholeString,pieceOfString);

                // Echo back the characters received
                USBCDC_sendDataInBackground((uint8_t*)pieceOfString,
                                            strlen(pieceOfString),CDC0_INTFNUM,0);

                // Has the user pressed return yet?
                if (retInString(wholeString)){

                    // Compare to string #1, and respond
                    if (!(strcmp(wholeString, "LED ON"))){

                        ssd1306_startscrollleft(0x00,0x0F);

                        // Turn off timer; no longer toggling LED
                        Timer_A_stop(TIMER_A0_BASE);

                        // Turn on LED P1.0
                        GPIO_setOutputHighOnPin(LED_PORT_BOARD, LED_PIN);

                        // Prepare the outgoing string
                        strcpy(outString,"\r\nLED is ON\r\n\r\n");

                        // Send the response over USB
                        USBCDC_sendDataInBackground((uint8_t*)outString,
                                                    strlen(outString),CDC0_INTFNUM,0);

                        // Compare to string #2, and respond
                    } else if (!(strcmp(wholeString, "LED OFF"))){
                        ssd1306_stopscroll();

                        // Turn off timer; no longer toggling LED
                        Timer_A_stop(TIMER_A0_BASE);

                        // Turn off LED P1.0
                        GPIO_setOutputLowOnPin(LED_PORT_BOARD, LED_PIN);

                        // Prepare the outgoing string
                        strcpy(outString,"\r\nLED is OFF\r\n\r\n");

                        // Send the response over USB
                        USBCDC_sendDataInBackground((uint8_t*)outString,
                                                    strlen(outString),CDC0_INTFNUM,0);

                        // Compare to string #3, and respond
                    } else if (!(strcmp(wholeString, "LED TOGGLE - SLOW"))){

                        // Turn off timer while changing toggle period
                        Timer_A_stop(TIMER_A0_BASE);

                        // Set timer period for slow LED toggle
                        Timer_A_params.timerPeriod = SlowToggle_Period;

                        Timer_A_initUpMode(TIMER_A0_BASE, &Timer_A_params);

                        // Start timer for toggling
                        Timer_A_startCounter(TIMER_A0_BASE,
                                             TIMER_A_UP_MODE);

                        // Prepare the outgoing string
                        strcpy(outString,
                               "\r\nLED is toggling slowly\r\n\r\n");

                        // Send the response over USB
                        USBCDC_sendDataInBackground((uint8_t*)outString,
                                                    strlen(outString),CDC0_INTFNUM,0);

                        // Compare to string #4, and respond
                    } else if (!(strcmp(wholeString,"LED TOGGLE - FAST"))){

                        // Turn off timer
                        Timer_A_stop(TIMER_A0_BASE);

                        // Set timer period for fast LED toggle
                        Timer_A_params.timerPeriod = FastToggle_Period;

                        Timer_A_initUpMode(TIMER_A0_BASE, &Timer_A_params);

                        // Start timer for toggling
                        Timer_A_startCounter(TIMER_A0_BASE,
                                             TIMER_A_UP_MODE);

                        // Prepare the outgoing string
                        strcpy(outString,
                               "\r\nLED is toggling fast\r\n\r\n");

                        // Send the response over USB
                        USBCDC_sendDataInBackground((uint8_t*)outString,
                                                    strlen(outString),CDC0_INTFNUM,0);

                        // Handle other
                    } else {

                        // Prepare the outgoing string
                        strcpy(outString,"\r\nNo such command!\r\n\r\n");

                        // Send the response over USB
                        USBCDC_sendDataInBackground((uint8_t*)outString,
                                                    strlen(outString),CDC0_INTFNUM,0);
                    }

                    // Clear the string in preparation for the next one
                    for (i = 0; i < MAX_STR_LENGTH; i++){
                        wholeString[i] = 0x00;
                    }
                }
                bCDCDataReceived_event = FALSE;
            }
            break;

            // These cases are executed while your device is disconnected from
            // the host (meaning, not enumerated); enumerated but suspended
            // by the host, or connected to a powered hub without a USB host
            // present.
        case ST_PHYS_DISCONNECTED:
        case ST_ENUM_SUSPENDED:
        case ST_PHYS_CONNECTED_NOENUM_SUSP:

            //Turn off LED P1.0
            GPIO_setOutputLowOnPin(LED_PORT_BOARD, LED_PIN);
            __bis_SR_register(LPM3_bits + GIE);
            _NOP();
            break;

            // The default is executed for the momentary state
            // ST_ENUM_IN_PROGRESS.  Usually, this state only last a few
            // seconds.  Be sure not to enter LPM3 in this state; USB
            // communication is taking place here, and therefore the mode must
            // be LPM0 or active-CPU.
        case ST_ENUM_IN_PROGRESS:
        default:;
        }

    }  // while(1)

    //END USB

    __delay_cycles(50);


    __bis_SR_register(LPM0_bits + GIE);
    __no_operation();

}

void printHelp() {

    // Prepare the first line of print
    strcpy(outString,"*******************************************************\n\n\r");
    // Send the response over USB
    USBCDC_sendDataInBackground((uint8_t*)outString,
                                strlen(outString),CDC0_INTFNUM,0);

    //    // add data to String of SN to test
    //    //strcat(deviceSN,"56987\t Rev.1.0\n\n\r");
    //    // Print device SN
    //    USBCDC_sendDataInBackground((uint8_t*)abramSerialStringDescriptor,              // Send Serial information
    //                                34,CDC0_INTFNUM,0);

    // Available commands, Broken to many line to simplify the look of the program
    // help command
    strcpy(outString,"P\t\t\t- Enter Device firmware update mode\n\n\r");
    // Send the response over USB
    USBCDC_sendDataInBackground((uint8_t*)outString,
                                strlen(outString),CDC0_INTFNUM,0);
    // device SN
    strcpy(outString,"?\t\t\t- Return device UUID #\n\n\r");
    // Send the response over USB
    USBCDC_sendDataInBackground((uint8_t*)outString,
                                strlen(outString),CDC0_INTFNUM,0);

    strcpy(outString,"#RRGGBB\t\t\t- Set LED color according to Hex color code\n\n\r");
    // Send the response over USB
    USBCDC_sendDataInBackground((uint8_t*)outString,
                                strlen(outString),CDC0_INTFNUM,0);

    strcpy(outString,"F\t\t\t- Set Fade transition Time in ms 'F1000'\n\n\r");
    // Send the response over USB
    USBCDC_sendDataInBackground((uint8_t*)outString,
                                strlen(outString),CDC0_INTFNUM,0);

    strcpy(outString,"G\t\t\t- Return current color, (rr,gg,bb)\n\n\r");
    // Send the response over USB
    USBCDC_sendDataInBackground((uint8_t*)outString,
                                strlen(outString),CDC0_INTFNUM,0);

    strcpy(outString,"B\t\t\t- Set Fade transition Colors B#RRGGBB-tttt#RRGGBB....\n\n\r");
    // Send the response over USB
    USBCDC_sendDataInBackground((uint8_t*)outString,
                                strlen(outString),CDC0_INTFNUM,0);

    strcpy(outString,"\t\t\t Fade transition after each color \n\n\r");
    // Send the response over USB
    USBCDC_sendDataInBackground((uint8_t*)outString,
                                strlen(outString),CDC0_INTFNUM,0);


    strcpy(outString,"\nFirmware Revision: V0.9.5\n\n\r");
    // Send the response over USB
    USBCDC_sendDataInBackground((uint8_t*)outString,
                                strlen(outString),CDC0_INTFNUM,0);

    // End of information Line
    strcpy(outString,"*******************************************************\r\n\r\n");
    // Send the response over USB
    USBCDC_sendDataInBackground((uint8_t*)outString,
                                strlen(outString),CDC0_INTFNUM,0);


}

// TODO change to more simplified option and add support for lower case string
char chrToHx(uint8_t number) {
    char formated;
    switch (number) {
    case 48:
        formated=0x00;
        break;
    case 49:
        formated=0x01;
        break;
    case 50:
        formated=0x02;
        break;
    case 51:
        formated=0x03;
        break;
    case 52:
        formated=0x04;
        break;
    case 53:
        formated=0x05;
        break;
    case 54:
        formated=0x06;
        break;
    case 55:
        formated=0x07;
        break;
    case 56:
        formated=0x08;
        break;
    case 57:
        formated=0x09;
        break;
    case 65:
        formated=0x0A;
        break;
    case 66:
        formated=0x0B;
        break;
    case 67:
        formated=0x0C;
        break;
    case 68:
        formated=0x0D;
        break;
    case 69:
        formated=0x0E;
        break;
    case 70:
        formated=0xF;
        break;
    }
    //    formated = number - 55;
    return formated;
    // return formated+0x00;
}


// Convert incoming color Asci to Decimal numbers and store in global
void converIncomingColor() {

    uint8_t tempTens,tempOnes;
    char buffer[2];

    formatedColor[0] = 0;                                                                               // Clear the array
    formatedColor[1] = 0;
    formatedColor[2] = 0;
    // Test if array place is not empty
    if (incomingColor[0] != 0x00) {
        // Convert to Hex received Red values
        sprintf(buffer,"%d", incomingColor[0]);
        tempTens = chrToHx(atol(buffer));
        sprintf(buffer,"%d", incomingColor[1]);
        tempOnes = chrToHx(atol(buffer));


        tempTens = (tempTens << 4);
        formatedColor[0] = tempTens|tempOnes;
    }

    if (incomingColor[2] != 0x00) {
        // Convert to Hex received Red values
        sprintf(buffer,"%d", incomingColor[2]);
        tempTens = chrToHx(atol(buffer));
        sprintf(buffer,"%d", incomingColor[3]);
        tempOnes = chrToHx(atol(buffer));


        tempTens = (tempTens << 4);
        formatedColor[1] = tempTens|tempOnes;

    }

    if (incomingColor[4] != 0x00) {
        // Convert to Hex received Red values
        sprintf(buffer,"%d", incomingColor[4]);
        tempTens = chrToHx(atol(buffer));
        sprintf(buffer,"%d", incomingColor[5]);
        tempOnes = chrToHx(atol(buffer));


        tempTens = (tempTens << 4);
        formatedColor[2] = tempTens|tempOnes;
    }
    // Send to the fade function
}

// Gets array of unformatted Decimal ACSCII and convert them to fade number that the program can use
uint32_t parseFadeTimer(uint8_t unformated[],uint8_t fadeCounter) {
    //    MAX_FADE_DECIMAL
    formated = 0;
    decimals = 1 ;                                                                             // Decimal number to calculated later
    //fadeTimer = 0;

    for (i = 0 ; i < fadeCounter ; i++) {
        decimals = decimals*10;
        unformated[i] = chrToHx(unformated[i]);                                                         // Convert to decimal and place again in the array
    }

    // For loop instead of power as importing math libraries no size for this code.
    for (i = 0 ; i <= fadeCounter ; i++ ) {                                                             // For loop that calculate the time fade value and store it

        decimals = decimals/10;                                                                         // Reduce the decimal size
        formated = formated + (unformated[i]*decimals);                                                 // Multiply and store the number
        unformated[i] = 0;

    }

    //    fadeTimer = formated;
    return formated;


}


////******************************************************************************
////
////This is the USCI_B0 interrupt vector service routine.
////
////******************************************************************************
//#if defined(__TI_COMPILER_VERSION__) || defined(__IAR_SYSTEMS_ICC__)
//#pragma vector=USCI_B0_VECTOR
//__interrupt
//#elif defined(__GNUC__)
//__attribute__((interrupt(USCI_B0_VECTOR)))
//#endif
//void USCI_B0_ISR (void)
//{
//    switch (__even_in_range(UCB0IV,12)){
//    case USCI_I2C_UCTXIFG:
//    {
//
//        //Check TX byte counter
//        if (transmitCounter < 7){
//            //Initiate send of character from Master to Slave
//            USCI_B_I2C_masterSendMultiByteNext(USCI_B0_BASE,
//                                               transmitData[transmitCounter][0]
//            );
//
//            USCI_B_I2C_masterSendMultiByteNext(USCI_B0_BASE,
//                                               transmitData[transmitCounter][1]
//            );
//
//            USCI_B_I2C_masterSendMultiByteStop(USCI_B0_BASE);
//
//            //Increment TX byte counter
//            transmitCounter++;
//        } else   {
//            //Initiate stop only
//            USCI_B_I2C_masterSendMultiByteStop(USCI_B0_BASE);
//
//            //Clear master interrupt status
//            USCI_B_I2C_clearInterrupt(USCI_B0_BASE,
//                                      USCI_B_I2C_TRANSMIT_INTERRUPT);
//
//            //Exit LPM0 on interrupt return
//            __bic_SR_register_on_exit(LPM0_bits);
//        }
//        break;
//    }
//    }
//}

/*
 * ======== UNMI_ISR ========
 */
#if defined(__TI_COMPILER_VERSION__) || (__IAR_SYSTEMS_ICC__)
#pragma vector = UNMI_VECTOR
__interrupt void UNMI_ISR (void)
#elif defined(__GNUC__) && (__MSP430__)
void __attribute__ ((interrupt(UNMI_VECTOR))) UNMI_ISR (void)
#else
#error Compiler not found!
#endif
{
    switch (__even_in_range(SYSUNIV, SYSUNIV_BUSIFG))
    {
    case SYSUNIV_NONE:
        __no_operation();
        break;
    case SYSUNIV_NMIIFG:
        __no_operation();
        break;
    case SYSUNIV_OFIFG:
        UCS_clearFaultFlag(UCS_XT2OFFG);
        UCS_clearFaultFlag(UCS_DCOFFG);
        SFR_clearInterrupt(SFR_OSCILLATOR_FAULT_INTERRUPT);
        break;
    case SYSUNIV_ACCVIFG:
        __no_operation();
        break;
    case SYSUNIV_BUSIFG:
        // If the CPU accesses USB memory while the USB module is
        // suspended, a "bus error" can occur.  This generates an NMI.  If
        // USB is automatically disconnecting in your software, set a
        // breakpoint here and see if execution hits it.  See the
        // Programmer's Guide for more information.
        SYSBERRIV = 0; //clear bus error flag
        USB_disable(); //Disable
    }
}



/*
 * ======== retInString ========
 */
// This function returns true if there's an 0x0D character in the string; and if
// so, it trims the 0x0D and anything that had followed it.
uint8_t retInString (char* string)
{
    uint8_t retPos = 0,i,len;
    char tempStr[MAX_STR_LENGTH] = "";

    strncpy(tempStr,string,strlen(string));  // Make a copy of the string
    len = strlen(tempStr);

    // Find 0x0D; if not found, retPos ends up at len
    while ((tempStr[retPos] != 0x0A) && (tempStr[retPos] != 0x0D) &&
            (retPos++ < len)) ;

    // If 0x0D was actually found...
    if ((retPos < len) && (tempStr[retPos] == 0x0D)){
        for (i = 0; i < MAX_STR_LENGTH; i++){ // Empty the buffer
            string[i] = 0x00;
        }

        //...trim the input string to just before 0x0D
        strncpy(string,tempStr,retPos);

        //...and tell the calling function that we did so
        return ( TRUE) ;

        // If 0x0D was actually found...
    } else if ((retPos < len) && (tempStr[retPos] == 0x0A)){
        // Empty the buffer
        for (i = 0; i < MAX_STR_LENGTH; i++){
            string[i] = 0x00;
        }

        //...trim the input string to just before 0x0D
        strncpy(string,tempStr,retPos);

        //...and tell the calling function that we did so
        return ( TRUE) ;
    } else if (tempStr[retPos] == 0x0D){
        for (i = 0; i < MAX_STR_LENGTH; i++){  // Empty the buffer
            string[i] = 0x00;
        }
        // ...trim the input string to just before 0x0D
        strncpy(string,tempStr,retPos);
        // ...and tell the calling function that we did so
        return ( TRUE) ;
    } else if (retPos < len){
        for (i = 0; i < MAX_STR_LENGTH; i++){  // Empty the buffer
            string[i] = 0x00;
        }

        //...trim the input string to just before 0x0D
        strncpy(string,tempStr,retPos);

        //...and tell the calling function that we did so
        return ( TRUE) ;
    }

    return ( FALSE) ; // Otherwise, it wasn't found
}

/*
 * ======== setTimer_A_Parameters ========
 */
// This function sets the timer A parameters
//void setTimer_A_Parameters()
//{
//    Timer_A_params.clockSource = TIMER_A_CLOCKSOURCE_ACLK;
//    Timer_A_params.clockSourceDivider = TIMER_A_CLOCKSOURCE_DIVIDER_1;
//    Timer_A_params.timerInterruptEnable_TAIE = TIMER_A_TAIE_INTERRUPT_DISABLE;
//    Timer_A_params.captureCompareInterruptEnable_CCR0_CCIE =
//            TIMER_A_CAPTURECOMPARE_INTERRUPT_ENABLE;
//    Timer_A_params.timerClear = TIMER_A_DO_CLEAR;
//    Timer_A_params.startTimer = false;
//}

/*
// * ======== initTimer ========
// */
//void initTimer (void)
//{
//    // Configure timer parameters
//    setTimer_A_Parameters();
//
//    // Start timer
//    Timer_A_clearTimerInterrupt(TIMER_A0_BASE);
//
//    // Set timer period to zero
//    Timer_A_params.timerPeriod = 0;
//
//    Timer_A_initUpMode(TIMER_A0_BASE, &Timer_A_params);
//}
//
///*
// * ======== TIMER1_A0_ISR ========
// */
//#if defined(__TI_COMPILER_VERSION__) || (__IAR_SYSTEMS_ICC__)
//#pragma vector=TIMER0_A0_VECTOR
//__interrupt void TIMER0_A0_ISR (void)
//#elif defined(__GNUC__) && (__MSP430__)
//void __attribute__ ((interrupt(TIMER0_A0_VECTOR))) TIMER0_A0_ISR (void)
//#else
//#error Compiler not found!
//#endif
//{
//    GPIO_toggleOutputOnPin(LED_PORT, LED_PIN);
//}

//Released_Version_5_20_06_02
