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

uint16_t servo0_stat = 300;
uint16_t servo1_stat = 300;
uint16_t servo2_stat = 300;
uint16_t servo3_stat = 300;


void drive(uint8_t data_x, uint8_t data_y);
void shoulder(uint8_t data_x, uint8_t data_y);
void front_arm(uint8_t data_x, uint8_t data_y);
void move_servo(uint8_t servo, uint8_t data, uint16_t *servo_stat);
void dc_pwm(uint8_t servo, uint8_t data, uint16_t *EN_stat);
void move_servo1_up(uint8_t n);
void move_servo1_down(uint8_t n);

