#include "adc.h"
#include "uart.h"
#include "system_init.h"

void flexSensor(void)
{   
	int input_adc;
	ADCON0bits.GO = 1;			// Turn on analog signal read
	while(ADCON0bits.GO == 1)	// While signal is being read.
	{
		result = (ADRESH << 8) + ADRESL  ; // Right shifted.
	}
    
    	if(input_adc > 900)
    	{
        	// Move motor
		// Send signal to motor through UART.
    	}
}

void adcon_setup(void)
{
	ADCON0bits.ADON = 1;    // Turn on the module
	ADCON0bits.ADCONT = 0  // ADGO is retriggered
	ADCON0bits.ADCS = 0;   // Clock supplied by FOSC, according to ADCLK register.
    	ADCON0bits.ADFRM0 = 1;      // Right justified for 10 bit result.   	
}


void adclk_setup(void)
{
	ADCLKbits.ADCCS = 0b001;    // FOSC/4
}

void ansel_setup(void)
{
	ANSELAbits.ANSA0 = 1; 	// RA0 analog
}

void adref_setup(void)
{
	ADREFbits.ADPREF = 0b00;    // VREF is connected to VDD
	
}

void adpch_setup(void)
{	
	ADPCHbits.ADPCH = 0b0000000; // AN0 selection register? Page 354
}
