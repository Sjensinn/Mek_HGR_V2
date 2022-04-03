
#include <xc.h>
#include "uart.h"
#include "stdio.h"

void uart_init(void){
    RC6PPS = 0x10;
    SPBRGL = 25; //25 fyrir 9600@16mhz
    SPBRGH = 0;
    BAUDCONbits.BRG16 = 0;  //16scaler  0=64 scaler(8bit))
    TX1STAbits.BRGH = 0;    //high speed off
    BAUD1CONbits.SCKP = 0;
    RC1STAbits.SPEN = 1;    //Setting the SPEN bit of the RCSTA register enables the EUSART and automatically configures the TX/CK I/O pin as an output.
    TX1STAbits.SYNC = 0;    //asynchronous 
    RC1STAbits.CREN = 1;    //RX on
    TX1STAbits.TXEN = 1;    //transmit enabled
    PIE3bits.RCIE = 1;      //Recieve Interrupt Enable for USART
}

void uart_Write(unsigned char data){
    while(0 == PIR3bits.TXIF){
        continue;
    }
    TX1REG = data;    // Write the data byte to the USART.
}

void uart_Write_uint8(uint8_t data){
        while(0 == PIR3bits.TXIF){
        continue;
    }
    TX1REG = data;    // Write the data byte to the USART.
}
void uart_Write_String(char* buf){
    int i=0;
    while(buf[i] != '\0'){
        uart_Write(buf[i++]);
    }
}

void putch(char data) {
    while (!TXIF) // check buffer
        continue; // wait till ready
    TXREG = data; // send data
}


void send_ready(void){
    uart_Write_uint8(READYSIGNAL);
}


uint8_t is_ready(uint8_t data){
    if (data == READYSIGNAL)
        return 1;
    else
        return 0;
}


void send_commands(uint8_t* data){
    for (int i = 0; i < 4; i++){
        //printf(*data);
        uart_Write(*data);
        data++;
        __delay_ms(1);
    }
    
}