/*
 * File:   adc.c
 * Author: Sindri Jens
 *
 * Created on April 7, 2022, 1:52 PM
 */


#include <xc.h>
#include "adc.h"

void adc_initialize(void){
    TRISAbits.TRISA0 = 1;
    PORTAbits.RA0 = 1; 
    ANSELAbits.ANSA0 = 1; //--
    ADREFbits.ADNREF = 1; //VREF- is connected to VREF- pin
    ADREFbits.ADPREF1 = 1;//10 = VREF+ is connected to VREF+ pin
    ADREFbits.ADPREF0 = 0;
    ADCON0bits.ADCS = 0; //0 = Clock supplied by FOSC, divided according to ADCLK register

    //Velja clock.
    /*REGISTER 23-6: ADCLK: ADC CLOCK SELECTION REGISTER
    bit 5-0 ADCCS<5:0>: ADC Conversion Clock Select bits
    111111 = FOSC/128
    111110 = FOSC/126
    111101 = FOSC/124
    ?
    ?
    ?
    000000 = FOSC/2/*/
    ADCLK = 0;
    ADCON0bits.ADFRM0 = 1; //1 = ADRES and ADPREV data are right-justified

    //stýring
    ADCON0bits.ADON = 1; //1 = ADC is enabled
    ADCON0bits.ADCONT = 0; //0 = ADGO is cleared upon completion of each conversion trigger
    /*
     bit 0 ADGO: ADC Conversion Status bit
    1 = ADC conversion cycle in progress. Setting this bit starts an ADC conversion cycle. The bit is
    cleared by hardware as determined by the ADCONT bit
    0 = ADC conversion completed/not in progress
     */

    }

uint16_t adc_readvalue(void){
    adcval = ADRESH;
    adcval = adcval<<8;
    adcval += ADRESL;
    return adcval;
}
uint16_t adc_measure(){
    ADCON0bits.ADGO = 1;
    while(ADCON0bits.ADGO == 1);
    //return adc_readvalue();
    return ADRES;
}