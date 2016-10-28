
#include "LCD12864_Port1.h"

void Test(void)
{
	//HAL_Delay
	
	LCD12864_Init();HAL_Delay(500);
	LCD12864_ClearScreen(0x55); HAL_Delay(500);
	LCD12864_ClearScreen(0x00);
	
	LCD12864_DisplayHanZi3232String("神思电子",1,1,LCD12864_SET | LCD12864_NORMAL);  HAL_Delay(500);
	LCD12864_DisplayHanZi3232String("神思电子",1,1,LCD12864_CLR | LCD12864_NORMAL);
	LCD12864_DisplayHanZi3232String("神思电子",13,1,LCD12864_SET | LCD12864_NORMAL);  HAL_Delay(500);
	LCD12864_DisplayHanZi3232String("神思电子",13,1,LCD12864_CLR | LCD12864_NORMAL);
	LCD12864_DisplayHanZi3232String("神思电子",23,1,LCD12864_SET | LCD12864_NORMAL);  HAL_Delay(500);
	LCD12864_DisplayHanZi3232String("神思电子",23,1,LCD12864_CLR | LCD12864_NORMAL);
	LCD12864_DisplayHanZi3232String("神思电子",30,1,LCD12864_SET | LCD12864_NORMAL);  HAL_Delay(500);
	LCD12864_DisplayHanZi3232String("神思电子",30,1,LCD12864_CLR | LCD12864_NORMAL);
	LCD12864_DisplayHanZi3232String("神思电子",23,1,LCD12864_SET | LCD12864_NORMAL);  HAL_Delay(500);
	LCD12864_DisplayHanZi3232String("神思电子",23,1,LCD12864_CLR | LCD12864_NORMAL);
	
	LCD12864_ClearScreen(0x00);
	
	LCD12864_DisplayHanZi1616String("消费成功",12,46,LCD12864_SET | LCD12864_NORMAL); HAL_Delay(500);
	//LCD12864_DisplayHanZi3232String("神思电子",1,1,LCD12864_SET | LCD12864_NORMAL);
	LCD12864_ClearScreen(0x00);
	
	LCD12864_DisplayASC2448String("123.",23,30,LCD12864_SET | LCD12864_NORMAL);HAL_Delay(500);
	
	LCD12864_ClearScreen(0x00);
	
	/**************************************************************************************/
	
	DisplayMess(0,"消费ABCD一卡通",0);HAL_Delay(500);
	
	ClrDisplay();
	
	DisplayNum(35,1,"ABCD1234"); HAL_Delay(500);
	
	ClrDisplay();
	
	dzDisplayPicture2(1,1,0); HAL_Delay(500);ClrDisplay();
	dzDisplayPicture2(1,1,1); HAL_Delay(500);ClrDisplay();
	dzDisplayPicture2(1,1,2); HAL_Delay(500);ClrDisplay();
	dzDisplayPicture2(1,1,3); HAL_Delay(500);ClrDisplay();
	dzDisplayPicture2(1,1,4); HAL_Delay(500);ClrDisplay();
	dzDisplayPicture2(1,1,5); HAL_Delay(500);ClrDisplay();
	dzDisplayPicture2(1,1,5); HAL_Delay(500); ClrFirstList();
	dzDisplayPicture2(17,1,5);HAL_Delay(500); ClrFirstList();
	dzDisplayPicture2(33,1,5);HAL_Delay(500); ClrFirstList();
	dzDisplayPicture2(49,1,5);HAL_Delay(500); ClrFirstList();
	
	LCD12864_ClearScreen(0xFF);HAL_Delay(500);ClrFirstList();
	ClrDisplay();
	{
		uint8_t x = 1,y = 0;
		while(1)
		{
			x++;if(x >= 48)x = 1;
			dzDisplayPicture2(x,1,5);
			if(x % 10 == 0)
			{
				y ++;if(y >= 5)y = 0;
				dzDisplayPicture2(1,112,y);
			}
			HAL_Delay(150);
			ClrDisplay();
		}
	}
	
	/**************************************************************************************/
	
	while(1);
}



