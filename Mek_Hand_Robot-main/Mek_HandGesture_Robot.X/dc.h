#ifndef DC_H
#define	DC_H

#include <xc.h>

#define DCMAX 1300
#define DCMIN 100

uint16_t ENA_stat = 100;
uint16_t ENB_stat = 100;


void dc_stop();
void dc_move(uint8_t x, uint8_t y, uint8_t xdir, uint8_t ydir);

#endif