#ifndef STEPPER_H
#define	STEPPER_H


#include <xc.h>

#define STEP_MAX 500     //Maximum number of steps 
#define STEP_MIN -500    //Minimum number of steps

uint8_t step_dir;       //Variable to keep the direction
int step_count;

void stepper_init(void);
void stepper_move(uint8_t direction);
void stepper_stop(void);
void set_stepper_speed(uint16_t speed);//
void step_enable(void);
void step_disable(void);
/*
*   @Brief:   This function increments the step_count variable if 
            step_dir = 1, if not it decrements step_count
*   @param  void
*   @return void
*/
void step_inc_dec(void);
/*
*   @Brief:   This function returns the direction the stepper is turning
*   @param  void
*   @return step_dir variable
*/
int get_dir(void);
/*
*   @Brief:   This function returns the number of steps it has turned
*   @param  void
*   @return step_count variable
*/
int get_steps(void);

#endif	/* STEPPER_H */