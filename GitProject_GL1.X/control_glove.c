/* 
 * File:   control_glove.c
 * Author: Sjensi
 *
 * Created on February 14, 2022, 4:17 PM
 */

/*
 * Data to transfer: 76543210
        bit     function
 *      7   -   Ay_direction : 1= fwd, 0 = bkwd
 *      6   -   Ay_enable : 
 *      5   -   Ax_direction : 1 = right 0 = left
 *      4   -   Ax_enable : 1 = enable | 0 = disable
 *      3   -   Finger 3: 
 *      2   -   finger 2:
 *      1   -   Finger 1: 
 *      0   -   Flex:            
 */


#include <xc.h>
#include "control_glove.h"
#include "gy_521.h"

    void get_Finger_Data(uint8_t *F1, uint8_t *F2, uint8_t *F3){
        *F1 = PORTBbits.RB0;
        *F2 = PORTBbits.RB1;
        *F3 = PORTBbits.RB2;

        return;
    }
    
    void get_Flex_Data(uint8_t *Flex){
        //*Flex = PORTAbits
    }

    uint8_t data_Transform(uint8_t flex, uint8_t f1, uint8_t f2, uint8_t f3, uint8_t ax, uint8_t ay){
        uint8_t transferData = 0;

        if(flex == 1){ //If flex sensor is active
            transferData += 1; 
        }    

        if(f1 == 1){ //If finger 1 touch is active
            transferData += 2;

            if(ax < ax_min || ax > ax_max){ //If accel X value is below min or above max threshold
                transferData =+ 16;
                if(ax > ax_max){
                    transferData =+ 32;
                }
            }

            if(ay < ay_min || ay > ay_max){ //If accel Y value is below min or above max threshold
                transferData =+ 64;
                if(ay > ay_max){
                    transferData =+ 128;
                }
            }
            return transferData;
        }

        //Finger 2
        if(f2 == 1){
            //For finger 1
            transferData += 4;

            //Ax
            if(ax < ax_min || ax > ax_max){ //If accel X value is below min or above max threshold
                transferData += 16;
                if(ax > ax_max){
                    transferData += 32;
                }
            }

            //Ay
            if(ay < ay_min || ay > ay_max){ //If accel Y value is below min or above max threshold
                transferData += 64;
                if(ay > ay_max){
                    transferData += 128;
                }
            }
            return transferData;
        }

        //Finger 3
        if(f3 == 1){
            transferData += 8;
            //Ax
            if(ax < ax_min || ax > ax_max){ //If accel X value is below min or above max threshold
                transferData += 16;
                if(ax > ax_max){
                    transferData += 32;
                }
            }

            //Ay
            if(ay < ay_min || ay > ay_max){ //If accel Y value is below min or above max threshold
                transferData += 64;
                if(ay > ay_max){
                    transferData += 128;
                }
            }
            return transferData;
        }
        

        return transferData; //If only flex sensor is active
    }
