/*
 * File:   Main.c
 * Author: Sjensi
 *
 * Mekatronisk Kerfi 1 : Gesture controlled Robot
 * 
 * This Project belongs to the Gesture Control Glove
 * 
 * 
 * Finger 1: RB0
 * Finger 2: RB1
 * Finger 3: RB2
 * 
 * Flex: RA1
 * 
 * I2C: RC3 and RC4
 * 
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
#include "adc.h"
#include "uart.h"

void main(void) {
    system_init();                  //Initiate clock, pins, uart, i2c, timer1 and interrupts
    gy_init(0x68);                  //Initiate MPU6050 with I2C address: 0x68
    uart_init();                    //Vantar að uppfæra UART skjal
    
    //Variables for Gyro
    int16_t accelo_x, accelo_y, accelo_z;
    //Variables for Accelerometer
    int16_t gyro_x, gyro_y, gyro_z;
    //Variable for temperature
    int16_t temperature; //Dummy
    //Variables for contact bit
    uint8_t finger1, finger2, finger3;
    //Variable for flex 
    int16_t flex;

    while(1){
        LED_TOGGLE();
        gy_Read(&accelo_x, &accelo_y, &accelo_z, &gyro_x, &gyro_y, &gyro_z, &temperature); //Fetch data from Gyro
        get_Flex_Data(&flex);            //Fetch data from ADC
        get_Finger_Data(&finger1, &finger2, &finger3);          //Fetch data from Fingers
        
        //send accel and gyro data along with noFinger/finger1/finger2/finger3 variablesto Data transformation function
        //send transformed data over Xbee unit
        //__delay_ms(100); //Refresh rate needs to be decied
    }
    return;
}



