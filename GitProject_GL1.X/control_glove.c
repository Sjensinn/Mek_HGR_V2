/* 
 * File:   control_glove.c
 * Author: Sjensi
 *
 * Created on February 14, 2022, 4:17 PM
 */



#include <xc.h>
#include "control_glove.h"
#include "gy_521.h"
#include "adc.h"

    //void get_Gyro_Accel(int16_t *AX, int16_t *AY, int16_t *AZ, int16_t *GX, int16_t *GY, int16_t *GZ);

    void get_Finger_Data(uint8_t *F1, uint8_t *F2, uint8_t *F3){
        &F1 = PORTBbits.RB0;
        &F2 = PORTBbits.RB1;
        &F3 = PORTBbits.RB2;
        
        return;
    }
    
    void get_Flex_Data(uint8_t *Flex){
        
    }
