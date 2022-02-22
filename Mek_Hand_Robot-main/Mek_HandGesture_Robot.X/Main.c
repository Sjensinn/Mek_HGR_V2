/*
 * File:   Main.c
 * Author: Sjensi
 *
 * Mekatronisk Kerfi 1 : Gesture controlled Robot
 * 
 *  * Created on February 6, 2022, 9:50 PM
 */

#ifndef _XTAL_FREQ
#define _XTAL_FREQ 16000000
#endif

#include <xc.h>
#include <stdio.h>
#include "config_bits.h"
#include "system_init.h"
#include "PCA9685_driver.h"
#include "I2C_MSSP1_driver.h"
#include "uart.h"
#include "stepper.h"
#include "robot.h"
#include "dc.h"

volatile uint8_t data_in;

void __interrupt() receive_isr();

void main(void) {
    system_init();                  //Initiate clock, pins, uart, i2c, timer1 and interrupts
    //PCA_Init(130, 0x08);            //Initiate PCA9685 unit with I2C address: 0x80 and prescalar of 130
    stepper_init();
    
    while(1){
        process(data_in);
        //process(0b11000010);
        //LATB = 0b00010100;
    }

    return;
}

void __interrupt() receive_isr() { //lesa gögnin með þessu
    while (RCIF == 1) {
        data_in = RCREG;
        //process(RCREG);
    }
}

