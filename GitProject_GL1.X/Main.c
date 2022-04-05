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

#define F1_getVal() PORTBbits.RB0
#define F2_getVal() PORTBbits.RB1
#define F3_getVal() PORTBbits.RB2

#include "config_bits.h"
#include "system_init.h"
#include <xc.h>
#include <stdio.h>
#include "I2C_MSSP1_driver.h"
#include "gy_521.h"
#include "uart.h"
#include "control_glove.h"

void __interrupt() isr();

volatile uint8_t data_in;
volatile uint8_t ready_flag = 0;

void main(void) {
    system_init();                  //Initiate clock, pins, uart, i2c, timer1 and interrupts
    gy_init(0x68);                  //Initiate MPU6050 with I2C address: 0x68
    
    //Variables
    int16_t accelo_x, accelo_y;
    uint8_t axd, ayd;
    uint16_t flex;
    uint8_t tx_data[4];


    while(1){
        //if(is_ready(0b11111111) == 1)
        //    ready_flag = 1;
        //else
        //    ready_flag = 0;
        
        if(ready_flag == 1){
            //Fetch data
            gy_Read(&accelo_x, &accelo_y); //Fetch data from Gyro
            flex = 0000; //get_Flex_Data();         //Fetch data from flex
            if(accelo_x > 0)
                axd = 1;
            else
                axd = 0;
            if(accelo_y > 0)
                ayd = 1;
            else
                ayd = 0;

            //Format data
            tx_data[0] = format_data_b1(flex);
            tx_data[1] = format_data_b2(F1_getVal(), F2_getVal(), F3_getVal(), axd, ayd);
            tx_data[2] = format_data_b3(accelo_x);
            tx_data[3] = format_data_b4(accelo_y);
            
            //Send data
            send_commands(tx_data);

            __delay_ms(100);
        }
    }
    return;
}

void __interrupt() isr() { //lesa gögnin með þessu
    while (RCIF == 1) {
        data_in = RCREG;
    }
    if (is_ready(data_in) == 1) { 
        ready_flag = 1;
    }
}



