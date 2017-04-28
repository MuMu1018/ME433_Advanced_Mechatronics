#include<xc.h>           // processor SFR definitions
#include<sys/attribs.h>  // __ISR macro
#include<math.h>

#define CS LATAbits.LATA0 // chip select pin
#define CHANNELA 0         
#define CHANNELB 1
#define PI 3.1415926535898

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

// send a byte via spi and return the response
unsigned char SPI1_IO(unsigned char ch) {
    SPI1BUF = ch;
    while(!SPI1STATbits.SPIRBF) {;} // wait to receive the byte
    return SPI1BUF;
}

// initialize SPI1
void SPI1_init() {
    // Master - SPI1, pins are: SDI1(B8), SDO1(A1), SCK1(B14).  
    // we manually control SS1 as a digital output (A0)
    RPA1Rbits.RPA1R = 0b0011; // Set SDO1 to A1
    SDI1Rbits.SDI1R = 0b0100; // Set SDI1 to B8, actually not connected to DAC
    SPI1CON = 0;              // turn off the SPI module and reset it
    SPI1BUF;                  // clear the rx buffer by reading from it
    SPI1BRG = 0x1;            // SPI1BRG = (80MHz/(2*20MHz))-1 = 1
    SPI1STATbits.SPIROV = 0;  // clear the overflow bit
    SPI1CONbits.CKE = 1;      // data changes when clock goes from HIGH to LOW (since CKP is 0)
    SPI1CONbits.MSTEN = 1;    // master operation
    SPI1CONbits.ON = 1;       // turn on SPI1
    TRISAbits.TRISA0 = 0;
}
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

int main() {
    int i;
    
    //__builtin_disable_interrupts();
    SPI1_init();
   // __builtin_enable_interrupts();
    
    while(1) {
        // use _CP0_SET_COUNT(0) and _CP0_GET_COUNT() to test the PIC timing
            // remember the core timer runs at half the sysclk
        for(i=0;i<200;i++){
            setVoltage(CHANNELA,127.5+127.5*sin((float)i*0.01*PI));
            setVoltage(CHANNELB,255*(float)i*0.005);
            _CP0_SET_COUNT(0);  // Reset the timer
            while(_CP0_GET_COUNT() < 12000){;}  // 24MHz/1kHz = 24000
        }
//        LATAINV = 0x10;     // turn off/on LED
 //       while(!PORTBbits.RB4){;} // if button is pushed, stop and wait
    }
}
