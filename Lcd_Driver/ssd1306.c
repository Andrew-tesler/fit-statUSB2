/**********************************************************
 * NAME: ssd1306.c
 *
 * PURPOSE: driver for SSD1306 OLED monitor
 *
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
 * 10/12/2018   Andrew T.   0.1.0     File creation
 *
 * *
 *******************************************************************/
#include "ssd1306.h"
#include "driverlib.h"
#include <msp430.h>





static uint8_t ssd1306_command(uint8_t command){


    uint8_t control = 0x00;

    USCI_B_I2C_masterSendMultiByteStart(USCI_B0_BASE,control);

    USCI_B_I2C_masterSendMultiByteNext(USCI_B0_BASE,command);

    USCI_B_I2C_masterSendMultiByteStop(USCI_B0_BASE);

    __delay_cycles(50);

    return 1;

}
void Tx_data_send(unsigned char *data_send, uint8_t size){
    __disable_interrupt();

       //    uint8_t control = 0x00;
       USCI_B_I2C_masterSendStart(USCI_B0_BASE);

       while(size)
       {

           USCI_B_I2C_masterSendMultiByteNext(USCI_B0_BASE,*data_send);
           __delay_cycles(50);
           data_send++;             // increment pointer
           //
           size--;                // decrement byte counter
       }
       USCI_B_I2C_masterSendMultiByteStop(USCI_B0_BASE);

       __enable_interrupt();
}


void Tx_data_send_bytes_no_stop(unsigned char *data_send){
    __disable_interrupt();

       //    uint8_t control = 0x00;
       USCI_B_I2C_masterSendStart(USCI_B0_BASE);

       while(size)
       {

           USCI_B_I2C_masterSendMultiByteNext(USCI_B0_BASE,*data_send);
           __delay_cycles(50);
           data_send++;             // increment pointer
           //
           size--;                // decrement byte counter
       }
//       USCI_B_I2C_masterSendMultiByteStop(USCI_B0_BASE);

       __enable_interrupt();
}


void ssd1306_display_init(){
//    P3SEL |= 0x03;                            // Assign I2C pins to USCI_B0
//    UCB0CTL1 |= UCSWRST;                      // Enable SW reset
//    UCB0CTL0 = UCMST + UCMODE_3 + UCSYNC;     // I2C Master, synchronous mode
//    UCB0CTL1 = UCSSEL_2 + UCSWRST;            // Use SMCLK, keep SW reset
//    UCB0BR0 = 12;                             // fSCL = SMCLK/12 = ~100kHz
//    UCB0BR1 = 0;
//    UCB0I2CSA = 0x3C;                         // Slave Address for OLED is 0x3C
//    UCB0CTL1 &= ~UCSWRST;                     // Clear SW reset, resume operation
//    UCB0IE |= UCTXIE;                         // Enable TX interrupt


    ssd1306_command(SSD1306_DISPLAYOFF);                    // 0xAE
    ssd1306_command(SSD1306_SETDISPLAYCLOCKDIV);            // 0xD5
    ssd1306_command(0x80);                                  // the suggested ratio 0x80
    ssd1306_command(SSD1306_SETMULTIPLEX);                  // 0xA8
    ssd1306_command(SSD1306_HEIGHT - 1);
    ssd1306_command(SSD1306_SETDISPLAYOFFSET);              // 0xD3
    ssd1306_command(0x0);                                   // no offset
    ssd1306_command(SSD1306_SETSTARTLINE | 0x0);            // line #0 0x40

    ssd1306_command(SSD1306_CHARGEPUMP);                    // 0x8D
    ssd1306_command(0x14);
//    ssd1306_command(0x10);
    ssd1306_command(SSD1306_MEMORYMODE);                    // 0x20
    ssd1306_command(0x00);                                  // 0x0 act like ks0108
    ssd1306_command(SSD1306_SEGREMAP | 0x1);                // 0x A1

    // Set scan direction
    ssd1306_command(SSD1306_COMSCANDEC);                    // 0xC8

    ssd1306_command(SSD1306_SETCOMPINS);                    // 0xDA
//    ssd1306_command(0x02);
    ssd1306_command(0x12);

    ssd1306_command(SSD1306_SETCONTRAST);                   // 0x81
//    ssd1306_command(0x8F);
    ssd1306_command(0xCF);

    ssd1306_command(SSD1306_SETPRECHARGE);                  // 0xd9
    ssd1306_command(0xF1);

    ssd1306_command(SSD1306_SETVCOMDETECT);                 // 0xDB
    ssd1306_command(0x40);

    ssd1306_command(SSD1306_DISPLAYALLON_RESUME);           // 0xA4

    ssd1306_command(SSD1306_NORMALDISPLAY);                 // 0xA6
//    ssd1306_command(0x2E);

    ssd1306_command(SSD1306_DISPLAYON);                     // 0xAF

}

static void ssd1306_clear_page(uint8_t page_number){
    // Set column start and end address
    ssd1306_command(SSD1306_COLUMNADDR);
    ssd1306_command(0);
    ssd1306_command(SSD1306_WIDTH - 1);

    // Set page start and end address
    ssd1306_command(SSD1306_PAGEADDR);
    ssd1306_command(page_number);
    ssd1306_command(page_number);


    //size = 1;

    i2c_tx_packet[0] = SSD1306_TRANSMISSION_DATA;
    //Tx_data_send(i2c_tx_buffer, size);

    uint16_t j = 0;
//  i2c_master_write_packet_wait_no_stop(i2c_master_instance, &i2c_tx_packet);
    //i2c_tx_buffer[0] = 0x00;
    for(j = 0; j < SSD1306_WIDTH; j++){
        //i2c_master_write_byte(i2c_master_instance, 0x00);
        i2c_tx_packet[j+1] = 0x00;
        size = j;
    }
    Tx_data_send(i2c_tx_packet, j);
}

void ssd1306_clear(){
    uint8_t i;
    for(i = 0; i < NUMBER_OF_PAGES; i++){
        ssd1306_clear_page(i);
    }
}

void ssd1306_clear_line(uint8_t line_number){
    if( line_number >= NUMBER_OF_LINES ){
        return;
    }

    ssd1306_clear_page(line_number);
    ssd1306_clear_page(line_number + NUMBER_OF_LINES);
}

void ssd1306_print_line(uint8_t line_number,  char* str){
    uint8_t number_of_char = strlen(str);
    if( line_number >= NUMBER_OF_LINES ){
        return;
    }
    if( number_of_char > NUMBER_OF_CHAR_PER_LINE ){
        number_of_char = NUMBER_OF_CHAR_PER_LINE;
    }
    ssd1306_clear_line(line_number);
    uint8_t i;
    for(i = 0; i < number_of_char; i++){
        ssd1306_print_char(line_number, i, *(str + i));
    }
}

static void ssd1306_print_char(uint8_t line_number, uint8_t column, char c){
    uint8_t* font_bitmap = (uint8_t *)&font[(uint16_t)(c * (SSD1306_FONT_WIDTH))];

    if( column > NUMBER_OF_CHAR_PER_LINE ){
        return;
    }
    if( line_number > NUMBER_OF_LINES ){
        return;
    }

    // Set vertical addressing mode
    ssd1306_command(SSD1306_MEMORYMODE);
    ssd1306_command(1);

    // Set column start and end address
    ssd1306_command(SSD1306_COLUMNADDR);
    if( column == 0 ){
        ssd1306_command( 0 );
        } else {
        ssd1306_command( column * SSD1306_FONT_WIDTH + 1 );
    }
    ssd1306_command( (column + 1) * SSD1306_FONT_WIDTH );

    // Set page start and end address
    ssd1306_command(SSD1306_PAGEADDR);
    ssd1306_command(line_number);
    ssd1306_command(line_number);


    i2c_tx_packet[0] = SSD1306_TRANSMISSION_DATA;

    uint8_t i;
    for(i = 0; i < SSD1306_FONT_WIDTH; i++){

        i2c_tx_packet[i+1] = *(font_bitmap + i);
    }

    Tx_data_send(i2c_tx_packet, i);
}

