/*
 * File:   pwm.c
 * Author: Sindri Jens
 *
 * Created on April 7, 2022, 2:02 PM
 */


#include <xc.h>
void PWM6_Initialize(void){
    // Set the PWM to the options selected in the PIC10 / PIC12 / PIC16 / PIC18 MCUs.
    // PWM6POL active_hi; PWM6EN enabled; 
    PWM6CON = 0x80;   //PWM6 enable
    RA2PPS = 0x0E;
    //PWM6DCH = 0x0F;   //pulse width length
    //PWM6DCL = 0x40;

    // Select timer
    CCPTMRS1bits.P6TSEL = 1; //PWM6 based on TMR2
    //CCPTMRS1bits.P6TSEL0 = 0;
    //CCPTMRS1bits.P6TSEL1 = 1;
}
void TMR2_Initialize(void){
    // Set TMR2 to the options selected in the User Interface
    T2CLKCON = 0x01; // T2CS FOSC/4; 
    T2HLT = 0x00; // T2PSYNC Not Synchronized; T2MODE Software control; T2CKPOL Rising Edge; T2CKSYNC Not Synchronized; 
    T2RST = 0x00; // T2RSEL T2CKIPPS pin; 
    //T2PR = 0x9B; //Þetta var áður
    T2PR = 77; //155 = 20kHz@16Mhz with 1 prescaler
    T2TMR = 0x00;//Holding register for the 8-bit TMR2; 
    PIR4bits.TMR2IF = 0;    // Clearing IF flag.

    T2CON = 0b10000000; //TMR2 on, pre 1:1 post 1:1  //var 0xF3 = T2CKPS 1:128; T2OUTPS 1:4; TMR2ON on; 
}

void PWM6_LoadDutyValue(uint16_t dutyValue){

    // Writing to 8 MSBs of PWM duty cycle in PWMDCH register
    PWM6DCH = (dutyValue & 0x03FC)>>2;
    // Writing to 2 LSBs of PWM duty cycle in PWMDCL register
    PWM6DCL = (dutyValue & 0x0003)<<6;
}