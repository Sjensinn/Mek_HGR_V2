#include <xc.h>
#include "Stepper.h"
int counter = 0; //Needs another solution
void stepper_init(){
    TRISD = TRISD | 0b00001111; //
    CCP1IF = 0; //Clear flag

    T1CONbits.CKPS0 = 0; //prescaler 4
    T1CONbits.CKPS1 = 1; //^
    T1CONbits.RD16 = 0; //1 = TMR1H is buffered
    
    T1CONbits.ON = 1;  //1 = Count enabled, 1 = Always on, otherwise off.
    T1GCONbits.GE = 0; //1 = ^              0 = ^

    CCP1CON = 0b10001011; //Compare mode: output will pulse 0-1-0; Clears TMR1
    T1CLK = 0b00000001; //Fosc/4
    INTCONbits.GIE = 1; //Enables all active interrupts
    INTCONbits.PEIE = 1; //Enables all active peripheral interrupts
    PIE6bits.CCP1IE = 1; //CCP1 interrupt is enabled 
    CCPR1L = 0xFF; //compare values
    CCPR1H = 0x00;
}
void set_stepper_speed(uint8_t high, uint8_t low){
    CCPR1H = high;
    CCPR1L = low;
}
void __interrupt() isr(void) { 
    if (CCP1IF == 1) {  //compare flag
        CCP1IF = 0;
        CCPR1L = 0x88; //compare values 0x1388=5ms@16Mhz
        CCPR1H = 0x13;
        if (counter >= 4) {
            counter = 0;
        } else {
            counter++;
        }
        if (counter == 0) {    //drive mode can be changed
            LATDbits.LATD0 = 1;
            LATDbits.LATD1 = 0;
            LATDbits.LATD2 = 0;
            LATDbits.LATD3 = 0;
        }
        if (counter == 1) {
            LATDbits.LATD0 = 0;
            LATDbits.LATD1 = 1;
            LATDbits.LATD2 = 0;
            LATDbits.LATD3 = 0;
        }
        if (counter == 2) {
            LATDbits.LATD0 = 0;
            LATDbits.LATD1 = 0;
            LATDbits.LATD2 = 1;
            LATDbits.LATD3 = 0;
        }
        if (counter == 3) {
            LATDbits.LATD0 = 0;
            LATDbits.LATD1 = 0;
            LATDbits.LATD2 = 0;
            LATDbits.LATD3 = 1;
        }
    }
}