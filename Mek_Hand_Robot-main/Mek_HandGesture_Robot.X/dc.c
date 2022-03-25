#include <xc.h>
#include "dc.h"
#include "PCA9685_driver.h"
#include "uart.h"
#include "I2C_MSSP1_driver.h"
void dc_stop() {
    LATB &= 0b11001001;
    //write PCA = 0 for EN A,B 
}

void dc_move(int8_t x, int8_t y) { //0b---XXXX- these four pins control direction of spin

     ENA_stat += (y& 0b01111111);
     ENB_stat += (y& 0b01111111);
     
     if (ENA_stat > (DCMAX)) { //redefine min/max
        ENA_stat = DCMAX;
    }
     if (ENA_stat < (DCMIN)) {
        ENA_stat = DCMIN;
    }
     if (ENB_stat > (DCMAX)) { //redefine min/max
        ENB_stat = DCMAX;
    }
     if (ENB_stat < (DCMIN)) {
        ENB_stat = DCMIN;
    }
     
     PCA_write(0, 0x00, (ENA_stat));
     PCA_write(1, 0x00, (ENB_stat));
     uart_Write((uint8_t)ENA_stat);
    if (x >> 7) {  // X0000000 -> 0000000X
       // move_servo(5, (data_y - data_x), ENA_stat); //(-) because negative x is added (could be data_y + (data_x & 0b00111111))
       // move_servo(5, (data_y), ENB_stat);
    } else {            //right tilt
       // move_servo(5, data_y, ENA_stat);
       // move_servo(5, data_y + data_x, ENB_stat);
    }

    if (y >> 7) {  //  Y0000000 -> 0000000Y
        //uart_Write((uint8_t)y);
        LATB &= 0b11101101;
        LATB |= 0b00100100;

    } else { //backwards tilt
        LATB &= 0b11011011;
        LATB |= 0b00010010;
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