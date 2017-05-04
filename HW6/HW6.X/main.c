#include <xc.h>
#include <sys/attribs.h>  // __ISR macro
#include <stdio.h>   // to use sprintf()
#include "ILI9163C.h"

// DEVCFG0
#pragma config DEBUG = 0b10 // no debugging
#pragma config JTAGEN = 0 // no jtag
#pragma config ICESEL = 0b11 // use PGED1 and PGEC1
#pragma config PWP = OFF // no write protect
#pragma config BWP = 1 // no boot write protect
#pragma config CP = 1 // no code protect

// DEVCFG1
#pragma config FNOSC = 0b011 // use primary oscillator with pll
#pragma config FSOSCEN = 0 // turn off secondary oscillator
#pragma config IESO = 0 // no switching clocks
#pragma config POSCMOD = 0b10 // high speed crystal mode
#pragma config OSCIOFNC = 1 // disable secondary osc
#pragma config FPBDIV = 0b00 // divide sysclk freq by 1 for peripheral bus clock
#pragma config FCKSM = 0b11 // do not enable clock switch
#pragma config WDTPS = 0b10100 // use slowest wdt
#pragma config WINDIS = 1 // wdt no window mode
#pragma config FWDTEN = 0 // wdt disabled
#pragma config FWDTWINSZ = 0b11 // wdt window at 25%

// DEVCFG2 - get the sysclk clock to 48MHz from the 8MHz crystal
#pragma config FPLLIDIV = 1 // divide input clock to be in range 4-5MHz
#pragma config FPLLMUL = 0b111 // multiply clock after FPLLIDIV
#pragma config FPLLODIV = 1 // divide clock after FPLLMUL to get 48MHz
#pragma config UPLLIDIV = 1 // divider for the 8MHz input clock, then multiplied by 12 to get 48MHz for USB
#pragma config UPLLEN = 0 // USB clock on

// DEVCFG3
#pragma config USERID = 0 // some 16bit userid, doesn't matter what
#pragma config PMDL1WAY = 0 // allow multiple reconfigurations
#pragma config IOL1WAY = 0 // allow multiple reconfigurations
#pragma config FUSBIDIO = 1 // USB pins controlled by USB module
#pragma config FVBUSONIO = 1 // USB BUSON controlled by USB module

#define CS LATBbits.LATB7  // SPI chip select pin
#define STRINGLENGTH 100

int main() {
    
  char str1[STRINGLENGTH],str2[STRINGLENGTH];
  int timer=10;
  float FPS=0.0;
  // some initialization function to set the right speed setting
  __builtin_disable_interrupts();
  
  SPI1_init();
  LCD_init();
  LCD_clearScreen(BACKGROUND);

  __builtin_enable_interrupts();
  while(1) {
      for (timer=0;timer<=100;timer++){
            _CP0_SET_COUNT(0);
            sprintf(str1,"Hello World %d!  ",timer);
            LCD_drawString(28,32,str1,BLUE); //String
            LCD_drawBar(20,48,timer,RED);    //Bar
            FPS = 24000000/_CP0_GET_COUNT(); //FPS
            sprintf(str2,"FPS: %1.1f",FPS);
            LCD_drawString(28,80,str2,BLUE);
            while(_CP0_GET_COUNT() < 4800000){;} // 24MHz/5Hz = 4800000
      }
      //LCD_clearScreen(BACKGROUND);
  }
  return 0;
}