#include <xc.h>
#include "dc.h"

void dc_stop() {
    LATB &= 0b11100001;
    //write PCA = 0 for EN A,B 
}

void dc_move(uint8_t data_x, uint8_t data_y) { //0b---XXXX- these four pins control direction of spin
    //                   left | right
    //forward tilt ->     +   |  + 
    //backwards tilt->    -   |  -
    //left tilt     ->    -   |  0
    //right tilt   ->     0   |  -
    //t.d. forward + right tilt =   +  |  +- 

    //**hugmynd //Snúa bílnum ef hendin hallar hvorki áfram né aftur?
    //left tilt(y = 0)->  -      +
    //right tilt(y = 0)-> +      -

    //Add PCA code for speed

    //nýtt fall í stað move_servo svo að pwm nái frá 0-100.
    if (data_x >> 8) {  //left tilt
       // move_servo(5, (data_y - data_x), ENA_stat); //(-) because negative x is added (could be data_y + (data_x & 0b00111111))
       // move_servo(5, (data_y), ENB_stat);
    } else {            //right tilt
       // move_servo(5, data_y, ENA_stat);
       // move_servo(5, data_y + data_x, ENB_stat);
    }

    if (data_y >> 8) { //forward tilt
        LATB &= 0b11110100;
        LATB |= 0b00010100;

    } else { //backwards tilt
        LATB &= 0b11101010;
        LATB |= 0b00001010;
    }

    //Left wheels
    //PCA_write() EN A //right tilt + y tilt
    // data_x(rt) + data_y(ft) = + +
    // data_x(rt) + data_y(bt) = + -

    //Right wheels
    //PCA_write() EN B //left tilt + y tilt
    // data_x(lt) + data_y(ft) = - +
    // data_x(lt) + data_y(bt) = - -
}