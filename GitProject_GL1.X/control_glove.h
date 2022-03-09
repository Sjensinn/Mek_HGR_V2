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
    
/**
 * @brief   This functions reads the ADC value for flex sensor
 * @param   void          
 * @return  returns the value
 */
uint16_t get_Flex_Data();

//Getting replaced
uint8_t data_Transform(int16_t flex, uint8_t f1, uint8_t f2, uint8_t f3, int16_t ax, int16_t ay);

/**
 * @brief   This function formats the first byte for flex sensor
 * @param   flex: 16 bit value from flex sensor          
 * @return  Formatted 8 bit formatted value for flex
 *          2 most LSB are address = 0
 *          Data format as described:
 *          Flexbit6 | FB5 | FB4 | FB3 | FB2 | FB1 | ADDR2 | ADDR1 
 * 
 *          Must reformat 16 bit value to 6 bit value
 */
uint8_t format_data_b1(uint16_t flex);

/**
 * @brief   This function formats the second byte for finger position
 * @param   f1: Finger 1    0/1 = disconnected/connected
 *          f2: Finger 2    0/1 = disconnected/connected
 *          f3: Finger 3    0/1 = disconnected/connected     
 * @return  Formatted 8 bit value for fingers and gyro directions
 *          2 most LSB are address = 1
 *          Data format as described:
 *          f3 | f2 | f1 | Axdir | Aydir | NA | NA | ADDR1 | ADDR0
 */
uint8_t format_data_b2(uint8_t f1, uint8_t f2, uint8_t f3, uint8_t axd, uint8_t ayd);

/**
 * @brief   This function formats the third byte for Accelarometer X-axis
 * @param   ax : Value from X-axis Accelerometer  
 * @return  Formatted 8 bit value for X-axis size only
 *          2 most LSB are address = 2
 *          Data format as described:
 *          Ax6 | Ax5 | Ax4 | Ax3 | Ax2 | Ax1 | ADDR1 | ADDR0
 * 
 *          Must transform resolution to 6 bit
 */
uint8_t format_data_b3(int16_t ax);

/**
 * @brief   This function formats the fourth byte for Accelarometer Y-axis
 * @param   ax : Value from Y-axis Accelerometer  
 * @return  Formatted 8 bit value for Y-axis size only
 *          2 most LSB are address = 3
 *          Data format as described:
 *          Ay6 | Ay5 | Ay4 | Ay3 | Ay2 | Ay1 | ADDR1 | ADDR0
 * 
 *          Must transform resolution to 6 bit
 */
uint8_t format_data_b4(int16_t ay);

#ifdef	__cplusplus
}
#endif
#endif	/* CONTROL_GLOVE_H */

