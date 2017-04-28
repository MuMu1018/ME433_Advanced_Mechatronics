#ifndef SPI1__H__
#define SPI1__H__

#include <xc.h>           // processor SFR definitions
#include <sys/attribs.h>  // __ISR macro

#define CS LATAbits.LATA0 // chip select pin
#define CHANNELA 0         
#define CHANNELB 1
#define PI 3.1415926535898

unsigned char SPI1_IO(unsigned char ch); // send a byte via spi and return the response
void SPI1_init(); // initialize SPI1
void setVoltage(char channel, unsigned char voltage); // set channel and voltage
    
#endif