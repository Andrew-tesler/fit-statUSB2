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
#include <Lcd_Driver/ssd1306_Driver.h>
#include <msp430.h>
#include "grlib.h"
#include "images/images.h"
#include "driverlib.h"
#include "globals.h"


uint8_t transmitCounter = 0;


//Graphics_Context g_sContext;

#if defined(__IAR_SYSTEMS_ICC__)
int16_t __low_level_init(void) {
    // Stop WDT (Watch Dog Timer)
    WDTCTL = WDTPW + WDTHOLD;
    return(1);
}

#endif

void main(void)
{

    __delay_cycles(50);

    // Set up the LCD
    Template_DriverInit();
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

    ssd1306_display(logo);
    __delay_cycles(500000);
    ssd1306_dim(0xFF);
    uint8_t i = 0;
    ssd1306_startscrollright(0x00,0x0F);

    __delay_cycles(5000000);
    ssd1306_dim(0xAA);
    ssd1306_startscrollleft(0x00,0x0F);

    for (i = 0 ; i < 0xFF ; i++) {
        __delay_cycles(50000);
        ssd1306_invertDisplay(1);
        __delay_cycles(50000);
        ssd1306_invertDisplay(0);
    }
    __delay_cycles(5000000);

    ssd1306_stopscroll();
    //   clearDisplay();
    __delay_cycles(50000);

    ssd1306_invertDisplay(1);

    for (i = 0 ; i < 0xFF ; i++) {
        ssd1306_dim(i);
        __delay_cycles(50000);
    }
    ssd1306_dim(0x00);


   ssd1306_invertDisplay(0);
    //    ssd1306_command(SSD1306_DISPLAYON);//--turn on oled panel
    //    Template_DriverInit();
    //Enter LPM0 with interrupts enabled
    __bis_SR_register(LPM0_bits + GIE);
    __no_operation();

}



//******************************************************************************
//
//This is the USCI_B0 interrupt vector service routine.
//
//******************************************************************************
#if defined(__TI_COMPILER_VERSION__) || defined(__IAR_SYSTEMS_ICC__)
#pragma vector=USCI_B0_VECTOR
__interrupt
#elif defined(__GNUC__)
__attribute__((interrupt(USCI_B0_VECTOR)))
#endif
void USCI_B0_ISR (void)
{
    switch (__even_in_range(UCB0IV,12)){
    case USCI_I2C_UCTXIFG:
    {

        //Check TX byte counter
        if (transmitCounter < 7){
            //Initiate send of character from Master to Slave
            USCI_B_I2C_masterSendMultiByteNext(USCI_B0_BASE,
                                               transmitData[transmitCounter][0]
            );

            USCI_B_I2C_masterSendMultiByteNext(USCI_B0_BASE,
                                               transmitData[transmitCounter][1]
            );

            USCI_B_I2C_masterSendMultiByteStop(USCI_B0_BASE);

            //Increment TX byte counter
            transmitCounter++;
        } else   {
            //Initiate stop only
            USCI_B_I2C_masterSendMultiByteStop(USCI_B0_BASE);

            //Clear master interrupt status
            USCI_B_I2C_clearInterrupt(USCI_B0_BASE,
                                      USCI_B_I2C_TRANSMIT_INTERRUPT);

            //Exit LPM0 on interrupt return
            __bic_SR_register_on_exit(LPM0_bits);
        }
        break;
    }
    }
}

