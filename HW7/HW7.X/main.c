#include <xc.h>
#include <sys/attribs.h>  // __ISR macro
#include <stdio.h>
#include "config.h"
#include "i2c_master_noint.h"
#include "ILI9163C.h"
#include "TFTLCD.h"
#include "LSM6DS333.h"

#define STRINGLENGTH 100

int main() {
    unsigned char dataReg8[STRINGLENGTH];
    // short dataReg16[STRINGLENGTH];
    char str1[STRINGLENGTH];
    int i;
    float Gx,Gy;
    
    __builtin_disable_interrupts();

    TRISAbits.TRISA4 = 0; // set LED an output pin
    TRISBbits.TRISB4 = 1; // set push button an input pin
    LATAbits.LATA4 = 0; // turn LED off
    LSM6DS333_init();
    SPI1_init();
    LCD_init();
    LCD_clearScreen(BACKGROUND);

    __builtin_enable_interrupts();

    while(1) {
        _CP0_SET_COUNT(0);
        while (_CP0_GET_COUNT()<1200000) {;}
        I2C_read_multiple(IMU_ADDR, 0x20, dataReg8, 14);
        Gx = getxXL(dataReg8);
        Gy = getyXL(dataReg8);
        /*
        sprintf(str1,"Gx = %1.3f!",Gx);
        LCD_drawString(10,10,str1,BLUE); //String
        sprintf(str1,"Gy = %1.3f!",Gy);
        LCD_drawString(10,20,str1,BLUE); //String
        */
        LCD_drawGravCross(Gx,Gy,WHITE);
    }
    return 0;
}
