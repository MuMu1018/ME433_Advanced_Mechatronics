#include "SPI1.h"


//where channel is 0 or 1 (for VoutA and VoutB), and voltage is the 8-bit output level.
void setVoltage(char channel, unsigned char voltage){
    unsigned char LSB,MSB;
    
    LSB = voltage << 4;               
    MSB = channel << 7;
    MSB |= 0b01110000;
    MSB |= voltage >> 4;  
    CS = 0;                        // enable SPI1 by set chip select line low
    SPI1_IO(MSB);
    SPI1_IO(LSB);      
    CS = 1;                        // raise the chip select line, ending communication
}
