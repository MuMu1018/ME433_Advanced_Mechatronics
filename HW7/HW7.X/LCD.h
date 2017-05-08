#ifndef LCD_H__
#define LCD_H__

#define BACKGROUND 0x0000 // BLACK
#define BARLENGTH 100

void LCD_drawCharacter(unsigned short, unsigned short, char, unsigned short);
void LCD_drawString(unsigned short, unsigned short, char*, unsigned short);
void LCD_drawBar(unsigned short, unsigned short, char, unsigned short);

#endif