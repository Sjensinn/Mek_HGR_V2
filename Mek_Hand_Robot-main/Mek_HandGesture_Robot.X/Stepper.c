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
    step_enable();

    if (direction==1) {
        if(Step_count <= 50){
            step_dir = 1;
            LATDbits.LATD4 = step_dir; //dir pin on A4988
            T1CONbits.ON = 1;
        }
        else{
            T1CONbits.ON = 0;
            step_disable();
        }
    } else{
        if(Step_count >= 0){
            step_dir = 0;
            LATDbits.LATD4 = step_dir;
            T1CONbits.ON = 1;
        }
        else{
            T1CONbits.ON = 0;
            step_disable();
        }
    }
    
}

void stepper_stop(void) {
    T1CONbits.ON = 0; //stop timer
    step_disable();
}

void set_stepper_speed(uint16_t speed) {
    CCPR1L = (speed & 0xFF);
    CCPR1H = (speed >> 8) & 0xFF;
}

void step_enable(void){
    TRISAbits.TRISA1 = 1;
    return;
}

void step_disable(void){
    TRISAbits.TRISA1 = 0;
    return;
   }

 uint8_t step_count(void){
    if(step_dir == 1)
        Step_count++;
    else
        Step_count--;
    
    return Step_count;
}
