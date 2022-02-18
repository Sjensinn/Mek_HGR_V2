/* 
 * File:   control_glove.h
 * Author: Sjensi
 *
 * Created on February 13, 2022, 4:17 PM
 */

#ifndef CONTROL_GLOVE_H
#define	CONTROL_GLOVE_H

#ifdef	__cplusplus
extern "C" {
#endif

#define ax_min -10000
#define ax_max 10000
#define ay_min -7000
#define ay_max 7000
    
void get_Finger_Data(uint8_t *F1, uint8_t *F2, uint8_t *F3);
    
void get_Flex_Data(uint8_t *Flex);

uint8_t data_Transform(int16_t flex, uint8_t f1, uint8_t f2, uint8_t f3, int16_t ax, int16_t ay);

#ifdef	__cplusplus
}
#endif
#endif	/* CONTROL_GLOVE_H */

