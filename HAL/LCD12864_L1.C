/*
****************************************************
*  File name          : LCD12864_L1.C
*  Author             : 5A4A5943
*  Version            : V0.0.1
*  Date               : 2016--08--23--16--00--09
*  Description        : 一级封装
*  Function List      : 
*  History            : 
*****************************************************
*/

#include "LCD12864.h"


/*
****************************************************
*  Function       : LCD12864_DisplayxHxWString
*  Description    : 显示任意宽和高的汉字字符串
*  Calls          : 
*  Called By      : 
*  Input          : Str:字符串 x：起始 y：起始
*  Output         : 
*  Return         : 
*  Others         : 当前不能辨别汉字与ASC
*****************************************************
*/
void LCD12864_DisplayxHxWString(uint8_t * Str,uint8_t H,uint8_t W,uint8_t x,uint8_t y,uint8_t Set)
{
	uint8_t Char[2] = {0},x_Start = x,y_Start = y;
	uint32_t Index = 0,Size = 0;
	do
	{
		if(Str[0] > 128)
		{
			Char[0] = Str[0];
			Char[1] = Str[1];
			
			Size = FontSearch(Char,&Index,0x00,H,W,Array);
			
			if(Size != 0x00)
			{
				LCD12864_Graphic(x_Start,x_Start + H - 1,y_Start,y_Start + W - 1,(uint8_t *)Index,Set);
			}
			
			Str += 2;
			y_Start += W;
		}
		else
		{
			Char[0] = Str[0];
			
			Size = FontSearch(Char,&Index,0x00,H,W,Array);
			
			if(Size != 0x00)
			{
				LCD12864_Graphic(x_Start,x_Start + H - 1,y_Start,y_Start + W - 1,(uint8_t *)Index,Set);
			}
			Str += 1;
			y_Start += W;
		}
	}while(*Str != 0x00);
}
/*
****************************************************
*  Function       : LCD12864_DisplayHanZi3232WString
*  Description    : 
*  Calls          : 
*  Called By      : 
*  Input          : 
*  Output         : 
*  Return         : 
*  Others         : 
*****************************************************
*/
void LCD12864_DisplayHanZi3232String(uint8_t * Str,uint8_t x,uint8_t y,uint8_t Set)
{
	LCD12864_DisplayxHxWString(Str,32,32,x,y,Set);
}
/*
****************************************************
*  Function       : LCD12864_DisplayHanZi1616WString
*  Description    : 
*  Calls          : 
*  Called By      : 
*  Input          : 
*  Output         : 
*  Return         : 
*  Others         : 
*****************************************************
*/
void LCD12864_DisplayHanZi1616String(uint8_t * Str,uint8_t x,uint8_t y,uint8_t Set)
{
	LCD12864_DisplayxHxWString(Str,16,16,x,y,Set);
}
void LCD12864_DisplayASC2448String(uint8_t * Str,uint8_t x,uint8_t y,uint8_t Set)
{
	LCD12864_DisplayxHxWString(Str,48,24,x,y,Set);
}
void LCD12864_DisplayASC0816String(uint8_t * Str,uint8_t x,uint8_t y,uint8_t Set)
{
	LCD12864_DisplayxHxWString(Str,16,8,x,y,Set);
}

void LCD12864_DisplayxHxWPic(uint8_t ID,uint8_t x,uint8_t y,uint8_t Set)
{
	uint32_t Index = 0x00;
	uint8_t H = 0,W = 0;
	PicSearch(ID,&H,&W,&Index);
	LCD12864_Graphic(x,x + H - 1,y,y + W - 1,(uint8_t *)Index,Set);
}















