/*
****************************************************
*  File name          : LCD12864_Port1.c
*  Author             : 5A4A5943
*  Version            : V0.0.1
*  Date               : 
*  Description        : 
*  Function List      : 
*  History            : 
*****************************************************
*/
#include "LCD12864_L1.H"

/*
****************************************************
*  Function       : DisplayMess
*  Description    : 显示一段汉字
*  Calls          : 
*  Called By      : 
*  Input          : 
*  Output         : 
*  Return         : 
*  Others         : 个人理解不同，目前Length没有用到
*****************************************************
*/
void DisplayMess(uint8_t sit, uint8_t *p, uint8_t lenth)
{
	uint8_t x = sit + 1,y = 1;
	uint8_t Hanzi[2] = {0x00};
	while(*p != 0x00)
	{
		if(*p > 128)
		{
			Hanzi[0] = p[0];
			Hanzi[1] = p[1];
			LCD12864_DisplayHanZi1616String(Hanzi,x,y,LCD12864_SET | LCD12864_NORMAL);
			p += 2;
			y += 16;
		}
		else
		{
			Hanzi[0] = p[0];
			LCD12864_DisplayASC0816String(Hanzi,x,y,LCD12864_SET | LCD12864_NORMAL);
			p += 1;
			y += 8;
		}
		if(y > 128){y = 0;x += 16;}//换行
	}
}
/*
****************************************************
*  Function       : ClrDisplay
*  Description    : 清屏函数
*  Calls          : 
*  Called By      : 
*  Input          : 
*  Output         : 
*  Return         : 
*  Others         : 
*****************************************************
*/
void ClrDisplay(void)
{
	LCD12864_ClearScreen(0x00);
}
/*
****************************************************
*  Function       : 
*  Description    : 
*  Calls          : 
*  Called By      : 
*  Input          : 
*  Output         : 
*  Return         : 
*  Others         : 
*****************************************************
*/
void ClrRAMDisplay(void)
{
	LCD12864_ClearScreen(0x00);
}
/*
****************************************************
*  Function       : 
*  Description    : 
*  Calls          : 
*  Called By      : 
*  Input          : 
*  Output         : 
*  Return         : 
*  Others         : 
*****************************************************
*/
void DisplayNum(uint8_t x, uint8_t y,uint8_t *num)
{
	LCD12864_DisplayASC0816String(num,x,y,LCD12864_SET | LCD12864_NORMAL);
}
/*
****************************************************
*  Function       : 
*  Description    : 
*  Calls          : 
*  Called By      : 
*  Input          : 
*  Output         : 
*  Return         : 
*  Others         : 第一列64*8
*****************************************************
*/
void ClrFirstList(void)
{
	uint8_t Buff[64] = {0x00};
	LCD12864_Graphic(1,64,1,16,Buff,LCD12864_CLR | LCD12864_NORMAL);
}
/*
****************************************************
*  Function       : 
*  Description    : 
*  Calls          : 
*  Called By      : 
*  Input          : 
*  Output         : 
*  Return         : 
*  Others         : 
*****************************************************
*/
void dzDisplayPicture2(uint8_t x, uint8_t y, uint8_t img)
{
	//uint8_t ID = img;
	//uint32_t Temp = (uint32_t)img;
	//switch(Temp)
	//{
	//	case 0x00:{ID = 0;break;}
	//	default:break;
	//}
	LCD12864_DisplayxHxWPic(img,x,y,LCD12864_SET | LCD12864_NORMAL);
}









