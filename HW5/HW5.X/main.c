#include <xc.h>
#include "i2c_master_noint.h"
#include <sys/attribs.h>  // __ISR macro

// DEVCFG0
#pragma config DEBUG = 0b10 // no debugging
#pragma config JTAGEN = 0 // no jtag
#pragma config ICESEL = 0b11 // use PGED1 and PGEC1
#pragma config PWP = 0x1FF // no write protect
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
#pragma config WDTPS = 0 // use slowest wdt
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

#define SLAVE_ADDR 0x20

//initialize I/O expander
void initExpander(){
    ANSELBbits.ANSB2 = 0;
    ANSELBbits.ANSB3 = 0;
    i2c_master_setup();
    i2c_master_start();
    i2c_master_send(SLAVE_ADDR<<1); // R/W = 0 = write
    i2c_master_send(0x00); // 0x00 = IODIR
    i2c_master_send(0xF0); // Initialize GP0-3 outputs(off), GP4-7 inputs
    i2c_master_stop();
}

void setExpander(char pin, char level){
    i2c_master_start();
    i2c_master_send(SLAVE_ADDR<<1); // R/W = 0 = write
    i2c_master_send(0x0A); // 0x0A = OLAT
    i2c_master_send(level<<pin); // set pin high/low
    i2c_master_stop();
}

char getExpander(){
    char level;
    i2c_master_start();
    i2c_master_send(SLAVE_ADDR<<1); // R/W = 0 = write
    i2c_master_send(0x09); // 0x09 = GPIO
    i2c_master_restart(); 
    i2c_master_send((SLAVE_ADDR<<1)|1); // R/W = 0 = write
    level = i2c_master_recv(); // receive a byte from GP7
    i2c_master_ack(1); // send NACK to slave
    i2c_master_stop();
    return level;
}


int main() {
  // some initialization function to set the right speed setting
  __builtin_disable_interrupts();
  
  TRISAbits.TRISA4 = 0; // set LED an output pin
  TRISBbits.TRISB4 = 1; // set push button an input pin
  LATAbits.LATA4 = 1; // turn LED off
  initExpander();
  
  __builtin_enable_interrupts();
  
  while(1) {
      char level = getExpander()>>7;
      setExpander(0,level);
  }
  return 0;
}