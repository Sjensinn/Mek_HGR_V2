/* 
 * File:   robot.h
 * Author: Sjensi
 *
 * Pre-Requirements: 
 * --PIC16F18877 Microcontroller
 * --16MHz Fosc : if not we must change SSP1ADD
 * --Using MSSP1 with pins RC3 and RC4 for SCL & SDA
 * 
 * Created on February 18, 2022, 15:26
 */

 #include <xc.h>

#define SERVO1MIN 100
#define SERVO1MAX 500

uint8_t servo1_stat = 300;

    volatile uint8_t data_in = 0;

    void process(uint8_t data);
    
    void move_servo1_up(uint8_t n);

    void move_servo1_down(uint8_t n);

    