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
uint8_t xdir = 0;
uint8_t ydir = 0;

uint16_t servo0_stat = 300;
uint16_t servo1_stat = 300;
uint16_t servo2_stat = 300;
uint16_t servo3_stat = 300;


void process(uint8_t data_flex, uint8_t data_fingers, uint8_t data_x, uint8_t data_y);
void update_servo0_stat(uint8_t data, uint8_t dir);
void update_servo1_stat(uint8_t data, uint8_t dir);
void update_servo2_stat(uint8_t data, uint8_t dir);
void update_servo3_stat(uint8_t data, uint8_t dir);


