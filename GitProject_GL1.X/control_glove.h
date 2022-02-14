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

    //void get_Gyro_Accel(int16_t *AX, int16_t *AY, int16_t *AZ, int16_t *GX, int16_t *GY, int16_t *GZ);
    
    void get_Finger_Data(uint8_t *F1, uint8_t *F2, uint8_t *F3);
    
    void get_Flex_Data(uint8_t *Flex);

#ifdef	__cplusplus
}
#endif

#endif	/* CONTROL_GLOVE_H */

