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
//*****************************************************************************
//
// Template_Driver.h - Display driver for any LCD Controller. This file serves as
//						a template for creating new LCD driver files
//
//*****************************************************************************

#ifndef __Template_Driver_H__
#define __Template_Driver_H__

//*****************************************************************************
//
// Include Files
//
//*****************************************************************************
#include "grlib.h"
#include "Images/images.h"
/*Put any necessary include files here*/

//*****************************************************************************
//
// User Configuration for the LCD Driver
//
//*****************************************************************************

// The SSD1306 Dirver used in multiple displays
// Select the appropriate display size.

uint8_t buffer[1024];

//#ifndef OLED_SSD1306_H_
//#define OLED_SSD1306_H_

// manual logic trigger for analyzer
//#define LOGIC_OUT   P2OUT
//#define LOGIC_DIR   P2DIR
//#define LOGIC_BIT   BIT5
//#define TRIGGER (LOGIC_OUT |= LOGIC_BIT)

//// OLED PORTS CONFIG
//#define OLED_SPI_DIR P1DIR
//#define OLED_SPI_SEL P1SEL
//#define OLED_SPI_SEL2 P1SEL2

//#define OLED_IO_DIR P2DIR
//#define OLED_IO_OUT P2OUT
//
//#define OLED_CS_DIR P2DIR
//#define OLED_CS_OUT P2OUT

// OLED GPIO CONFIG
//#define OLED_RES BIT1   // P2.1
//#define OLED_DC BIT2    // P2.2
//#define OLED_CS BIT0    // P2.0
//#define OLED_SIMO BIT7  // P1.7
////#define OLED_SOMI BIT6    // P1.6; unused for OLED
//#define OLED_SCLK BIT5  // P1.5

// OLED GPIO MACROS
//#define OLED_SELECT (OLED_CS_OUT &= ~OLED_CS)
//#define OLED_DESELECT    (OLED_CS_OUT |= OLED_CS)
//#define OLED_COMMAND (OLED_IO_OUT &= ~OLED_DC)
//#define OLED_DATA    (OLED_IO_OUT |= OLED_DC)
//#define OLED_RES_LOW  (OLED_IO_OUT &= ~OLED_RES)
//#define OLED_RES_HIGH (OLED_IO_OUT |= OLED_RES)

// SSD1306 PARAMETERS
#define SSD1306_LCDWIDTH 128
#define SSD1306_LCDHEIGHT 64
#define SSD1306_MAXROWS 7
#define SSD1306_MAXCONTRAST 0xFF

    // command table
#define SSD1306_SETCONTRAST 0x81
#define SSD1306_DISPLAYALLON_RESUME 0xA4
#define SSD1306_DISPLAYALLON 0xA5
#define SSD1306_NORMALDISPLAY 0xA6
#define SSD1306_INVERTDISPLAY 0xA7
#define SSD1306_DISPLAYOFF 0xAE
#define SSD1306_DISPLAYON 0xAF


    // scrolling commands
#define SSD1306_SCROLL_RIGHT 0x26
#define SSD1306_SCROLL_LEFT 0X27
#define SSD1306_SCROLL_VERT_RIGHT 0x29
#define SSD1306_SCROLL_VERT_LEFT 0x2A
#define SSD1306_SET_VERTICAL 0xA3

    // address setting
#define SSD1306_SETLOWCOLUMN 0x00
#define SSD1306_SETHIGHCOLUMN 0x10
#define SSD1306_MEMORYMODE 0x20
#define SSD1306_COLUMNADDRESS 0x21
#define SSD1306_COLUMNADDRESS_MSB 0x00
#define SSD1306_COLUMNADDRESS_LSB 0x7F
#define SSD1306_PAGEADDRESS 0x22
#define SSD1306_PAGE_START_ADDRESS 0xB0

    // hardware configuration
#define SSD1306_SETSTARTLINE 0x40
#define SSD1306_SEGREMAP 0xA0
//#define SSD1306_SEGREMAP 0xA1
#define SSD1306_SETMULTIPLEX 0xA8
#define SSD1306_COMSCANINC 0xC0
#define SSD1306_COMSCANDEC 0xC8
#define SSD1306_SETDISPLAYOFFSET 0xD3
#define SSD1306_SETCOMPINS 0xDA

    // timing and driving
#define SSD1306_SETDISPLAYCLOCKDIV 0xD5
#define SSD1306_SETPRECHARGE 0xD9
#define SSD1306_SETVCOMDETECT 0xDB
#define SSD1306_NOP 0xE3

    // power supply configuration
#define SSD1306_CHARGEPUMP 0x8D
#define SSD1306_EXTERNALVCC 0x10
#define SSD1306_SWITCHCAPVCC 0x20

#define SSD1306_DEACTIVATE_SCROLL 0x2E

// PROTOTYPES
void SSD1306PinSetup( void );
void SSD1306Init( void );

void SSD1306SendCommand( char *data, int i );

void SSD1306SendData( char *data, int i );
void setAddress( char page, char column );
void clearScreen(void);
void charDraw(char row, char column, int data);
void stringDraw( char row, char column, char *word);
void pixelDraw(char x, char y);
void horizontalLine(char xStart, char xStop, char y);
void verticalLine(char x, char yStart, char yStop);
void imageDraw(const char IMAGE[], char row, char column);
//void circleDraw(char x, char y, char radius);
void circleDraw(register int x, register int y, int r);

void Set_Contrast_Control(unsigned char d);
void Set_Inverse_Display(unsigned char d);
void Set_Display_On_Off(unsigned char d);

void Fill_RAM( char data);
void Fill_RAM_PAGE(unsigned char page, char data);

//#endif /*SSD1306_OLED_H_*/




#define SSD1306_128_64
//   #define SSD1306_128_32
//   #define SSD1306_96_16

#if defined SSD1306_128_64 && defined SSD1306_128_32
#error "Only one SSD1306 display can be specified at once in SSD1306.h"
#endif
#if !defined SSD1306_128_64 && !defined SSD1306_128_32 && !defined SSD1306_96_16
#error "At least one SSD1306 display must be specified in SSD1306.h"
#endif


#if defined SSD1306_128_64
#define SSD1306_LCDWIDTH                  128
#define SSD1306_LCDHEIGHT                 64
#endif
#if defined SSD1306_128_32
#define SSD1306_LCDWIDTH                  128
#define SSD1306_LCDHEIGHT                 32
#endif
#if defined SSD1306_96_16
#define SSD1306_LCDWIDTH                  96
#define SSD1306_LCDHEIGHT                 16
#endif
//
//
//#define SSD1306_SETCONTRAST 0x81
//#define SSD1306_DISPLAYALLON_RESUME 0xA4
//#define SSD1306_DISPLAYALLON 0xA5
//#define SSD1306_NORMALDISPLAY 0xA6
//#define SSD1306_INVERTDISPLAY 0xA7
//#define SSD1306_DISPLAYOFF 0xAE
//#define SSD1306_DISPLAYON 0x2F
//
//#define SSD1306_SETDISPLAYOFFSET 0xD3
//#define SSD1306_SETCOMPINS 0xDA
//
//#define SSD1306_SETVCOMDETECT 0xDB
//
//#define SSD1306_SETDISPLAYCLOCKDIV 0xD5
//#define SSD1306_SETPRECHARGE 0xD9
//
//#define SSD1306_SETMULTIPLEX 0xA8
//
//#define SSD1306_SETLOWCOLUMN 0x00
//#define SSD1306_SETHIGHCOLUMN 0x10
//
//#define SSD1306_SETSTARTLINE 0x40
//
//#define SSD1306_MEMORYMODE 0x20
//#define SSD1306_COLUMNADDR 0x21
//#define SSD1306_PAGEADDR   0x22
//
//#define SSD1306_COMSCANINC 0xC0
//#define SSD1306_COMSCANDEC 0xC8
//
////#define SSD1306_SEGREMAP 0xA0
//
//#define SSD1306_CHARGEPUMP 0x8D

//#define SSD1306_EXTERNALVCC 0x1
//#define SSD1306_SWITCHCAPVCC 0x2

// Scrolling #defines
//#define SSD1306_ACTIVATE_SCROLL 0x2F
//#define SSD1306_DEACTIVATE_SCROLL 0x2E
//#define SSD1306_SET_VERTICAL_SCROLL_AREA 0xA3
//#define SSD1306_RIGHT_HORIZONTAL_SCROLL 0x26
//#define SSD1306_LEFT_HORIZONTAL_SCROLL 0x27
//#define SSD1306_VERTICAL_AND_RIGHT_HORIZONTAL_SCROLL 0x29
//#define SSD1306_VERTICAL_AND_LEFT_HORIZONTAL_SCROLL 0x2A
//
//
//// Number of pixels on LCD X-axis
//// TemplateDisplayFix
//#define LCD_X_SIZE      1
//
//// Number of pixels on LCD Y-axis
//// TemplateDisplayFix
//#define LCD_Y_SIZE      1
//
//// Number of bits required to draw one pixel on the LCD screen
//// TemplateDisplayFix
//#define BPP     1
//
//// Define LCD Screen Orientation Here TODO Not working try to implement
//#define LANDSCAPE
////#define LANDSCAPE_FLIP
////#define PORTRAIT
////#define PORTRAIT_FLIP

//*****************************************************************************
//
// Defines for the pins that are used to communicate with the LCD Driver
//
//*****************************************************************************

/*Define Pin Names here i.e. #define LCD_RESET_OUT	P6OUT*/

//*****************************************************************************
//
// Defines for LCD driver configuration
//
//*****************************************************************************

/* Defines for pixels, colors, masks, etc. Anything Template_Driver.c needs*/

//*****************************************************************************
//
// This driver operates in four different screen orientations.  They are:
//
// * Portrait - The screen is taller than it is wide. This is selected by defining
//              PORTRAIT.
//
// * Landscape - The screen is wider than it is tall. This is selected by defining
//               LANDSCAPE.
//
// * Portrait flip - The screen is taller than it is wide. This is
//                   selected by defining PORTRAIT_FLIP.
//
// * Landscape flip - The screen is wider than it is tall. This is
//                    selected by defining LANDSCAPE_FLIP.
//
// These can also be imagined in terms of screen rotation; if landscape mode is
// 0 degrees of screen rotation, portrait flip is 90 degrees of clockwise
// rotation, landscape flip is 180 degrees of rotation, and portrait is
// 270 degress of clockwise rotation.
//
// If no screen orientation is selected, "landscape" mode will be used.
//
//*****************************************************************************
#if !defined(PORTRAIT) && !defined(PORTRAIT_FLIP) && \
        !defined(LANDSCAPE) && !defined(LANDSCAPE_FLIP)
#define LANDSCAPE
#endif

//*****************************************************************************
//
// Various definitions controlling coordinate space mapping and drawing
// direction in the four supported orientations.
//
//*****************************************************************************
#ifdef PORTRAIT
#define MAPPED_X(x, y) (LCD_X_SIZE - (y) - 1)
#define MAPPED_Y(x, y) (x)
#endif
#ifdef LANDSCAPE
#define MAPPED_X(x, y) (x)
#define MAPPED_Y(x, y) (y)
#endif
#ifdef PORTRAIT_FLIP
#define MAPPED_X(x, y)  (y)
#define MAPPED_Y(x, y)  (LCD_Y_SIZE - (x) - 1)
#endif
#ifdef LANDSCAPE_FLIP
#define MAPPED_X(x, y)  (LCD_X_SIZE - (x) - 1)
#define MAPPED_Y(x, y)  (LCD_Y_SIZE - (y) - 1)
#endif

//*****************************************************************************
//
// Various LCD Controller command name labels and associated control bits
//
//*****************************************************************************

//*****************************************************************************
//
// Macros for the Display Driver
//
//*****************************************************************************

/* All macros can go here. This is typically the color translation function (example below)
   and could also include Set_Address(), Write_Data(), etc. */

// Translates a 24-bit RGB color to a display driver-specific color.
//
// \param c is the 24-bit RGB color.  The least-significant byte is the blue
// channel, the next byte is the green channel, and the third byte is the red
// channel.
//
// This macro translates a 24-bit RGB color into a value that can be written
// into the display's frame buffer in order to reproduce that color, or the
// closest possible approximation of that color. This particular example
// requires the 8-8-8 24 bit RGB color to convert into 5-6-5 16 bit RGB Color
// Your conversion should be made to fit your LCD settings.
//
// \return Returns the display-driver specific color
//
// TemplateDisplayFix

#define DPYCOLORTRANSLATE(c)    ((((c) & 0x00f80000) >> 8) |               \
        (((c) & 0x0000fc00) >> 5) |               \
        (((c) & 0x000000f8) >> 3))

//*****************************************************************************
//
// Prototypes for the globals exported by this driver.
//
//*****************************************************************************
extern void ssd1306_DriverInit(void);
extern const Graphics_Display g_sTemplate_Driver;
extern uint8_t Template_Memory[];


void ssd1306_command(uint8_t);

void ssd1306_drawPixel(int16_t, int16_t, uint16_t);

void ssd1306_display(uint8_t[]);

void ssd1306_clearDisplay();

void ssd1306_startscrollright(uint8_t,uint8_t);

void ssd1306_startscrollleft(uint8_t, uint8_t );

void ssd1306_stopscroll();

void ssd1306_dim(uint8_t);

void ssd1306_invertDisplay(uint8_t);

//void ssd1306_DriverPixelDrawMultiple(int16_t,int16_t, int16_t, int16_t, int16_t ,  uint8_t*, uint32_t*);

//void ssd1306_DriverPixelDraw(int16_t ,int16_t ,uint16_t);

//void Template_DriverPixelDraw(int16_t,int16_t ,uint16_t);

#endif // __Template_Driver_H__
