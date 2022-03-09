/* 
 * File:   uart.h
 * Author: Sjensi & Danni
 * 
 * UART driver for PIC16F18877 
 * Prerequirements:
 * -16MHz int osc
 * -using pins RC6->EUSART:TX and RC7->EUSART:RX
 * 
 */

#ifndef UART_H
#define	UART_H
#include <xc.h>

#ifdef	__cplusplus
extern "C" {
#endif
    
#ifndef _XTAL_FREQ
#define _XTAL_FREQ 16000000
#endif
    

#define READYSIGNAL 0xAA

/**
 * @brief   This function intitiates the USART module in asynchronous mode
 * @param   void             
 * @return  void
 * 
 *      Baudrate: 9600
 */
void uart_init(void);

/**
 * @brief   This function writes one character to USART bus
 * @param   char data: byte to be written to RX pin          
 * @return  void
 */
void uart_Write(unsigned char data);

/**
 * @brief   This function writes a string to USART bus
 * @param   char* buf: pointer to char array (string)             
 * @return  void 
 */
void uart_Write_String(char* buf);

/*
 * @brief   This function writes to TXREG
 * @param   data: characted to write           
 * @return  void 
*/
void putch(char data);

/**
 * @brief   This function sends Ready signal
 * @param   void             
 * @return  void
 * 
 */
void send_ready(void);

/**
 * @brief   This function verifies Ready signal
 * @param   data: Data rx from UART             
 * @return  Returns 0 for NReady
 *                  1 for Ready
 */
uint8_t is_ready(uint8_t data);

/**
 * @brief   This function sends commands from control to robot
 * @param   *data: pointer to Data to tx to robot            
 * @return  void
 * 
 * Call: send_commands(data); 
 * Where data is the array containing the four bytes
 * 
 */
void send_commands(uint8_t* data);

#ifdef	__cplusplus
}
#endif

#endif	/* UART_H */

