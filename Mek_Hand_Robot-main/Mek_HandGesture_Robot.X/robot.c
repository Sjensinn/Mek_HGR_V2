
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

void process(uint8_t data_flex, uint8_t data_fingers, uint8_t data_x, uint8_t data_y){
    int8_t x = (int8_t)data_x + ((data_fingers<<3) & 0b10000000);
    int8_t y = (int8_t)data_y + ((data_fingers<<3) & 0b10000000);
    if((data_fingers>>4) == 1){ // if finger1
        //uart_Write((uint8_t)y);
        dc_move(x, y);
    }
    
}
void hold() {
    dc_stop();
    stepper_stop();
}

void shoulder(uint8_t data_x, uint8_t data_y) {
    //move_servo(3, data_y, &servo3_stat);
}

void front_arm(uint8_t data_x, uint8_t data_y) {
    //move_servo(1, data_y, &servo1_stat);
    //move_servo(2, data_x, &servo2_stat);
}

void move_servo(uint8_t servo, uint8_t data, uint16_t servo_stat){
    /*
    *servo_stat += data;
     if (*servo_stat <= (SERVO1MAX - 10)) {
        *servo_stat += 10;
    }
     
     if (*servo_stat >= (SERVO1MIN + 10)) {
        *servo_stat -= 10;
    }
     PCA_write(servo, 0x00, *servo_stat);
     *      */
}

void dc_pwm(uint8_t dc, uint8_t data, uint16_t *EN_stat){
    *EN_stat += data;
     if (*EN_stat <= (SERVO1MAX - 10)) { //redefine min/max
        *EN_stat += 10;
    }
     
     if (*EN_stat >= (SERVO1MIN + 10)) {
        *EN_stat -= 10;
    }
     PCA_write(dc, 0x00, *EN_stat);
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