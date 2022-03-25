#ifndef STEPPER_H
#define	STEPPER_H


#include <xc.h>

void stepper_init(void);
void stepper_move(uint8_t direction);
void stepper_stop(void);
void set_stepper_speed(uint16_t speed);//

#endif	/* STEPPER_H */