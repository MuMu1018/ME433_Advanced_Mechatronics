#include <xc.h>
#include <sys/attribs.h>  // __ISR macro
#include <stdio.h>   // to use sprintf()
#include "ILI9163C.h"
#include "config.h"

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