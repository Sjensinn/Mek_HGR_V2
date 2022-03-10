#ifndef DC_H
#define	DC_H


#include <xc.h>
uint16_t &ENA_stat = 100;
uint16_t &ENB_stat = 100;
void dc_stop();
void dc_move(uint8_t data_x, uint8_t data_y);

#endif