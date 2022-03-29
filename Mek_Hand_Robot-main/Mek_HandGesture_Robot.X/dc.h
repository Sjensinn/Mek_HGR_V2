#ifndef DC_H
#define	DC_H

#include <xc.h>

#define DCMAX 1300
#define DCMIN 100

int16_t ENA_stat = 700;
int16_t ENB_stat = 700;


void dc_stop();
void dc_move(int8_t x, int8_t y);

#endif