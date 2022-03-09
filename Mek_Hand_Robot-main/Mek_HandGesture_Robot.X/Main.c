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
volatile uint8_t data_flex; //XXXXXX-00
volatile uint8_t data_fingers; //----XX-01
volatile uint8_t data_x; //XXXXX-dir-10
volatile uint8_t data_y; //XXXXX-dir-11 

void __interrupt() receive_isr();

void main(void) {
    system_init(); //Initiate clock, pins, uart, i2c, timer1 and interrupts
    //PCA_Init(130, 0x08);            //Initiate PCA9685 unit with I2C address: 0x80 and prescalar of 130
    stepper_init();

    while (1) {
        //flex(data_flex>>2); //Grabber servo(0)
        switch (data_fingers >> 2) {
            case 0: //all off
                hold();
                break;
            case 1: //DC on, Stepper off
                drive(data_x, data_y);
                break;
            case 2: //Stepper on, Shoulder servo(3) on, DC off
                shoulder(data_x >> 2, data_y >> 2);
                break;
            case 3: //Elbow servo(2) on, Wrist servo(1) on, DC off, Stepper off 
                front_arm(data_x >> 2, data_y >> 2);
                break;
            default:
                break;
        }
        //process(0b11000010);
        //LATB = 0b00010100;
        
        //if(flag){ //sjá receive_isr() data_in->case 3
        printf("könnte ich noch eins haben"); //request an update (t.d. 0b00101010)
        printf("Bitte"); //Manners
    }

    return;
}

void __interrupt() receive_isr() {

    while (RCIF == 1) {
        data_in = RCREG;
    }
    switch (data_in & 0b11) {
        case 0:
            data_flex = data_in;
            break;
        case 1:
            data_fingers = data_in;
            break;
        case 2:
            data_x = data_in;
            break;
        case 3:
            data_y = data_in;
            if (CCP1IF == 0) {
                //Setja flag fyrir request update hérna? 
                //fer bara í ef stepper kallaði ekki á interrupt

            }
            break;
        default:
            break;
    }



    if (CCP1IF == 1) { //compare flag
        CCP1IF = 0;
        LATDbits.LATD5 ^= 1; //toggle pin for A4988
        //CCPR1H = 0x00;
        //CCPR1L = 0xFA; //0.0005s 500us 0xFA = 0.5ms@16Mhz
        CCPR1H = 0x01; //Finna út úr því hvernig er best að breyta þessari breytu
        CCPR1L = 0x34; //0.0005s 500us 0x134 = 0.616ms@(((16Mhz)/4)/8)
    }

}