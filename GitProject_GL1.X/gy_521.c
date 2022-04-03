    
#include <xc.h>
#include <stdio.h>
#include "gy_521.h"
#include "I2C_MSSP1_driver.h"
#include "uart.h"   //for troubleshooting


void gy_init(uint8_t gyAdd){
    gy_address = gyAdd << 1;
    __delay_ms(200);
    
    //Set sampling rate to 1KHz
    I2C_Start();                    //Send start signal
    I2C_Write(gy_address);          //Write address and R/W bit cleared
    I2C_Write(SMPLRT_DIV);          //Sample Rate divider reg
    I2C_Write(0x07);                //Sample rate = gyro_output_rate/(1+ SMPLRT_DIV) for 1KHz
    I2C_Stop();
    
    //Set the clock src and disable sleep
    I2C_Start();                    //Send start signal
    I2C_Write(gy_address);          //Write address and R/W bit cleared
    I2C_Write(PWR_MGMT_1);          //Power management1 reg
    I2C_Write(0x01);                //Using X axis gyro for clock as recommended and sleep off
    I2C_Stop();
    
    //Configure Digital low pass filter reg
    I2C_Start();                    //Send start signal
    I2C_Write(gy_address);          //Write address and R/W bit cleared
    I2C_Write(CONFIG);              //Config register
    I2C_Write(0x00);                //don't use external inputs
    I2C_Stop();
    
    //Configure gyro to 2000�/s and accel to -+2g
    I2C_Start();                    //Send start signal
    I2C_Write(gy_address);          //Write address and R/W bit cleared
    I2C_Write(GYRO_CONFIG);         //Gyro config register
    I2C_Write(0x00);                //250 deg per sec (0x00), no self test (0x18 for 2000�/sec))
    I2C_Write(0x00);                //Accel config to 0x00 for +-2g
    I2C_Stop();
    
    //Set interrupts
    I2C_Start();                    //Send start signal
    I2C_Write(gy_address);          //Write address and R/W bit cleared
    I2C_Write(INT_ENABLE);          //Interrupts enable Register
    I2C_Write(0x00);                 //When data is ready disable
    I2C_Stop();
}

void gy_Read(int16_t* Ax, int16_t* Ay){
    uint8_t axl, axh, ayl, ayh;

    I2C_Start();
    I2C_Write(gy_address);          //Address in write
    I2C_Write(ACCEL_XOUT_H);        //First register to read
    
    //Reading values from the sensor and asigning to pointer
    I2C_Start();
    I2C_Write(gy_address + 0x01);   //Address in read
    axh = I2C_Read(0);
    axl = I2C_Read(0);
    ayh = I2C_Read(0);
    ayl = I2C_Read(1);
    I2C_Stop();

    *Ax = (axh << 8) | axl;
    *Ay = (ayh << 8) | ayh;

    return;
}

void gy_test(void){
    int16_t ax, ay;
    char buffer[50];

    gy_Read(&ax, &ay);

    sprintf(buffer, "AX: %d\t AY:%d \r\n", ax, ay);
    uart_Write_String(buffer);
}