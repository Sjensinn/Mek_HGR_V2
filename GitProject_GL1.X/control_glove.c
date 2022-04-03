/* 
 * File:   control_glove.c
 * Author: Sjensi
 *
 * Created on February 14, 2022, 4:17 PM
 */




#include <xc.h>
#include <stdlib.h>
#include "control_glove.h"
#include "gy_521.h"

    
    uint16_t get_Flex_Data(){
        //*Flex = PORTAbits
        return 0;
    }

    uint8_t format_data_b1(uint16_t flex){
        uint8_t b = 0;          //Variable to return

        b = (flex/1024) << 2;   //Maximum resolution of 64
        b = b & 11111100;       //make sure address is correct
        return b;               //Return the formatted data
    }

    uint8_t format_data_b2(uint8_t f1, uint8_t f2, uint8_t f3, uint8_t axd, uint8_t ayd){
        uint8_t b = 0;

        //Fingers
        if (f1 > 0)
            b = b+32;
        else if(f2 > 0)
            b = b+64;
        else if(f3 > 0)
            b = b+128;

        //Accel X dir
        if (axd == 1)
            b = b + 16;
        //Accel Y dir
        if(ayd == 1)
            b = b + 8;
        //Address
        b = b + 1;       //make sure address is correct
        return b;               //Return the formatted data
    }

    uint8_t format_data_b3(int16_t ax){
        uint8_t b = 0;

        b = (abs(ax)/512) << 2; //Try 512, because normal data ranges from -10k to +10k
        b = b + 2;
        return b;
    }

    uint8_t format_data_b4(int16_t ay){
        uint8_t b = 0;

        b = (abs(ay)/512) << 2; //Try 512, because normal data ranges from -10k to +10k
        b = b + 3;
        return b;
    }