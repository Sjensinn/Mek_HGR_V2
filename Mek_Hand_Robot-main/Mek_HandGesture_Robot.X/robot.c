
#include <xc.h>
#include "I2C_MSSP1_driver.h"
#include "uart.h"
#include "PCA9685_driver.h"
#include "dc.h"
#include "Stepper.h"
#include "robot.h"
#include "pwm.h"

//data_flex; //00XXXXXX
//data_fingers; //f3 | f2 | f1 | Axdir | Aydir | NA | ADDR1 | ADDR0  (01)
//data_x; //00XXXXXX was XXXXXX-10
//data_y; //00XXXXXX was XXXXXX-11

void process(uint8_t data_flex, uint8_t data_fingers, uint8_t data_x, uint8_t data_y) {
    
    update_servo3_stat(data_flex);

    if ((data_fingers & 0b00010000) == 0b00010000) {
        xdir = 1;
    } else {
        xdir = 0;
    }
    if ((data_fingers & 0b00001000) == 0b00001000) {
        ydir = 1;
    } else {
        ydir = 0;
    }

    if ((data_fingers & 0b00100000) == 0b00100000) { //finger 1 = wheels
        stepper_stop();
        //PCA_Set_Freq(0x03); //Update output frequency of PCA
        
        if (data_y > 4) {
            dc_move(data_y, ydir);
        } else if (data_x > 4) {
            dc_turn(data_x, xdir);
        } else {
            dc_stop();
        }

    } else if ((data_fingers & 0b01000000) == 0b01000000) { //finger 2 = shoulder
        stepper_stop();
        dc_stop();
        //PCA_Set_Freq(130);

        if(data_x > 10){
            update_servo0_stat(data_x, xdir);
        }
        if(data_y > 10){
            update_servo1_stat(data_y, ydir);
        }
    } else if ((data_fingers & 0b10000000) == 0b10000000) { //finger 3 = wrist
        dc_stop();

        if (xdir == 1 && data_x > 10) {
            stepper_move(1);
            __delay_ms(10);
        } else if (xdir == 0 && data_x > 10) {
            stepper_move(0);
            __delay_ms(10);
        } else {
            stepper_stop();
            dc_stop();
        }
        if(data_y > 10){
            update_servo2_stat(data_y, ydir);
        }

        //PCA_write(2, 0, servo1_stat);

    }
    else{
        dc_stop();
        stepper_stop();
    }


    int8_t x = (int8_t) data_x + ((data_fingers << 3) & 0b10000000);
    int8_t y = (int8_t) data_y + ((data_fingers << 3) & 0b10000000);
    if ((data_fingers >> 4) == 1) { // if finger1
        //uart_Write((uint8_t)y);

    }
}

uint16_t get_servo0_stat() {
    return servo0_stat;
}

void update_servo0_stat(uint8_t data, uint8_t dir) {
    if (dir == 1) {
        for(int i = 0; i < data; i+=2){
            servo0_stat++;
            if(servo0_stat > SERVO0MAX)
                servo0_stat = SERVO0MAX;
            PCA_write(0, 0, servo0_stat);
        }
    } else {
        for(int i = 0; i < data; i+=2){
            servo0_stat--;
            if(servo0_stat < SERVO0MIN)
                servo0_stat = SERVO0MIN;
            PCA_write(0, 0, servo0_stat);
        }
    }
}

void update_servo1_stat(uint8_t data, uint8_t dir) {
    if (dir == 1){
        for(int i = 0; i < data; i+=2){
            servo1_stat++;
            if(servo1_stat > SERVO1MAX)
                servo1_stat = SERVO1MAX;
            PCA_write(1, 0, servo1_stat);
        }
    } else {
        for(int i = 0; i < data; i+=2){
            servo1_stat--;
            if(servo1_stat < SERVO1MIN)
                servo1_stat = SERVO1MIN;
            PCA_write(1, 0, servo1_stat);
        }
    }
}

void update_servo2_stat(uint8_t data, uint8_t dir) {
    if (dir == 1){
        for(int i = 0; i < data; i++){
            servo2_stat++;
            if(servo2_stat > SERVO2MAX)
                servo2_stat = SERVO2MAX;
            PCA_write(2, 0, servo2_stat);
        }
    } else {
        for(int i = 0; i < data; i++){
            servo2_stat--;
            if(servo2_stat < SERVO2MIN)
                servo2_stat = SERVO2MIN;
            PCA_write(2, 0, servo2_stat);
        }
    }
}

void update_servo3_stat(uint8_t data) {

        servo3_stat = data*10;
        if(servo3_stat > SERVO3MAX)
            servo3_stat = SERVO3MAX;
        if(servo3_stat < SERVO3MIN)
            servo3_stat = SERVO3MIN;
        
        PCA_write(3, 0, servo3_stat);
}