
#include <xc.h>
#include "I2C_MSSP1_driver.h"
#include "uart.h"
#include "PCA9685_driver.h"
#include "dc.h"
#include "stepper.h"
#include "robot.h"



void hold() {
    dc_stop();
    stepper_stop();
}

void drive(uint8_t data_x, uint8_t data_y) {
    stepper_stop();
    dc_move(data_x, data_y);
}

void shoulder(uint8_t data_x, uint8_t data_y) {
    
    move_servo(3, data_y, &servo3_stat);
}

void front_arm(uint8_t data_x, uint8_t data_y) {
    move_servo(1, data_y, &servo1_stat);
    move_servo(2, data_x, &servo2_stat);
}

void move_servo(uint8_t servo, uint8_t data, uint16_t *servo_stat){
    *servo_stat += data;
     if (*servo_stat <= (SERVO1MAX - 10)) {
        *servo_stat += 10;
    }
     
     if (*servo_stat >= (SERVO1MIN + 10)) {
        *servo_stat -= 10;
    }
     PCA_write(servo, 0x00, *servo_stat);
}
void dc_pwm(uint8_t servo, uint8_t data, uint16_t *EN_stat){
    *EN_stat += data;
     if (*EN_stat <= (SERVO1MAX - 10)) { //redefine min/max
        *EN_stat += 10;
    }
     
     if (*EN_stat >= (SERVO1MIN + 10)) {
        *EN_stat -= 10;
    }
     PCA_write(servo, 0x00, *EN_stat);
}

void move_servo1_up(uint8_t n) {

    /*
     Servo1_stat += data_x
     */
    //Check if we are at limit for servo

    if (servo1_stat <= (SERVO1MAX - 10)) {
        servo1_stat += 10;
    }

    PCA_write(n, 0x00, servo1_stat);
}

void move_servo1_down(uint8_t n) {
    if (servo1_stat >= (SERVO1MIN + 10)) {
        servo1_stat -= 10;
    }

    PCA_write(n, 0x00, servo1_stat);
}