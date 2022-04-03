#include <xc.h>
#include "dc.h"
#include "PCA9685_driver.h"
#include "uart.h"
#include "I2C_MSSP1_driver.h"
#include <stdio.h>

void dc_stop() {
    LATB &= 0b11001001;
}

void dc_move(uint8_t x, uint8_t y, uint8_t xdir, uint8_t ydir) { //0b---XXXX- these four pins control direction of spin
        if (ydir == 1) { //forward tilt
            //LATB &= 0b11101101;
            //LATB |= 0b00100100;
            LATBbits.LATB1 = 0;
            LATBbits.LATB2 = 1;
            LATBbits.LATB4 = 0;
            LATBbits.LATB5 = 1;

        } else { //backwards tilt
            //LATB &= 0b11011011;
            //LATB |= 0b00010010;
            LATBbits.LATB1 = 1;
            LATBbits.LATB2 = 0;
            LATBbits.LATB4 = 1;
            LATBbits.LATB5 = 0;
        }
        ENA_stat = y*100; //finna gott gildi, prufa 50
        ENB_stat = y*100;

        if (xdir == 1) { //right tilt
            ENB_stat += ((uint16_t)x*100);
        } else {
            ENA_stat += ((uint16_t)x*100);
        }

        if (ENA_stat > (DCMAX)) { //redefine min/max, er 100/1300 atm
            ENA_stat = DCMAX;
        }
        if (ENA_stat < (DCMIN)) {
            ENA_stat = DCMIN;
        }
        if (ENB_stat > (DCMAX)) {
            ENB_stat = DCMAX;
        }
        if (ENB_stat < (DCMIN)) {
            ENB_stat = DCMIN;
        }
        PCA_write(4, 0x00, (ENA_stat));
        PCA_write(5, 0x00, (ENB_stat));

}