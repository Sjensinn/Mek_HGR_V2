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
#include "Stepper.h"
#include "robot.h"
#include "dc.h"

volatile uint8_t data_in; //each byte transmission
volatile uint8_t data_flex; //00XXXXXX was XXXXXX-00
volatile uint8_t data_fingers; //f3 | f2 | f1 | Axdir | Aydir | NA | NA | ADDR1 | ADDR0  (01)
volatile uint8_t data_x; //00XXXXXX was XXXXXX-10
volatile uint8_t data_y; //00XXXXXX was XXXXXX-11 
volatile uint8_t ready = 0;


void __interrupt() receive_isr();

void main(void) {
    int8_t x;
    int8_t y;
    system_init(); //Initiate clock, pins, uart, i2c, timer1 and interrupts
    //PCA_Init(130, 0x08);            //Initiate PCA9685 unit with I2C address: 0x80 and prescalar of 130
    stepper_init();

    while (1) {
        if (ready) { //from receive_isr() data_in->data_y 
            ready = 0;

            switch (data_fingers & 0b11100000) {
                    x = (data_x) + (data_fingers << 3 & 0b10000000); //convert to signed
                    y = (data_y) + (data_fingers << 4 & 0b10000000); //sign-0-XXXXXX
                case 0b00100000: //DC on, Stepper off
                    drive(x, y);
                    break;
                case 0b01000000: //Stepper on, Shoulder servo(3) on, DC off
                    shoulder(x, y);
                    break;
                case 0b10000000: //Elbow servo(2) on, Wrist servo(1) on, DC off, Stepper off 
                    front_arm(x, y);
                    break;
                default:
                    break;
            }

            printf(0xAA); //biðja um update //má senda beint hex?
        }
        //Gætum disablað uart interrupts á köflum ef við þurfum heil datasett.(?)
        //flex(data_flex>>2); //Grabber servo(0)




    }

    return;
}

void __interrupt() receive_isr() {//bæta counter á þetta ef það er eitthvað vesen

    while (RCIF == 1) {
        data_in = RCREG;
    }
    switch (data_in & 0b11) {
        case 0:
            data_flex = data_in >> 2;
            break;
        case 1:
            data_fingers = data_in;
            break;
        case 2:
            data_x = data_in >> 2;
            break;
        case 3:
            data_y = data_in >> 2;
            //if (CCP1IF == 0) {
            ready = 1;
            //setja data_in = 0b00000100 eða eitthvað sem triggerar default?
            //}
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