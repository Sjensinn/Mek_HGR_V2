/* 
 * File:   adc.h
 *
 */



#ifndef ADC_H
#define ADC_H

#ifdef __cplusplus

extern "C"



#include <xc.h>

/*
 * @brief   This function gets adc input from the address bank *          
 * 	Refer to datasheet for intial procedure 
 * @param   10 bit address bank          
 * @return  void
 *
 */
void flexSensor(void);

/**
 * @brief   This function sets the ADCON registers
 *          Refer to datasheet for intial procedure 
 * @param   8 bit ADCON address          
 * @return  void
 *
 */
void adcon_setup(void);

/**
 * @brief   This function sets the ADCLK registers
 *          Refer to datasheet for intial procedure 
 * @param   8 bit ADCLK address          
 * @return  void
 *
 */
void adclk_setup(void);

/**
 * @brief   This function sets the select analog input.
 *          Refer to datasheet for intial procedure 
 * @param   8 bit ANSEL address          
 * @return  void
 *
 */
void ansel_setup(void);

/**
 * @brief   This function sets the Analog reference voltage
 *          Refer to datasheet for intial procedure 
 * @param          
 * @return  void
 *
 */
void adref_setup(void);

/**
 * @brief   This function sets the ADC positive channel selection register
 *          Refer to datasheet for intial procedure 
 * @param   8 bit ADPCH register          
 * @return  void
 *
 */
void adpch_setup(void);


#ifdef	__cplusplus
}
#endif

#endif	/* ADC_H */


