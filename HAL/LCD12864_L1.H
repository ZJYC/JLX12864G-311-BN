
#ifndef __LCD12864_L1_H__
#define __LCD12864_L1_H__

#include "LCD12864.h"

void LCD12864_DisplayxHxWString(uint8_t * Str,uint8_t H,uint8_t W,uint8_t x,uint8_t y,uint8_t Set);
void LCD12864_DisplayHanZi3232String(uint8_t * Str,uint8_t x,uint8_t y,uint8_t Set);
void LCD12864_DisplayHanZi1616String(uint8_t * Str,uint8_t x,uint8_t y,uint8_t Set);
void LCD12864_DisplayASC2448String(uint8_t * Str,uint8_t x,uint8_t y,uint8_t Set);
void LCD12864_DisplayASC0816String(uint8_t * Str,uint8_t x,uint8_t y,uint8_t Set);
void LCD12864_DisplayxHxWPic(uint8_t ID,uint8_t x,uint8_t y,uint8_t Set);

#endif




































