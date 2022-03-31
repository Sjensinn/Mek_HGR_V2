
#include <xc.h>
#include "I2C_MSSP1_driver.h"
#include "uart.h"
#include "PCA9685_driver.h"
#include "dc.h"
#include "Stepper.h"
#include "robot.h"

//data_flex; //00XXXXXX
//data_fingers; //f3 | f2 | f1 | Axdir | Aydir | NA | ADDR1 | ADDR0  (01)
//data_x; //00XXXXXX was XXXXXX-10
//data_y; //00XXXXXX was XXXXXX-11

void process(uint8_t data_flex, uint8_t data_fingers, uint8_t data_x, uint8_t data_y) {

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

    if ((data_fingers & 0b00100000) == 0b00100000) { //finger 1
        dc_move(data_x, data_y, xdir, ydir);
    } else if ((data_fingers & 0b01000000) == 0b01000000) { //finger 2
        update_servo0_stat(data_x, xdir);
        PCA_write(0, 0, servo0_stat);
        update_servo1_stat(data_x, xdir);
        PCA_write(1, 0, servo1_stat);
    } else if ((data_fingers & 0b10000000) == 0b10000000) { //finger 3
        update_servo2_stat(data_x, xdir);
        PCA_write(2, 0, servo1_stat);
        //setja stepper (og færa hvað er á hvaða fingri)
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
        servo0_stat += (uint16_t) data;
    } else {
        servo0_stat -= (uint16_t) data;
    }
}

void update_servo1_stat(uint8_t data, uint8_t dir) {
    if (dir == 1) {
        servo1_stat += (uint16_t) data;
    } else {
        servo1_stat -= (uint16_t) data;
    }
}

void update_servo2_stat(uint8_t data, uint8_t dir) {
    if (dir == 1) {
        servo2_stat += (uint16_t) data;
    } else {
        servo2_stat -= (uint16_t) data;
    }
}

void update_servo3_stat(uint8_t data, uint8_t dir) {
    if (dir == 1) {
        servo3_stat += (uint16_t) data;
    } else {
        servo3_stat -= (uint16_t) data;
    }
}