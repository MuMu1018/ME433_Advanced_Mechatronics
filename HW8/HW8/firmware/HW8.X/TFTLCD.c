#include <xc.h>
#include <math.h>
#include "TFTLCD.h"
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
 
void LCD_drawGravCross(float Gx, float Gy, unsigned short color){
    int i,j;
    char xlength = abs(Gx * CROSSLENGTH);
    char ylength = abs(Gy * CROSSLENGTH);
    if (Gx>0){
        for (i=0;i<xlength;i++){
            for(j=0;j<2;j++){
                LCD_drawPixel(64+i,64+j,color);
            }
        }
        if (xlength < CROSSLENGTH){
            for (i=xlength;i<CROSSLENGTH;i++){
                for(j=0;j<2;j++){
                    LCD_drawPixel(64+i,64+j,BACKGROUND);
                }
            }
        }
        for (i=1;i<CROSSLENGTH;i++){
            for(j=0;j<2;j++){
                LCD_drawPixel(64-i,64+j,BACKGROUND);
            }
        }    
    }
    else{
        for (i=0;i<xlength;i++){
            for(j=0;j<2;j++){
                LCD_drawPixel(64-i,64+j,color);
            }
        }
        if (xlength < CROSSLENGTH){
            for (i=xlength;i<CROSSLENGTH;i++){
                for(j=0;j<2;j++){
                    LCD_drawPixel(64-i,64+j,BACKGROUND);
                }
            }
        }
        for (i=1;i<CROSSLENGTH;i++){
            for(j=0;j<2;j++){
                LCD_drawPixel(64+i,64+j,BACKGROUND);
            }
        } 
    }
    if (Gy>0){
        for (i=0;i<ylength;i++){
            for(j=0;j<2;j++){
                LCD_drawPixel(64+j,64+i,color);
            }
        }
        if (ylength < CROSSLENGTH){
            for (i=ylength;i<CROSSLENGTH;i++){
                for(j=0;j<2;j++){
                    LCD_drawPixel(64+j,64+i,BACKGROUND);
                }
            }
        }
        for (i=1;i<CROSSLENGTH;i++){
            for(j=0;j<2;j++){
                LCD_drawPixel(64+j,64-i,BACKGROUND);
            }
        }
    }
    else{
        for (i=0;i<ylength;i++){
            for(j=0;j<2;j++){
                LCD_drawPixel(64+j,64-i,color);
            }
        }
        if (ylength < CROSSLENGTH){
            for (i=ylength;i<CROSSLENGTH;i++){
                for(j=0;j<2;j++){
                    LCD_drawPixel(64+j,64-i,BACKGROUND);
                }
            }
        }
        for (i=1;i<CROSSLENGTH;i++){
            for(j=0;j<2;j++){
                LCD_drawPixel(64+j,64+i,BACKGROUND);
            }
        }
    }
    
}
