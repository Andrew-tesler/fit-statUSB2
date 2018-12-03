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
 * NAME: ssd1306_Driver.c
 *
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
 * 27/11/2018  Andrew T.     0.1.0     initial Release
 *
 * *
 *******************************************************************/

//*****************************************************************************
//
// Include Files
//
//*****************************************************************************
#include <defines.c>
#include <Lcd_Driver/ssd1306_Driver.h>
#include <msp430.h>
#include "grlib.h"
#include "driverlib.h"
#include "FontPack.h"

//*****************************************************************************
//
// Global Variables
//
//*****************************************************************************
/* Global buffer for the display. This is especially useful on 1BPP, 2BPP, and 4BPP
   displays. This allows you to update pixels while reading the neighboring pixels
   from the buffer instead of a read from the LCD controller. A buffer is not required
   as a read followed by a write can be used instead.*/
//uint8_t Template_Memory[(LCD_X_SIZE * LCD_Y_SIZE * BPP + 7) / 8];
//    uint16_t vccstate = 0x00;
//    // Init sequence
//    ssd1306_command(SSD1306_DISPLAYOFF);                    // 0xAE
//    ssd1306_command(SSD1306_SETDISPLAYCLOCKDIV);            // 0xD5
//    ssd1306_command(0x80);                                  // the suggested ratio 0x80
//
//    ssd1306_command(SSD1306_SETMULTIPLEX);                  // 0xA8
//    ssd1306_command(0x3F);                                  // SSD1306_LCDHEIGHT - 1
//
//    ssd1306_command(SSD1306_SETDISPLAYOFFSET);              // 0xD3
//    ssd1306_command(0x00);                                   // no offset
//    ssd1306_command(SSD1306_SETSTARTLINE);                   // line #0
//    ssd1306_command(SSD1306_CHARGEPUMP);                    // 0x8D
//    if (vccstate == SSD1306_EXTERNALVCC)
//    { ssd1306_command(0x10); }
//    else
//    { ssd1306_command(0x14); }
//    ssd1306_command(SSD1306_MEMORYMODE);                    // 0x20
//    ssd1306_command(0x00);                                  // 0x0 act like ks0108
//    ssd1306_command(0xA1);                                  // SSD1306_SEGREMAP | 0x1
//    ssd1306_command(SSD1306_COMSCANDEC);                    // 0xC8
//
//#if defined SSD1306_128_32
//    ssd1306_command(SSD1306_SETCOMPINS);                    // 0xDA
//    ssd1306_command(0x02);
//    ssd1306_command(SSD1306_SETCONTRAST);                   // 0x81
//    ssd1306_command(0x8F);
//
//#elif defined SSD1306_128_64
//    ssd1306_command(SSD1306_SETCOMPINS);                    // 0xDA
//    ssd1306_command(0x12);
//    ssd1306_command(SSD1306_SETCONTRAST);                   // 0x81
//    if (vccstate == SSD1306_EXTERNALVCC)
//    { ssd1306_command(0x9F); }
//    else
//    { ssd1306_command(0xCF); }
//
//#elif defined SSD1306_96_16
//    ssd1306_command(SSD1306_SETCOMPINS);                    // 0xDA
//    ssd1306_command(0x2);   //ada x12
//    ssd1306_command(SSD1306_SETCONTRAST);                   // 0x81
//    if (vccstate == SSD1306_EXTERNALVCC)
//    { ssd1306_command(0x10); }
//    else
//    { ssd1306_command(0xAF); }
//
//#endif
//
//    ssd1306_command(SSD1306_SETPRECHARGE);                  // 0xd9
//    if (vccstate == SSD1306_EXTERNALVCC)
//    { ssd1306_command(0x22); }
//    else
//    { ssd1306_command(0xF1); }
//    ssd1306_command(SSD1306_SETVCOMDETECT);                 // 0xDB
//    ssd1306_command(0x40);
//    ssd1306_command(SSD1306_DISPLAYALLON_RESUME);           // 0xA4
//    ssd1306_command(SSD1306_NORMALDISPLAY);                 // 0xA6
//
//    ssd1306_command(SSD1306_DEACTIVATE_SCROLL);             // 0x2E
//
//    ssd1306_command(SSD1306_DISPLAYON);//--turn on oled panel   0x2F
//ssd1306_DriverInit(void)
//{
//    uint16_t vccstate = 0x00;
//    // Init sequence
//    ssd1306_command(SSD1306_DISPLAYOFF);                    // 0xAE
//    ssd1306_command(SSD1306_SETDISPLAYCLOCKDIV);            // 0xD5
//    ssd1306_command(0x80);                                  // the suggested ratio 0x80
//
//    ssd1306_command(SSD1306_SETMULTIPLEX);                  // 0xA8
//    ssd1306_command(0x3F);                                  // SSD1306_LCDHEIGHT - 1
//
//    ssd1306_command(SSD1306_SETDISPLAYOFFSET);              // 0xD3
//    ssd1306_command(0x00);                                   // no offset
//    ssd1306_command(SSD1306_SETSTARTLINE);                   // line #0
//    ssd1306_command(SSD1306_CHARGEPUMP);                    // 0x8D
//    if (vccstate == SSD1306_EXTERNALVCC)
//    { ssd1306_command(0x10); }
//    else
//    { ssd1306_command(0x14); }
//    ssd1306_command(SSD1306_MEMORYMODE);                    // 0x20
//    ssd1306_command(0x00);                                  // 0x0 act like ks0108
//    ssd1306_command(0xA1);                                  // SSD1306_SEGREMAP | 0x1
//    ssd1306_command(SSD1306_COMSCANDEC);                    // 0xC8
//
//#if defined SSD1306_128_32
//    ssd1306_command(SSD1306_SETCOMPINS);                    // 0xDA
//    ssd1306_command(0x02);
//    ssd1306_command(SSD1306_SETCONTRAST);                   // 0x81
//    ssd1306_command(0x8F);
//
//#elif defined SSD1306_128_64
//    ssd1306_command(SSD1306_SETCOMPINS);                    // 0xDA
//    ssd1306_command(0x12);
//    ssd1306_command(SSD1306_SETCONTRAST);                   // 0x81
//    if (vccstate == SSD1306_EXTERNALVCC)
//    { ssd1306_command(0x9F); }
//    else
//    { ssd1306_command(0xCF); }
//
//#elif defined SSD1306_96_16
//    ssd1306_command(SSD1306_SETCOMPINS);                    // 0xDA
//    ssd1306_command(0x2);   //ada x12
//    ssd1306_command(SSD1306_SETCONTRAST);                   // 0x81
//    if (vccstate == SSD1306_EXTERNALVCC)
//    { ssd1306_command(0x10); }
//    else
//    { ssd1306_command(0xAF); }
//
//#endif
//
//    ssd1306_command(SSD1306_SETPRECHARGE);                  // 0xd9
//    if (vccstate == SSD1306_EXTERNALVCC)
//    { ssd1306_command(0x22); }
//    else
//    { ssd1306_command(0xF1); }
//    ssd1306_command(SSD1306_SETVCOMDETECT);                 // 0xDB
//    ssd1306_command(0x40);
//    ssd1306_command(SSD1306_DISPLAYALLON_RESUME);           // 0xA4
//    ssd1306_command(SSD1306_NORMALDISPLAY);                 // 0xA6
//
//    ssd1306_command(SSD1306_DEACTIVATE_SCROLL);             // 0x2E
//
//    ssd1306_command(SSD1306_DISPLAYON);//--turn on oled panel   0x2F
//
//}

char SSD1306_init[] = {


                       SSD1306_DISPLAYOFF,
                       SSD1306_SETDISPLAYCLOCKDIV,
                       0x80,
                       SSD1306_SETMULTIPLEX,
                       0x3F,
                       SSD1306_SETDISPLAYOFFSET,
                       0x00,
                       SSD1306_SETSTARTLINE,
                       SSD1306_CHARGEPUMP,
                       0x10,
                       SSD1306_MEMORYMODE,                   // 0x20
                       0x00,                                // 0x0 act like ks0108
                       0xA1,                                  // SSD1306_SEGREMAP | 0x1
                       SSD1306_COMSCANDEC,
                       SSD1306_SETCOMPINS,                    // 0xDA
                       0x12,
                       SSD1306_SETCONTRAST,                   // 0x81
                       0x9F,
                       SSD1306_SETPRECHARGE,                 // 0xd9
                       0x22,
                       SSD1306_SETVCOMDETECT,                 // 0xDB
                       0x40,
                       SSD1306_DISPLAYALLON_RESUME,           // 0xA4
                       SSD1306_NORMALDISPLAY,                 // 0xA6
                       SSD1306_DEACTIVATE_SCROLL,           // 0x2E
                       0x2F
};

void SSD1306Init( void )
{
//    OLED_DESELECT;

//    OLED_COMMAND;

//    OLED_RES_LOW;

    // Delay for 200ms at 16Mhz
//    __delay_cycles(3200000);

//    OLED_RES_HIGH;

//    __delay_cycles(1600000);

    //TRIGGER;

    SSD1306SendCommand(SSD1306_init, sizeof SSD1306_init);

}

/* Function    : SSD1306SendCommand( char *data, int i )
 * Description : Sends a command to the OLED display
 * Input       : Command pointer and number of bytes to transfer
 * Output      : None
 * gwd
 */
void SSD1306SendCommand( char *data, int i )
{
    __disable_interrupt();

    uint8_t control = 0x00;

    while(i)
    {

        USCI_B_I2C_masterSendMultiByteStart(USCI_B0_BASE,control);

        USCI_B_I2C_masterSendMultiByteNext(USCI_B0_BASE,*data);

        USCI_B_I2C_masterSendMultiByteStop(USCI_B0_BASE);

        __delay_cycles(70);

        //
        data++;             // increment pointer
        //
        i--;                // decrement byte counter
    }


    __enable_interrupt();
}

/* Function    : SSD1306SendData( char c )
 * Description : Sends data to the OLED display
 * Input       : Data
 * Output      : None
 */
void SSD1306SendData( char *data, int i )
{
    __disable_interrupt();

    uint8_t control = 0x00;

    while(i)
    {



        USCI_B_I2C_masterSendMultiByteStart(USCI_B0_BASE,control);

        USCI_B_I2C_masterSendMultiByteNext(USCI_B0_BASE,*data);

        USCI_B_I2C_masterSendMultiByteStop(USCI_B0_BASE);

        __delay_cycles(50);

        //
        data++;             // increment pointer
        //
        i--;                // decrement byte counter

    }


    __enable_interrupt();
}

/* Function     : setAddress(char page, char column)
 * Description  : sets position of LCD RAM
 * Input        : page (0-7), column (0-127)
 * Output       : none
 */
void setAddress( char page, char column )
{

    char pageAddress[] = {SSD1306_PAGE_START_ADDRESS};
    char columnAddress[] = { SSD1306_COLUMNADDRESS, SSD1306_COLUMNADDRESS_MSB, SSD1306_COLUMNADDRESS_LSB };

    if (page > SSD1306_MAXROWS)
    {
        page = SSD1306_MAXROWS;
    }

    if (column > SSD1306_LCDWIDTH)
    {
        column = SSD1306_LCDWIDTH;
    }

    pageAddress[0] = SSD1306_PAGE_START_ADDRESS | (SSD1306_MAXROWS - page);

    columnAddress[0] = SSD1306_COLUMNADDRESS;
    columnAddress[1] = SSD1306_COLUMNADDRESS_MSB | column;
    columnAddress[2] = SSD1306_COLUMNADDRESS_LSB;

    //__no_operation();

    SSD1306SendCommand(pageAddress, 1);
    SSD1306SendCommand(columnAddress, 3);

}

/* Function     : clearScreen(void)
 * Description  : wipes data in memory to 0x00
 * Input        : none
 * Output       : blank screen (0x00)
 */
void clearScreen(void)
{
    char ramData[] = {0x00};

    char i,j;

    for(i=0; i < 8 ;i++)
    {
        setAddress(i,0);

        for(j=0; j < SSD1306_LCDWIDTH; j++)
        {
            SSD1306SendData(ramData, 1);
        }
    }
}

/* Function     : charDraw(char row, char column, int data)
 * Description  : write char to address
 * Input        : (row, column), data
 * Output       : char at address
 */
void charDraw(char row, char column, int data)
{
    int h;

    if (row > SSD1306_MAXROWS)
    {
        row = SSD1306_MAXROWS;
    }

    if (column > SSD1306_LCDWIDTH)
    {
        column = SSD1306_LCDWIDTH;
    }

    if ( data < 32 || data > 129 )
    {
        data = '.';
    }

    h = (data - 32) * 6;

    setAddress(row, column);
    SSD1306SendData( (char *)FONT6x8 + h, 6 );

}

/* Function     : stringDraw(char row, char column, char *word)
 * Description  : write string to address
 * Input        : (row, column), data
 * Output       : char at address
 */
void stringDraw( char row, char column, char *word)
{
    char a = 0;

    if (row > SSD1306_MAXROWS)
    {
        row = SSD1306_MAXROWS;
    }

    if (column > SSD1306_LCDWIDTH)
    {
        column = SSD1306_LCDWIDTH;
    }

    while (word[a] != 0)
    {
        if (word[a] != 0x0A)
        {
            if (word[a] != 0x0D)
            {
                charDraw(row, column, word[a]);

                __no_operation();

                column += 6;

                if (column >= (SSD1306_LCDWIDTH - 6 ))
                {
                    column = 0;
                    if ( row < SSD1306_MAXROWS )
                        row++;
                    else
                        row = 0;
                }

            }
            else
            {
                if ( row < SSD1306_MAXROWS )
                    row++;
                else
                    row = 0;
                column = 0;
            }
            a++;
        }
    }
}

/* Function     : pixelDraw(char x, char y)
 * Description  : draw individual pixel at coordinate
 * Input        : X,Y coordinates
 * Output       : single pixel
 */
void pixelDraw(char x, char y)
{
    char page, temp;
    char coordinate[] = {0x00};

    if (x > SSD1306_LCDWIDTH - 1)
    {
        x = SSD1306_LCDWIDTH - 1;
    }

    if (y > SSD1306_LCDHEIGHT - 1)
    {
        y = SSD1306_LCDHEIGHT - 1;
    }

    page = y / 8;
    temp = 0x80 >> (y % 8);
    coordinate[0] = temp;

    setAddress(page,x);
    SSD1306SendData(coordinate, 1);

}

/* Function     : horizontalLine(char xStart, char xStop, char y)
 * Description  : draw horizontal line from xStart to xStop
 * Input        : X Start & Stop coordinate, Y
 * Output       : display horizontal line
 */
void horizontalLine(char xStart, char xStop, char y)
{
    char temp = 0;
    char page, a;
    char ramData[] = { 0x00 };

    if (xStart > SSD1306_LCDWIDTH - 1)
    {
        xStart = SSD1306_LCDWIDTH - 1;
    }

    if (xStop > SSD1306_LCDWIDTH - 1)
    {
        xStop = SSD1306_LCDWIDTH - 1;
    }

    if (y > SSD1306_LCDHEIGHT - 1)
    {
        y = SSD1306_LCDHEIGHT - 1;
    }

    if (xStart > xStop)
    {
        temp = xStart;
        xStart = xStop;
        xStop = temp;
    }

    page = y / 8;
    temp = 0x80 >> (y %8);

    a = xStart;
    ramData[0] = temp;

    setAddress(page, xStart);

    while (a <= xStop)
    {
        SSD1306SendData(ramData, 1);
        a++;
    }
}

/* Function     : verticalLine(char x, char yStart, char yStop)
 * Description  : draw vertical line from yStart to yStop
 * Input        : Y Start & Stop coordinate, X
 * Output       : display vertical line
 */
void verticalLine(char x, char yStart, char yStop)
{
    char temp1 = 0, temp2 = 0;
    char page1, page2, pageStart;
    char a;
    char ramData1[] = {0x00};
    char ramData2[] = {0x00};

    if (x > SSD1306_LCDWIDTH - 1)
    {
        x = SSD1306_LCDWIDTH - 1;
    }

    if (yStart > SSD1306_LCDHEIGHT - 1)
    {
        yStart = SSD1306_LCDHEIGHT - 1;
    }

    if (yStop > SSD1306_LCDHEIGHT - 1)
    {
        yStop = SSD1306_LCDHEIGHT - 1;
    }

    if (yStart > yStop)
    {
        temp1 = yStart;
        yStart = yStop;
        yStop = temp1;
    }

    page1 = yStart / 8;
    page2 = yStop / 8;
    pageStart = yStart % 8;

    if (page1 != page2)
    {
        if ( pageStart > 0)
        {
            temp1 = 0xFF00 >> pageStart;
            temp1 = temp1 ^ 0xFF;
        }
        else
        {
            temp1 = 0xFF;
        }
    }
    else
    {
        temp1 = 0;

        a = yStart - (page1 * 8);
        a = 0xFF00 >> a;
        temp2 = temp2 ^ a;
    }

    ramData1[0] = temp1;

    setAddress(page1,x);
    SSD1306SendData(ramData1, 1);

    a = page1 + 1;
    ramData1[0] = 0xFF;

    while (a < page2)
    {
        setAddress(a, x);
        SSD1306SendData(ramData1, 1);
        a++;
    }

    temp2 = 8 - (yStop % 8);
    temp2--;
    temp2 = 0xFF << temp2;

    ramData2[0] = temp2;

    setAddress(page2, x);
    SSD1306SendData(ramData2, 1);
}

/* Function     : imageDraw(const char IMAGE[], char row, char column)
 * Description  : draw image at row, column
 * Input        : image, row, column
 * Output       : display image
 */
// from TI_DogsLCD_HAL
void imageDraw(const char IMAGE[], char row, char column)
{
    char a, height, width;

    width = IMAGE[0];
    height = IMAGE[1];

    for ( a = 0; a < height; a++)
    {
        setAddress(row + a, column);
        SSD1306SendData((char *)IMAGE + 2 + a * width, width);
    }
}


// circleDraw function is not complete. needs checks for page surround x-axis for proper column fill

/* Function     : circleDraw(register int x, register int y, int r)
 * Description  : draw circle at x,y of radius r
 * Input        : x,y, radius
 * Output       : display circle
 */
void circleDraw(register int x, register int y, int r)
{
    register int xx = -r;
    register int yy = 0;
    register int e = 2 - (2 * r);
    do {
        pixelDraw(x - xx, y + yy);
        pixelDraw(x - yy, y - xx);
        pixelDraw(x + xx, y - yy);
        pixelDraw(x + yy, y + xx);
        if(e >  xx) e += ((++xx << 1) + 1);
        if(e <= yy) e += ((++yy << 1) + 1);
    } while (xx < 0);
}


/* Function    : Fill_RAM( unsigned char c )
 * Description : Fills the OLED with one particular data
 * Input       : Data
 * Output      : None
 */
void Fill_RAM( char data )
{
    unsigned char i,j;

    char ramData[] = { 0x00};

    ramData[0] = data;

    for(i=0; i < 8 ;i++)
    {
        setAddress(i,0);

        for(j=0; j < SSD1306_LCDWIDTH; j++)
        {
            SSD1306SendData(ramData, 1);
        }
    }
}

/* Function    : Fill_RAM_PAGE
 * Description : Fills an OLED page with a particular data
 * Input       : page no.[0-7], Data
 * Output      : None
 */
void Fill_RAM_PAGE(unsigned char page, char data)
{
    unsigned char j;

    char ramData[] = { 0x00 };

    ramData[0] = data;

    setAddress(page,0);

    for(j=0; j < SSD1306_LCDWIDTH ;j++)
    {
        SSD1306SendData(ramData, 1);
    }
}

void Set_Contrast_Control(unsigned char d)
{
    char ramData[] = {SSD1306_SETCONTRAST, 0x00};
    ramData[1] = d;

    SSD1306SendCommand(ramData, 2);
}

void Set_Inverse_Display(unsigned char d)
{
    // 0 = normal, 1 = inverted

    char ramData[] = {SSD1306_NORMALDISPLAY};
    ramData[0] = ramData[0] + d;

    SSD1306SendCommand(ramData, 1);
}

void Set_Display_On_Off(unsigned char d)
{
    // 0 = off, 1 = on

    char ramData[] = {SSD1306_DISPLAYOFF};
    ramData[0] = ramData[0] + d;

    SSD1306SendCommand(ramData, 1);
}

//
//
////*****************************************************************************
////
//// Suggested functions to help facilitate writing the required functions below
////
////*****************************************************************************
//
//// Writes data to the LCD controller
//static void
//WriteData(uint16_t usData)
//{
//    /* Write data to the LCD controller. For instance this can be bit banged
//       with 6800 or 8080 protocol or this could be the SPI routine for a SPI LCD */
//}
//
//// Writes a command to the LCD controller
//static void
//WriteCommand(uint8_t ucCommand)
//{
//    /* This function is typically very similar (sometimes the same) as WriteData()
//       The difference is that this is for the LCD to interpret commands instead of pixel
//       data. For instance in 8080 protocol, this means pulling the DC line low.*/
//}
//
//// Sets the pixel address of the LCD driver
//void SetAddress(int16_t lX,
//                int16_t lY)
//{
//    /* This function typically writes commands (using WriteCommand()) to the
//        LCD to tell it where to move the cursor for the next pixel to be drawn. */
//}
//
//// Initializes the pins required for the GPIO-based LCD interface.
//// This function configures the GPIO pins used to control the LCD display
//// when the basic GPIO interface is in use. On exit, the LCD controller
//// has been reset and is ready to receive command and data writes.
//static void
//InitGPIOLCDInterface(void)
//{
//    /* Initialize the hardware to configure the ports properly for communication */
//}
//
//// Initialize DisplayBuffer.
//// This function initializes the display buffer and discards any cached data.
//static void
//InitLCDDisplayBuffer(uint32_t ulValue)
//{
//    uint16_t i = 0,j = 0;
//    for(i = 0; i < LCD_Y_SIZE; i++)
//    {
//        for(j = 0; j < (LCD_X_SIZE * BPP + 7) / 8; j++)
//        {
//            Template_Memory[i * LCD_Y_SIZE + j] = ulValue;
//        }
//    }
//}
//
//// Initializes the display driver.
//// This function initializes the LCD controller
////
//// TemplateDisplayFix
//void
//ssd1306_DriverInit(void)
//{
//    uint16_t vccstate = 0x00;
//    // Init sequence
//    ssd1306_command(SSD1306_DISPLAYOFF);                    // 0xAE
//    ssd1306_command(SSD1306_SETDISPLAYCLOCKDIV);            // 0xD5
//    ssd1306_command(0x80);                                  // the suggested ratio 0x80
//
//    ssd1306_command(SSD1306_SETMULTIPLEX);                  // 0xA8
//    ssd1306_command(0x3F);                                  // SSD1306_LCDHEIGHT - 1
//
//    ssd1306_command(SSD1306_SETDISPLAYOFFSET);              // 0xD3
//    ssd1306_command(0x00);                                   // no offset
//    ssd1306_command(SSD1306_SETSTARTLINE);                   // line #0
//    ssd1306_command(SSD1306_CHARGEPUMP);                    // 0x8D
//    if (vccstate == SSD1306_EXTERNALVCC)
//    { ssd1306_command(0x10); }
//    else
//    { ssd1306_command(0x14); }
//    ssd1306_command(SSD1306_MEMORYMODE);                    // 0x20
//    ssd1306_command(0x00);                                  // 0x0 act like ks0108
//    ssd1306_command(0xA1);                                  // SSD1306_SEGREMAP | 0x1
//    ssd1306_command(SSD1306_COMSCANDEC);                    // 0xC8
//
//#if defined SSD1306_128_32
//    ssd1306_command(SSD1306_SETCOMPINS);                    // 0xDA
//    ssd1306_command(0x02);
//    ssd1306_command(SSD1306_SETCONTRAST);                   // 0x81
//    ssd1306_command(0x8F);
//
//#elif defined SSD1306_128_64
//    ssd1306_command(SSD1306_SETCOMPINS);                    // 0xDA
//    ssd1306_command(0x12);
//    ssd1306_command(SSD1306_SETCONTRAST);                   // 0x81
//    if (vccstate == SSD1306_EXTERNALVCC)
//    { ssd1306_command(0x9F); }
//    else
//    { ssd1306_command(0xCF); }
//
//#elif defined SSD1306_96_16
//    ssd1306_command(SSD1306_SETCOMPINS);                    // 0xDA
//    ssd1306_command(0x2);   //ada x12
//    ssd1306_command(SSD1306_SETCONTRAST);                   // 0x81
//    if (vccstate == SSD1306_EXTERNALVCC)
//    { ssd1306_command(0x10); }
//    else
//    { ssd1306_command(0xAF); }
//
//#endif
//
//    ssd1306_command(SSD1306_SETPRECHARGE);                  // 0xd9
//    if (vccstate == SSD1306_EXTERNALVCC)
//    { ssd1306_command(0x22); }
//    else
//    { ssd1306_command(0xF1); }
//    ssd1306_command(SSD1306_SETVCOMDETECT);                 // 0xDB
//    ssd1306_command(0x40);
//    ssd1306_command(SSD1306_DISPLAYALLON_RESUME);           // 0xA4
//    ssd1306_command(SSD1306_NORMALDISPLAY);                 // 0xA6
//
//    ssd1306_command(SSD1306_DEACTIVATE_SCROLL);             // 0x2E
//
//    ssd1306_command(SSD1306_DISPLAYON);//--turn on oled panel   0x2F
//
//}
//
//// Send command to the display
//// Command structure is : control signal(0x00), The command itself(c)
//// The issue command to SPI to stop transmission
//void ssd1306_command(uint8_t c) {
//
//    uint8_t control = 0x00;
//
//    USCI_B_I2C_masterSendMultiByteStart(USCI_B0_BASE,control);
//
//    USCI_B_I2C_masterSendMultiByteNext(USCI_B0_BASE,c);
//
//    USCI_B_I2C_masterSendMultiByteStop(USCI_B0_BASE);
//
//    __delay_cycles(50);
//
//
//
//}
//
////! Draws a pixel on the screen.
////!
//
////! \param lX is the X coordinate of the pixel.
////! \param lY is the Y coordinate of the pixel.
////! \param ulValue is the color of the pixel.
////!
////! This function sets the given pixel to a particular color.  The coordinates
////! of the pixel checked
////!
////! \return None.
////
////*****************************************************************************
//void ssd1306_drawPixel(int16_t x, int16_t y, uint16_t color) {
//    if ((x < 0) || (x >= 128) || (y < 0) || (y >= 64))
//        return;
//
//    x = 128 - x - 1;
//    y = 64 - y - 1;
//
//    // x is which column
//    switch (color)
//    {
//    case WHITE:   buffer[x+ (y/8)*SSD1306_LCDWIDTH] |=  (1 << (y&7)); break;
//    case BLACK:   buffer[x+ (y/8)*SSD1306_LCDWIDTH] &= ~(1 << (y&7)); break;
//    case INVERSE: buffer[x+ (y/8)*SSD1306_LCDWIDTH] ^=  (1 << (y&7)); break;
//    }
//}
//
//
//void ssd1306_display(uint8_t array[]) {
//
//    ssd1306_command(SSD1306_COLUMNADDR);
//    ssd1306_command(0x00);   // Column start address (0 = reset)
//    ssd1306_command(0x7F); // Column end address (127 = reset) SSD1306_LCDWIDTH-1
//
//    ssd1306_command(SSD1306_PAGEADDR); //0x22
//    ssd1306_command(0x00); // Page start address (0 = reset)
//#if SSD1306_LCDHEIGHT == 64
//    ssd1306_command(0x07); // Page end address
//#endif
//#if SSD1306_LCDHEIGHT == 32
//    ssd1306_command(3); // Page end address
//#endif
//#if SSD1306_LCDHEIGHT == 16
//    ssd1306_command(1); // Page end address
//#endif
//
//    uint16_t i;
//    uint8_t x;
//
//#ifdef TWBR
//    uint8_t twbrbackup = TWBR;
//    TWBR = 12; // upgrade to 400KHz!
//#endif
//
//    for (i=0; i<(SSD1306_LCDWIDTH*SSD1306_LCDHEIGHT/8); i++) {
//        __delay_cycles(500);
//
//        USCI_B_I2C_masterSendMultiByteStart(USCI_B0_BASE,0x40);
//
//        //        WIRE_WRITE(0x40);
//        for (x=0; x<16; x++) {
//
////                        USCI_B_I2C_masterSendMultiByteNext(USCI_B0_BASE,0xAA);
//            USCI_B_I2C_masterSendMultiByteNext(USCI_B0_BASE,array[i]);
//            i++;
//        }
//        i--;
//        USCI_B_I2C_masterSendMultiByteStop(USCI_B0_BASE);
//    }
//}
//
//
//void ssd1306_clearDisplay() {
//    uint16_t i;
//
//    for (i=0; i<(SSD1306_LCDWIDTH*SSD1306_LCDHEIGHT/8); i++) {
//
//        buffer[i] = 0x00;
//    }
//}
//
//void ssd1306_startscrollright(uint8_t start, uint8_t stop){
//    ssd1306_command(SSD1306_RIGHT_HORIZONTAL_SCROLL);
//    ssd1306_command(0X00);
//    ssd1306_command(start);
//    ssd1306_command(0X00);
//    ssd1306_command(stop);
//    ssd1306_command(0X00);
//    ssd1306_command(0XFF);
//    ssd1306_command(SSD1306_ACTIVATE_SCROLL);
//  }
//
//
//void ssd1306_startscrollleft(uint8_t start, uint8_t stop){
//  ssd1306_command(SSD1306_LEFT_HORIZONTAL_SCROLL);
//  ssd1306_command(0X00);
//  ssd1306_command(start);
//  ssd1306_command(0X00);
//  ssd1306_command(stop);
//  ssd1306_command(0X00);
//  ssd1306_command(0XFF);
//  ssd1306_command(SSD1306_ACTIVATE_SCROLL);
//}
//
//void ssd1306_stopscroll(void){
//  ssd1306_command(SSD1306_DEACTIVATE_SCROLL);
//}
//
//void ssd1306_dim(uint8_t num) {
//    uint8_t contrast;
//    contrast = num;
//
//  // the range of contrast to too small to be really useful
//  // it is useful to dim the display
//  ssd1306_command(SSD1306_SETCONTRAST);
//  ssd1306_command(contrast);
//}
//
//
//void ssd1306_invertDisplay(uint8_t i) {
//  if (i==1) {
//    ssd1306_command(SSD1306_INVERTDISPLAY);
//  } else {
//    ssd1306_command(SSD1306_NORMALDISPLAY);
//  }
//}
//
////*****************************************************************************
////
////! Draws a horizontal sequence of pixels on the screen.
////!
////! \param pvDisplayData is a pointer to the driver-specific data for this
////! display driver.
////! \param lX is the X coordinate of the first pixel.
////! \param lY is the Y coordinate of the first pixel.
////! \param lX0 is sub-pixel offset within the pixel data, which is valid for 1
////! or 4 bit per pixel formats.
////! \param lCount is the number of pixels to draw.
////! \param lBPP is the number of bits per pixel; must be 1, 4, or 8.
////! \param pucData is a pointer to the pixel data.  For 1 and 4 bit per pixel
////! formats, the most significant bit(s) represent the left-most pixel.
////! \param pucPalette is a pointer to the palette used to draw the pixels.
////!
////! This function draws a horizontal sequence of pixels on the screen, using
////! the supplied palette.  For 1 bit per pixel format, the palette contains
////! pre-translated colors; for 4 and 8 bit per pixel formats, the palette
////! contains 24-bit RGB values that must be translated before being written to
////! the display.
////!
////! \return None.
////
////*****************************************************************************
//void ssd1306_DriverPixelDrawMultiple(
//                                 int16_t lX,
//                                 int16_t lY,
//                                 int16_t lX0,
//                                 int16_t lCount,
//                                 int16_t lBPP,
//                                 const uint8_t *pucData,
//                                 const uint32_t *pucPalette)
//{
//    uint16_t ulByte;
//
//    //
//    // Determine how to interpret the pixel data based on the number of bits
//    // per pixel.
//    //
//    switch(lBPP)
//    {
//    // The pixel data is in 1 bit per pixel format
//    case 1:
//    {
//        // Loop while there are more pixels to draw
//        while(lCount > 0)
//        {
//            // Get the next byte of image data
//            ulByte = *pucData++;
//
//            // Loop through the pixels in this byte of image data
//            for(; (lX0 < 8) && lCount; lX0++, lCount--)
//            {
//                // Draw this pixel in the appropriate color
//                ssd1306_drawPixel( lX++, lY,
//                                         ((uint16_t *)buffer)[(ulByte >>
//                                                 (7 -
//                                                         lX0)) & 1]);
//            }
//
//            // Start at the beginning of the next byte of image data
//            lX0 = 0;
//        }
//        // The image data has been drawn
//
//        break;
//    }
//
//    // The pixel data is in 2 bit per pixel format
//    case 2:
//    {
//        // Loop while there are more pixels to draw
//        while(lCount > 0)
//        {
//            // Get the next byte of image data
//            ulByte = *pucData++;
//
//            // Loop through the pixels in this byte of image data
//            for(; (lX0 < 4) && lCount; lX0++, lCount--)
//            {
//                // Draw this pixel in the appropriate color
//                ssd1306_drawPixel( lX++, lY,
//                                         ((uint16_t *)pucPalette)[(ulByte >>
//                                                 (6 -
//                                                         (lX0 <<
//                                                                 1))) & 3]);
//            }
//
//            // Start at the beginning of the next byte of image data
//            lX0 = 0;
//        }
//        // The image data has been drawn
//
//        break;
//    }
//    // The pixel data is in 4 bit per pixel format
//    case 4:
//    {
//        // Loop while there are more pixels to draw.  "Duff's device" is
//        // used to jump into the middle of the loop if the first nibble of
//        // the pixel data should not be used.  Duff's device makes use of
//        // the fact that a case statement is legal anywhere within a
//        // sub-block of a switch statement.  See
//        // http://en.wikipedia.org/wiki/Duff's_device for detailed
//        // information about Duff's device.
//        switch(lX0 & 1)
//        {
//        case 0:
//
//            while(lCount)
//            {
//                // Get the upper nibble of the next byte of pixel data
//                // and extract the corresponding entry from the palette
//                ulByte = (*pucData >> 4);
//                ulByte = (*(uint16_t *)(pucPalette + ulByte));
//                // Write to LCD screen
//                ssd1306_drawPixel( lX++, lY, ulByte);
//
//                // Decrement the count of pixels to draw
//                lCount--;
//
//                // See if there is another pixel to draw
//                if(lCount)
//                {
//        case 1:
//            // Get the lower nibble of the next byte of pixel
//            // data and extract the corresponding entry from
//            // the palette
//            ulByte = (*pucData++ & 15);
//            ulByte = (*(uint16_t *)(pucPalette + ulByte));
//            // Write to LCD screen
//            ssd1306_drawPixel( lX++, lY, ulByte);
//
//            // Decrement the count of pixels to draw
//            lCount--;
//                }
//            }
//        }
//        // The image data has been drawn.
//
//        break;
//    }
//
//    // The pixel data is in 8 bit per pixel format
//    case 8:
//    {
//        // Loop while there are more pixels to draw
//        while(lCount--)
//        {
//            // Get the next byte of pixel data and extract the
//            // corresponding entry from the palette
//            ulByte = *pucData++;
//            ulByte = (*(uint16_t *)(pucPalette + ulByte));
//            // Write to LCD screen
//            ssd1306_drawPixel(lX++, lY, ulByte);
//        }
//        // The image data has been drawn
//        break;
//    }
//    }
//}
////*****************************************************************************
////
//// All the following functions (below) for the LCD driver are required by grlib
////
////*****************************************************************************
//
////*****************************************************************************
////
////! Draws a pixel on the screen.
////!
////! \param pvDisplayData is a pointer to the driver-specific data for this
////! display driver.
////! \param lX is the X coordinate of the pixel.
////! \param lY is the Y coordinate of the pixel.
////! \param ulValue is the color of the pixel.
////!
////! This function sets the given pixel to a particular color.  The coordinates
////! of the pixel are assumed to be within the extents of the display.
////!
////! \return None.
////
////*****************************************************************************
////// TemplateDisplayFix
////static void
////Template_DriverPixelDraw(void *pvDisplayData,
////                         int16_t lX,
////                         int16_t lY,
////                         uint16_t ulValue)
////{
////    // Check if the pixel place with LCD boundaries
////    if ((lX < 0) | (lX >= SSD1306_LCDWIDTH)  | ( lY < 0 ) | (lY >= SSD1306_LCDHEIGHT))
////            return;
////
////
////    /* This function already has checked that the pixel is within the extents of
////       the LCD screen and the color ulValue has already been translated to the LCD.
////       This function typically looks like:*/
////
////    // Interpret pixel data (if needed)
////    // Update buffer (if applicable)
////    // Template_Memory[lY * LCD_Y_SIZE + (lX * BPP / 8)] = , |= , &= ...
////    // Template memory must be modified at the bit level for 1/2/4BPP displays
////
////   // buffer[lX+ (lY/8)*SSD1306_LCDWIDTH] |=  (1 << (lY&7));
////
////    //SetAddress(MAPPED_X(lX, lY), MAPPED_Y(lX, lY));
////    //WriteData(ulValue);
////}
//
//
////Template_DriverPixelDraw(void *pvDisplayData,
////                         int16_t lX,
////                         int16_t lY,
////                         uint16_t ulValue)
////{
////    // Check if the pixel place with LCD boundaries
////    if ((lX < 0) | (lX >= SSD1306_LCDWIDTH)  | ( lY < 0 ) | (lY >= SSD1306_LCDHEIGHT))
////            return;
////
////
////    /* This function already has checked that the pixel is within the extents of
////       the LCD screen and the color ulValue has already been translated to the LCD.
////       This function typically looks like:*/
////
////    // Interpret pixel data (if needed)
////    // Update buffer (if applicable)
////    // Template_Memory[lY * LCD_Y_SIZE + (lX * BPP / 8)] = , |= , &= ...
////    // Template memory must be modified at the bit level for 1/2/4BPP displays
////
////    buffer[lX+ (lY/8)*SSD1306_LCDWIDTH] |=  (1 << (lY&7));
////
////    SetAddress(MAPPED_X(lX, lY), MAPPED_Y(lX, lY));
////    WriteData(ulValue);
////}
//
////*****************************************************************************
////
////! Draws a horizontal sequence of pixels on the screen.
////!
////! \param pvDisplayData is a pointer to the driver-specific data for this
////! display driver.
////! \param lX is the X coordinate of the first pixel.
////! \param lY is the Y coordinate of the first pixel.
////! \param lX0 is sub-pixel offset within the pixel data, which is valid for 1
////! or 4 bit per pixel formats.
////! \param lCount is the number of pixels to draw.
////! \param lBPP is the number of bits per pixel; must be 1, 4, or 8.
////! \param pucData is a pointer to the pixel data.  For 1 and 4 bit per pixel
////! formats, the most significant bit(s) represent the left-most pixel.
////! \param pucPalette is a pointer to the palette used to draw the pixels.
////!
////! This function draws a horizontal sequence of pixels on the screen, using
////! the supplied palette.  For 1 bit per pixel format, the palette contains
////! pre-translated colors; for 4 and 8 bit per pixel formats, the palette
////! contains 24-bit RGB values that must be translated before being written to
////! the display.
////!
////! \return None.
////
////*****************************************************************************
//static void
//Template_DriverPixelDrawMultiple(
//                                 int16_t lX,
//                                 int16_t lY,
//                                 int16_t lX0,
//                                 int16_t lCount,
//                                 int16_t lBPP,
//                                 const uint8_t *pucData,
//                                 const uint32_t *pucPalette)
//{
//    uint16_t ulByte;
//
//    //
//    // Determine how to interpret the pixel data based on the number of bits
//    // per pixel.
//    //
//    switch(lBPP)
//    {
//    // The pixel data is in 1 bit per pixel format
//    case 1:
//    {
//        // Loop while there are more pixels to draw
//        while(lCount > 0)
//        {
//            // Get the next byte of image data
//            ulByte = *pucData++;
//
//            // Loop through the pixels in this byte of image data
//            for(; (lX0 < 8) && lCount; lX0++, lCount--)
//            {
//                // Draw this pixel in the appropriate color
//                ssd1306_drawPixel( lX++, lY,
//                                         ((uint16_t *)pucPalette)[(ulByte >>
//                                                 (7 -
//                                                         lX0)) & 1]);
//            }
//
//            // Start at the beginning of the next byte of image data
//            lX0 = 0;
//        }
//        // The image data has been drawn
//
//        break;
//    }
//
//    // The pixel data is in 2 bit per pixel format
//    case 2:
//    {
//        // Loop while there are more pixels to draw
//        while(lCount > 0)
//        {
//            // Get the next byte of image data
//            ulByte = *pucData++;
//
//            // Loop through the pixels in this byte of image data
//            for(; (lX0 < 4) && lCount; lX0++, lCount--)
//            {
//                // Draw this pixel in the appropriate color
//                ssd1306_drawPixel( lX++, lY,
//                                         ((uint16_t *)pucPalette)[(ulByte >>
//                                                 (6 -
//                                                         (lX0 <<
//                                                                 1))) & 3]);
//            }
//
//            // Start at the beginning of the next byte of image data
//            lX0 = 0;
//        }
//        // The image data has been drawn
//
//        break;
//    }
//    // The pixel data is in 4 bit per pixel format
//    case 4:
//    {
//        // Loop while there are more pixels to draw.  "Duff's device" is
//        // used to jump into the middle of the loop if the first nibble of
//        // the pixel data should not be used.  Duff's device makes use of
//        // the fact that a case statement is legal anywhere within a
//        // sub-block of a switch statement.  See
//        // http://en.wikipedia.org/wiki/Duff's_device for detailed
//        // information about Duff's device.
//        switch(lX0 & 1)
//        {
//        case 0:
//
//            while(lCount)
//            {
//                // Get the upper nibble of the next byte of pixel data
//                // and extract the corresponding entry from the palette
//                ulByte = (*pucData >> 4);
//                ulByte = (*(uint16_t *)(pucPalette + ulByte));
//                // Write to LCD screen
//                ssd1306_drawPixel( lX++, lY, ulByte);
//
//                // Decrement the count of pixels to draw
//                lCount--;
//
//                // See if there is another pixel to draw
//                if(lCount)
//                {
//        case 1:
//            // Get the lower nibble of the next byte of pixel
//            // data and extract the corresponding entry from
//            // the palette
//            ulByte = (*pucData++ & 15);
//            ulByte = (*(uint16_t *)(pucPalette + ulByte));
//            // Write to LCD screen
//            ssd1306_drawPixel( lX++, lY, ulByte);
//
//            // Decrement the count of pixels to draw
//            lCount--;
//                }
//            }
//        }
//        // The image data has been drawn.
//
//        break;
//    }
//
//    // The pixel data is in 8 bit per pixel format
//    case 8:
//    {
//        // Loop while there are more pixels to draw
//        while(lCount--)
//        {
//            // Get the next byte of pixel data and extract the
//            // corresponding entry from the palette
//            ulByte = *pucData++;
//            ulByte = (*(uint16_t *)(pucPalette + ulByte));
//            // Write to LCD screen
//            ssd1306_drawPixel(lX++, lY, ulByte);
//        }
//        // The image data has been drawn
//        break;
//    }
//    }
//}
//
//
//
////*****************************************************************************
////
////! Draws a horizontal line.
////!
////! \param pvDisplayData is a pointer to the driver-specific data for this
////! display driver.
////! \param lX1 is the X coordinate of the start of the line.
////! \param lX2 is the X coordinate of the end of the line.
////! \param lY is the Y coordinate of the line.
////! \param ulValue is the color of the line.
////!
////! This function draws a horizontal line on the display.  The coordinates of
////! the line are assumed to be within the extents of the display.
////!
////! \return None.
////
////*****************************************************************************
//static void
//Template_DriverLineDrawH(void *pvDisplayData,
//                         int16_t lX1,
//                         int16_t lX2,
//                         int16_t lY,
//                         uint16_t ulValue)
//{
//    /* Ideally this function shouldn't call pixel draw. It should have it's own
//       definition using the built in auto-incrementing of the LCD controller and its
//       own calls to SetAddress() and WriteData(). Better yet, SetAddress() and WriteData()
//       can be made into macros as well to eliminate function call overhead. */
//
//    do
//    {
//        ssd1306_drawPixel( lX1, lY, ulValue);
//    }
//    while(lX1++ < lX2);
//}
//
////*****************************************************************************
////
////! Draws a vertical line.
////!
////! \param pvDisplayData is a pointer to the driver-specific data for this
////! display driver.
////! \param lX is the X coordinate of the line.
////! \param lY1 is the Y coordinate of the start of the line.
////! \param lY2 is the Y coordinate of the end of the line.
////! \param ulValue is the color of the line.
////!
////! This function draws a vertical line on the display.  The coordinates of the
////! line are assumed to be within the extents of the display.
////!
////! \return None.
////
////*****************************************************************************
//static void
//Template_DriverLineDrawV(void *pvDisplayData,
//                         int16_t lX,
//                         int16_t lY1,
//                         int16_t lY2,
//                         uint16_t ulValue)
//{
//    do
//    {
//        ssd1306_drawPixel( lX, lY1, ulValue);
//    }
//    while(lY1++ < lY2);
//}
//
////*****************************************************************************
////
////! Fills a rectangle.
////!
////! \param pvDisplayData is a pointer to the driver-specific data for this
////! display driver.
////! \param pRect is a pointer to the structure describing the rectangle.
////! \param ulValue is the color of the rectangle.
////!
////! This function fills a rectangle on the display.  The coordinates of the
////! rectangle are assumed to be within the extents of the display, and the
////! rectangle specification is fully inclusive (in other words, both sXMin and
////! sXMax are drawn, along with sYMin and sYMax).
////!
////! \return None.
////
////*****************************************************************************
//static void
//Template_DriverRectFill(void *pvDisplayData,
//                        const Graphics_Rectangle *pRect,
//                        uint16_t ulValue)
//{
//    int16_t x0 = pRect->sXMin;
//    int16_t x1 = pRect->sXMax;
//    int16_t y0 = pRect->sYMin;
//    int16_t y1 = pRect->sYMax;
//
//    while(y0++ <= y1)
//    {
//        Template_DriverLineDrawH(pvDisplayData, x0, x1, y0, ulValue);
//    }
//}
//
////*****************************************************************************
////
////! Translates a 24-bit RGB color to a display driver-specific color.
////!
////! \param pvDisplayData is a pointer to the driver-specific data for this
////! display driver.
////! \param ulValue is the 24-bit RGB color.  The least-significant byte is the
////! blue channel, the next byte is the green channel, and the third byte is the
////! red channel.
////!
////! This function translates a 24-bit RGB color into a value that can be
////! written into the display's frame buffer in order to reproduce that color,
////! or the closest possible approximation of that color.
////!
////! \return Returns the display-driver specific color.
////
////*****************************************************************************
//static uint32_t
//Template_DriverColorTranslate(void *pvDisplayData,
//                              uint32_t ulValue)
//{
//    /* The DPYCOLORTRANSLATE macro should be defined in TemplateDriver.h */
//
//    //
//    // Translate from a 24-bit RGB color to a color accepted by the LCD.
//    //
//    return(DPYCOLORTRANSLATE(ulValue));
//}
//
////*****************************************************************************
////
////! Flushes any cached drawing operations.
////!
////! \param pvDisplayData is a pointer to the driver-specific data for this
////! display driver.
////!
////! This functions flushes any cached drawing operations to the display.  This
////! is useful when a local frame buffer is used for drawing operations, and the
////! flush would copy the local frame buffer to the display.
////!
////! \return None.
////
////*****************************************************************************
//static void
//Template_DriverFlush(void *pvDisplayData)
//{
//    // Flush Buffer here. This function is not needed if a buffer is not used,
//    // or if the buffer is always updated with the screen writes.
//    int16_t i = 0,j = 0;
//    for(i = 0; i < LCD_Y_SIZE; i++)
//    {
//        for(j = 0; j < (LCD_X_SIZE * BPP + 7) / 8; j++)
//        {
//            ssd1306_drawPixel( j, i,
//                                     Template_Memory[i * LCD_Y_SIZE + j]);
//        }
//    }
//}
//
////*****************************************************************************
////
////! Send command to clear screen.
////!
////! \param pvDisplayData is a pointer to the driver-specific data for this
////! display driver.
////!
////! This function does a clear screen and the Display Buffer contents
////! are initialized to the current background color.
////!
////! \return None.
////
////*****************************************************************************
//static void
//Template_DriverClearScreen(void *pvDisplayData,
//                           uint16_t ulValue)
//{
//    // This fills the entire display to clear it
//    // Some LCD drivers support a simple command to clear the display
//    int16_t y0 = 0;
//    while(y0++ <= (LCD_Y_SIZE - 1))
//    {
//        Template_DriverLineDrawH(pvDisplayData, 0, LCD_X_SIZE - 1, y0, ulValue);
//    }
//}
//
////*****************************************************************************
////
////! The display structure that describes the driver for the blank template.
////
////*****************************************************************************
////const Graphics_Display g_sTemplate_Driver =
////{
//// sizeof(tDisplay),
//// Template_Memory,
////#if defined(PORTRAIT) || defined(PORTRAIT_FLIP)
//// LCD_Y_SIZE,
//// LCD_X_SIZE,
////#else
//// LCD_X_SIZE,
//// LCD_Y_SIZE,
////#endif
//// ssd1306_DriverPixelDraw,
//// Template_DriverPixelDrawMultiple,
//// Template_DriverLineDrawH,
//// Template_DriverLineDrawV,
//// Template_DriverRectFill,
//// Template_DriverColorTranslate,
//// Template_DriverFlush,
//// Template_DriverClearScreen
////};
//
////*****************************************************************************
////
//// Close the Doxygen group.
////! @}
////
////*****************************************************************************
