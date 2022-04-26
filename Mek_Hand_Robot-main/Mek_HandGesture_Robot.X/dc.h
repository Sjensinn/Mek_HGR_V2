#ifndef DC_H
#define	DC_H

#include <xc.h>

#define DCMAX 800
#define DCMIN 100

uint16_t ENA_stat = 100;
uint16_t ENB_stat = 100;

void dc_init(void);
void dc_stop();
void dc_move(uint8_t y, uint8_t ydir);
void dc_turn(uint8_t x, uint8_t xdir);
void dc_update(uint8_t motor_speed);
void dc_update_ccp(uint8_t motor_speed);

#endif