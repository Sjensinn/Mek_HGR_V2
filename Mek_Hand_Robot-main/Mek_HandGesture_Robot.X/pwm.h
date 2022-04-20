// This is a guard condition so that contents of this file are not included
// more than once.  
#ifndef XC_HEADER_TEMPLATE_H
#define	XC_HEADER_TEMPLATE_H
#include <xc.h>

void PWM6_Initialize(void);
void TMR2_Initialize(void);
void PWM6_LoadDutyValue(uint16_t dutyValue);

#endif	/* XC_HEADER_TEMPLATE_H */

