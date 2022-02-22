/*
 * File:   Main.c
 * Author: Sjensi
 *
 * Mekatronisk Kerfi 1 : Gesture controlled Robot
 * This Project belongs to the Gesture Control Glove
 * 
 * Pins
 * Finger 1: RB0
 * Finger 2: RB1
 * Finger 3: RB2
 * Flex: RA0
 * I2C: RC3 and RC4
 * UART: RC6 and RC7
 * 
 *  * Created on February 6, 2022, 9:50 PM
 */

#ifndef _XTAL_FREQ
#define _XTAL_FREQ 16000000
#endif

#include "config_bits.h"
#include "system_init.h"
#include <xc.h>
#include <stdio.h>
#include "I2C_MSSP1_driver.h"
#include "gy_521.h"
#include "uart.h"

void __interrupt() isr();
volatile uint8_t data_in;

void main(void) {
    system_init();                  //Initiate clock, pins, uart, i2c, timer1 and interrupts
    gy_init(0x68);                  //Initiate MPU6050 with I2C address: 0x68
    
    //Variables for Accelerometer
    int16_t accelo_x, accelo_y;
    //Variables for contact bit
    uint8_t finger1, finger2, finger3;
    //Variable for flex 
    int16_t flex;

    while(1){
        gy_Read(&accelo_x, &accelo_y); //Fetch data from Gyro
        finger1 = 1;
        finger2 = 0;
        finger3 = 0;
        data_Transform(0, finger1, finger2, finger3, accelo_x, accelo_y); //Flex, f1, f2, f3, ax, ay
        
        //gy_test();

    }
    return;
}

void __interrupt() isr() { //lesa gögnin með þessu
    while (RCIF == 1) {
        data_in = RCREG;
    }
    if (RC1STAbits.OERR) { //overflow
        RC1STAbits.CREN = 0;
        NOP();
        RC1STAbits.CREN = 1;
    }

    if (CCP1IF == 1) { //compare flag
        CCP1IF = 0;
        LATDbits.LATD5 ^= 1; //toggle pin for A4988
        //CCPR1H = 0x00;
        //CCPR1L = 0xFA; //0.0005s 500us 0xFA = 0.5ms@16Mhz
        CCPR1H = 0x01;
        CCPR1L = 0x34; //0.0005s 500us 0x134 = 0.616ms@(((16Mhz)/4)/8)
    }
}



