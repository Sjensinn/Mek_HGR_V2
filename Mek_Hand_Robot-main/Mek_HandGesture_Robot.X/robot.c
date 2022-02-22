
 #include <xc.h>
 #include "I2C_MSSP1_driver.h"
 #include "uart.h"
 #include "PCA9685_driver.h"
 #include "dc.h"
 #include "stepper.h"
#include "robot.h"


void process(uint8_t data) {
    /*
     * Data to transfer: 76543210
         val   bit     function
     *   128   7   -   Ay_direction : 1= fwd, 0 = bkwd
     *   64    6   -   Ay_enable : 
     *   32    5   -   Ax_direction : 1 = right 0 = left
     *   16    4   -   Ax_enable : 1 = enable | 0 = disable
     *   8     3   -   Finger 3:  Elbow/Wrist
     *   4     2   -   finger 2:  Shoulder
     *   2     1   -   Finger 1:  DC
     *   1     0   -   Flex:
     */
    if ((data & 1) == 11) { //flex
        //PCA_write();
    }

    if ((data & 2) == 2) { //if finger 1 (DC))        
        stepper_stop();
        if ((data & 64) == 64) { //Ay EN
            if ((data & 128) == 128) { //foward tilt
                DC_move(0);
            } else {
                DC_move(1); // 0-4
            }
        }
        if ((data & 16) == 16) { //Ax EN
            if ((data & 32) == 32) { //right tilt
                DC_move(2);
            } else {
                DC_move(3);
            }
        } else{
            DC_stop();
        }
    } else if ((data & 4) == 4) { //if finger 2 (shoulder)
        DC_stop();
        if ((data & 64) == 64) { //Ay EN
            if ((data & 128) == 128) { //foward tilt
                //PCA_write();
            } else {
                //PCA_write();
            }
        }
        if ((data & 16) == 16) { //Ax EN
            if ((data & 32) == 32) { //right tilt
                stepper_move(0);
            } else {
                stepper_move(1);
            }
        }
    } else if ((data & 8) == 8) { //if finger 3 (elbow/wrist)
        stepper_stop();
        DC_stop();
        if ((data & 64) == 64) { //Ay EN
            if ((data & 128) == 128) { //foward tilt
                //PCA_write();
            } else {
                //PCA_write(); // 0-4
            }
        }
        if ((data & 16) == 16) { //Ax EN
            if ((data & 32) == 32) { //right tilt
                //PCA_write();
            } else {
                //PCA_write(); // 0-3
            }
        }

    } else {
        stepper_stop();
        DC_stop();
    }

}

void move_servo1_up(uint8_t n){
    //Check if we are at limit for servo
    if(servo1_stat <= (SERVO1MAX - 10)){
        servo1_stat += 10;
    }
    
    PCA_write(n, 0x00, servo1_stat);
}

void move_servo1_down(uint8_t n){
    if( servo1_stat >= (SERVO1MIN + 10) ){
        servo1_stat -= 10;
    }

    PCA_write(n, 0x00, servo1_stat);
}