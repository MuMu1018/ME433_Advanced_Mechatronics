#include <xc.h>
#include <sys/attribs.h>  // __ISR macro
#include <stdio.h>
#include "i2c_master_noint.h"
#include "ILI9163C.h"
#include "LCD.h"
#include "config.h"

#define IMU_ADDR 0b1101011
#define STRINGLENGTH 100

//initialize I/O expander
void initIMU(){
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

void initPIC(){
    TRISAbits.TRISA4 = 0; // set LED an output pin
    TRISBbits.TRISB4 = 1; // set push button an input pin
    LATAbits.LATA4 = 0; // turn LED off
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

int main() {
    unsigned char data[STRINGLENGTH];
    int i;
    
  __builtin_disable_interrupts();
  
  initIMU();
  initPIC();
  SPI1_init();
  LCD_init();
  LCD_clearScreen(BACKGROUND);

  __builtin_enable_interrupts();
  
  while(1) {
        _CP0_SET_COUNT(0);
        while (_CP0_GET_COUNT()<1200000) {;}
		/*
         * I2C_read_multiple(0x6a, 0x20, data, 14);
         * for(i=0; i<7; i++){
         * data_combine[i] = data[2*i+1]<<8 | data[2*i];
         * }
         */
  }
  return 0;
}
