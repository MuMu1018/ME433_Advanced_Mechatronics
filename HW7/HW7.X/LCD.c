#include <xc.h>
#include "LCD.h"
#include "ILI9163C.h"
void LCD_drawCharacter(unsigned short x, unsigned short y, char ch, unsigned short color){
    int i,j;
    if ((x<_GRAMWIDTH-5)&&(y<_GRAMHEIGH-8)){
        for (i=0;i<5;i++){
            for(j=0;j<8;j++){
                if(((ASCII[ch-0x20][i])>>j)&(0x01))
                    LCD_drawPixel(x+i,y+j,color);
                else
                    LCD_drawPixel(x+i,y+j,BACKGROUND); 
            }
        }
    }
}

void LCD_drawString(unsigned short x, unsigned short y, char ch[], unsigned short color){
    int i=0,k=0;
    while(1){
        if (ch[i] == '\0')
            break;
        LCD_drawCharacter(x+k,y,ch[i],color);
        i++;
        k+=6;
    }
}

void LCD_drawBar(unsigned short x, unsigned short y, char length, unsigned short color){
    int i,j;
    for (i=0;i<length;i++){
        for(j=0;j<2;j++){
            LCD_drawPixel(x+i,y+j,color);
        }
    }
    if (length < BARLENGTH){
        for (i=length;i<BARLENGTH;i++){
            for(j=0;j<2;j++){
                LCD_drawPixel(x+i,y+j,BACKGROUND);
            }
        }
    }
}
 
