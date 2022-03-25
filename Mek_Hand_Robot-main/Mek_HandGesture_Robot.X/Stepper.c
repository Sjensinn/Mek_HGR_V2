#include "Stepper.h"

void stepper_init(void) {
    //TRISD = 0b00000000;
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
}

void stepper_move(uint8_t direction) { //add speed
    //add formula for speed
    T1CONbits.ON = 1; //start timer
    if (direction==1) {
        LATDbits.LATD4 = 1; //dir pin on A4988
    } else {
        LATDbits.LATD4 = 0;
    }
}

void stepper_stop(void) {
    T1CONbits.ON = 0; //stop timer
}

void set_stepper_speed(uint16_t speed) {
    CCPR1L = (speed & 0xFF);
    CCPR1H = (speed >> 8) & 0xFF;
}

/*void __interrupt() isr(void) {
    if (CCP1IF == 1) { //compare flag
        CCP1IF = 0;
        LATDbits.LATD5 ^= 1; //toggle pin for A4988
        //CCPR1H = 0x00;
        //CCPR1L = 0xFA; //0.0005s 500us 0xFA = 0.5ms@16Mhz
        CCPR1H = 0x01;
        CCPR1L = 0x34; //0.0005s 500us 0x134 = 0.616ms@(((16Mhz)/4)/8)
        //CCPR1H = 0x0;
        //CCPR1L = 0xFA; //0.0005s 500us 0xFA = 0.616ms@(((16Mhz)/4)/8)
    }
}*/