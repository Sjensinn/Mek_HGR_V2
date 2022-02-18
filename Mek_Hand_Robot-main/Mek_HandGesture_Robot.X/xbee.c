#include <xc.h>
#include <stdio.h>
#include <stdlib.h>
#include "xbee.h"



void eusart_init() {
    //PI3 = 0x30 = 0b00110000
    //INTCON = 0xC0 = 0b11000000
    //TX1STA = 0x1A = 0b00011010
    //RC1STA = 0x90 = 0b10010000
    //ANSELCbits.ANSC7 = 0;
    //ANSELCbits.ANSC6 = 0;
    RC6PPS = 0x10;
    SPBRGL = 25; //25 fyrir 9600@16mhz
    SPBRGH = 0;
    BAUDCONbits.BRG16 = 0; //16scaler  0=64 scaler(8bit))
    TX1STAbits.BRGH = 0; //high speed off
    BAUD1CONbits.SCKP = 0;
    RC1STAbits.SPEN = 1; //Setting the SPEN bit of the RCSTA register enables the EUSART and automatically configures the TX/CK I/O pin as an output.
    TX1STAbits.SYNC = 0; //asynchronous 
    RC1STAbits.CREN = 1; //RX on
    TX1STAbits.TXEN = 1; //transmit enabled
    
    /*PIE3bits.RCIE = 1; //receive interrupt enable
    INTCONbits.GIE = 1; //enable global interrupts
    INTCONbits.PEIE = 1; //enable peripherals
    PIE3bits.TXIE = 0; //transmit interrupt enable*/

    
}

void putch(char data) {
    while (!TXIF) // check buffer
        continue; // wait till ready
    TXREG = data; // send data
}

void uart_send(uint8_t data) { //putch
    printf("%c",data);
    //LATDbits.LATD3 ^= 1;
}
