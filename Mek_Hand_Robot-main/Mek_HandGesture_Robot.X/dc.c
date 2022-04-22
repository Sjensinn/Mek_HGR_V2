#include <xc.h>
#include "dc.h"
#include "PCA9685_driver.h"
#include "uart.h"
#include "I2C_MSSP1_driver.h"
#include <stdio.h>
#include "pwm.h"

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
    PWM6_LoadDutyValue(0); //min = 0, max = 5100(98%)
    T2CONbits.T2ON = 0;

    //PCA_write(4, 0x00, 1);
    //PCA_write(5, 0x00, 1);
    
}

void dc_move(uint8_t y, uint8_t ydir) { //0b---XXXX- these four pins control direction of spin
    T2CONbits.T2ON = 1;
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
        T2CONbits.T2ON = 1;
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
        ENA_stat = ((uint16_t)motor_speed*25);
        
        if (ENA_stat >= (DCMAX)) { //redefine min/max, er 100/1300 atm
            ENA_stat = DCMAX;
        }
        if (ENA_stat <= (DCMIN)) {
            ENA_stat = DCMIN;
        }

        PWM6_LoadDutyValue(ENA_stat); //min = 0, max = 5100(98%)
}

void dc_update_ccp(uint8_t motor_speed){
    
}