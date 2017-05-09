#include <xc.h>
#include "LSM6DS333.h"

//initialize I/O expander
void LSM6DS333_init(){
    ANSELBbits.ANSB2 = 0;
    ANSELBbits.ANSB3 = 0;
    i2c_master_setup();
    
    // Initialize accelerometer
    i2c_master_start();
    i2c_master_send(IMU_ADDR<<1);   // R/W = 0 = write
    i2c_master_send(0x10);  // 0x10 = CTRL1_XL
    i2c_master_send(0x82);  // ODR_XL = 0b1000 (1.66kHz)
                            // FS_XL = 0b00 (2g), BW_XL = 0b10 (100Hz)
    i2c_master_stop();
    
    // Initialize gyroscope
    i2c_master_start();
    i2c_master_send(IMU_ADDR<<1);   // R/W = 0 = write
    i2c_master_send(0x11);  // 0x11 = CTRL2_G
    i2c_master_send(0x88);  // ODR_G = 0b1000 (1.66kHz), FS_G = 0b10 (1000dps)
                            // FS_125 = 0 (disabled), bit 0 = 0 (must set 0)
    i2c_master_stop();
    
    // Initialize 
    i2c_master_start();
    i2c_master_send(IMU_ADDR<<1);   // R/W = 0 = write
    i2c_master_send(0x12);  // 0x12 = CTRL3_C
    i2c_master_send(0x04);  // default = 0x04, IF_INC = 1(default)
    i2c_master_stop();
}

void I2C_read_multiple(unsigned char address, unsigned char regis, unsigned char * data, int length){
    char i;
    i2c_master_start();
    i2c_master_send(address<<1);   // R/W = 0 = write
    i2c_master_send(regis);  // 0x20 = OUT_TEMP_L
    i2c_master_restart(); 
    i2c_master_send((address<<1)|1); // R/W = 1 = read
    for(i=0;i<length;i++){
        data[i] = i2c_master_recv(); // receive a byte from GP7
        if(i!=(length-1))
            i2c_master_ack(0);
    }
    i2c_master_ack(1); // send NACK to slave
    i2c_master_stop();
}

float getxXL(unsigned char * data) { // convert x-acceleration 
    signed short x = data[9]<<8 | data[8];
    return x*(2.0/32757.0);
}

float getyXL(unsigned char * data) { // convert y-acceleration 
    signed short y = data[11]<<8 | data[10];
    return y*(2.0/32757.0);
}
