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
#include "LCD.h"

volatile uint8_t data_in; //each byte transmission
volatile uint8_t data_flex; //00XXXXXX was XXXXXX-00
volatile uint8_t data_fingers; //f3 | f2 | f1 | Axdir | Aydir | NA | ADDR1 | ADDR0  (01)
volatile uint8_t data_x; //00XXXXXX was XXXXXX-10
volatile uint8_t data_y; //00XXXXXX was XXXXXX-11 
volatile uint8_t ready = 0;

void __interrupt() receive_isr();

void main(void) {
    int8_t x, y;
    uint8_t init_ready;
    system_init(); //Initiate clock, pins, uart, i2c, timer1 and interrupts
    //PCA_Init(130, 0x08);            //Initiate PCA9685 unit with I2C address: 0x80 and prescalar of 130
    stepper_init();
    //LCD_init(0x4E);
  
    while(1){
        init_ready = 1;     //Ready for initial communications
        while(PORTAbits.RA0){ 
            if(init_ready == 1){
                send_ready(); //send ready signal
                init_ready = 0; //Clear the initial ready
            }
            if(ready == 1){ 
                ready = 0; //Reset ready status
                //Do stuff here
                //process();
                 send_ready();
            }
        }
    }

    return;
}

void __interrupt() receive_isr() {//b�ta counter � �etta ef �a� er eitthva� vesen

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
            //setja data_in = 0b00000100 e�a eitthva� sem triggerar default?
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
        CCPR1H = 0x01; //Finna �t �r �v� hvernig er best a� breyta �essari breytu
        CCPR1L = 0x34; //0.0005s 500us 0x134 = 0.616ms@(((16Mhz)/4)/8)
    }

}