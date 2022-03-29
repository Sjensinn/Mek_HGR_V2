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
    step_dir = direction;
    if (step_dir==1) { //forward
        if(step_count <= 50){
            step_enable();
            LATDbits.LATD4 = step_dir; //dir pin on A4988
            T1CONbits.ON = 1;
        }
        else{
            T1CONbits.ON = 0;
            step_disable();
        }
    } 
    else{ //Backwards
        if(step_count >= 0){
            step_enable();
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
    //Port A1 is connected to enable port of driver
    TRISAbits.TRISA1 = 1;
    return;
}

void step_disable(void){
    //Port A1 is connected to enable port of driver    
    TRISAbits.TRISA1 = 0;
    return;
   }

 void step_inc_dec(void){
    if(step_dir == 1)
        step_count++;
    else
        step_count--;
}

int get_dir(void){
    return step_dir;
}

int get_steps(void){
    return step_count;
}
