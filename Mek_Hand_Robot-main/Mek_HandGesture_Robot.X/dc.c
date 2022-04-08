#include <xc.h>
#include "dc.h"
#include "PCA9685_driver.h"
#include "uart.h"
#include "I2C_MSSP1_driver.h"
#include <stdio.h>

void dc_init(void){
    /*
     
    CCP1IF = 0; //Clear flag
    T1CONbits.CKPS1 = 1;
    T1CONbits.CKPS0 = 1; // 11 = 8ps
    T1CONbits.RD16 = 0; //1 = TMR1H is buffered
    //T1CONbits.ON = 1; //1 = Count enabled, 1 = Always on, otherwise off.
    T1GCONbits.GE = 0;  //1 = ^              0 = ^
    CCP1CON = 0b10001011; //Compare mode: output will pulse 0-1-0; Clears TMR1
    T1CLK = 0b00000001; //Fosc/4
    INTCONbits.GIE = 1; //Enables all active interrupts
    INTCONbits.PEIE = 1; //Enables all active peripheral interrupts
    PIE6bits.CCP1IE = 1; //CCP1 interrupt is enabled
    step_count = 0;
     * */
}

void dc_stop() {
    //LATB &= 0b11001001;
    PCA_write(4, 0x00, 1);
    PCA_write(5, 0x00, 1);
    
}

void dc_move(uint8_t y, uint8_t ydir) { //0b---XXXX- these four pins control direction of spin
    if (ydir == 1) { //forward tilt
            LATBbits.LATB1 = 1;
            LATBbits.LATB2 = 1;

        } else { //backwards tilt
            LATBbits.LATB1 = 0;
            LATBbits.LATB2 = 0;
        }

        dc_update(y);
}

void dc_turn(uint8_t x, uint8_t xdir){
        if (xdir == 1) { //right tilt
            LATBbits.LATB1 = 1;
            LATBbits.LATB2 = 0;
        } else {
            LATBbits.LATB1 = 0;
            LATBbits.LATB2 = 1;
        }
        
        dc_update(x);
}

void dc_update(uint8_t motor_speed){
        ENA_stat = ((uint16_t)motor_speed*100);
        ENB_stat = ENA_stat;
        
        if (ENA_stat >= (DCMAX)) { //redefine min/max, er 100/1300 atm
            ENA_stat = DCMAX;
        }
        if (ENA_stat <= (DCMIN)) {
            ENA_stat = DCMIN;
        }
        if (ENB_stat >= (DCMAX)) {
            ENB_stat = DCMAX;
        }
        if (ENB_stat <= (DCMIN)) {
            ENB_stat = DCMIN;
        }
        
        PCA_write(4, 0x00, ENA_stat);
        PCA_write(5, 0x00, ENB_stat);

}

void dc_update_ccp(uint8_t motor_speed){
    
}