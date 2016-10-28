/*
****************************************************
*  File name          : Font.h
*  Author             : 5A4A5943
*  Version            : V0.0.1
*  Date               : 
*  Description        : 
*  Function List      : 
*  History            : 
*****************************************************
*/
#ifndef __FONT_H__
#define __FONT_H__

#include "LCD12864.h"

#if 1 //32*32
typedef struct typFNT_GB32_  
{
    uint8_t Index[3];  
    uint8_t Msk[128]; 
}typFNT_GB32;
#endif
#if	1//16*16
typedef struct typFNT_GB16_    
{
    uint8_t Index[3];   
    uint8_t   Msk[32];  
}typFNT_GB16;
#endif
#if	1//08*16
typedef struct typFNT_ASC0816_    
{
    uint8_t Index[2];   
    uint8_t   Msk[16];  
}typFNT_ASC0816;
#endif
#if 1//24*48

typedef struct typFNT_ASC2448_    
{
    uint8_t   Index[2];   
    uint8_t   Msk[144];  
}typFNT_ASC_2448;

#endif
#if	1//点阵图片
typedef struct Pic_xHxW_
{
	uint8_t ID;
	uint8_t H;
	uint8_t W;
	uint8_t * Msk;
}Pic_xHxW;

#endif

uint32_t GetFont3232(uint8_t * Char,uint32_t * Index,uint8_t * Buff,FontType_ Type);
uint32_t GetFont1616(uint8_t * Char,uint32_t * Index,uint8_t * Buff,FontType_ Type);
uint32_t GetFontASC2448(uint8_t * Char,uint32_t * Index,uint8_t * Buff,FontType_ Type);
uint32_t GetFontASC0816(uint8_t * Char,uint32_t * Index,uint8_t * Buff,FontType_ Type);
uint32_t GetFontPic(uint8_t * Char,uint32_t * Index,uint8_t * Buff,FontType_ Type);

#endif




