
#include "LCD12864.h"
/*
****************************************************
*  File name          : LCD12864.c
*  Author             : 5A4A5943
*  Version            : V1.0
*  Date               : 
*  Description        : This file is a implement of Harderware init and Basic memory operation.
*  Function List      : 
						void LCD12864_Init(void)
						void LCD12864_ClearScreen(uint8_t Data)
						void LCD12864_TestDisplay(uint8_t Data1,uint8_t Data2)
						void LCD12864_Graphic(uint16_t X_Start,uint16_t X_End,uint16_t Y_Start,uint16_t Y_End,uint8_t * Buff)
						uint8_t LCD12864RamWrite(uint16_t X_Start,uint16_t X_End,uint16_t Y_Start,uint16_t Y_End,uint8_t * Buff)
						uint8_t LCD12864Sync(void)
						uint8_t LCD12864SetPixel(uint8_t x,uint8_t y,uint8_t color)
*  History            : 
						2016--08--22--11--04--29：
						添加画点函数LCD12864SetPixel并测试成功
						
*****************************************************
*/
#include <Ctype.h>
#include "LCD12864.h"

void LCD12864_Delay(uint8_t i);

extern FONT_MANAGE FontManage3232;
extern FONT_MANAGE FontManage1616;
extern FONT_MANAGE FontManage2448;
extern FONT_MANAGE FontManage0816;
extern FONT_MANAGE FontManagePic;
JLX12864G_	JLX12864G = {0x00};
FONT_MANAGE	FontManage = {0x00,0x00,100,100,0x00};

/*
****************************************************
*  Function       : LinkAdd
*  Description    : 添加链表
*  Calls          : 
*  Called By      : 
*  Input          : Head：链表头  Added：新加元素
*  Output         : 
*  Return         : 失败返回非 0 值
*  Others         : 
*****************************************************
*/
uint8_t LinkAdd(pFONT_MANAGE Head,pFONT_MANAGE Added)
{
	pFONT_MANAGE Temp = Head;
	uint8_t Cnt = 0;
	
	while(Temp->NEXT != 0x00 && Cnt++ < 128)Temp = Temp->NEXT;
	
	if(Cnt < 128)
	{
		Temp->NEXT = Added;
		return 0x00;
	}
	return Cnt;
}
/*
****************************************************
*  Function       : FontInit
*  Description    : 字库初始化
*  Calls          : 
*  Called By      : 
*  Input          : 
*  Output         : 
*  Return         : 
*  Others         : 
*****************************************************
*/
uint8_t FontInit(void)
{
	memset((uint8_t *) &FontManage,0,sizeof(FONT_MANAGE));
	LinkAdd(&FontManage,&FontManage3232);
	LinkAdd(&FontManage,&FontManage1616);
	LinkAdd(&FontManage,&FontManage2448);
	LinkAdd(&FontManage,&FontManage0816);
	LinkAdd(&FontManage,&FontManagePic);
}
/*
****************************************************
*  Function       : FontSearch
*  Description    : 字模搜索
*  Calls          : 
*  Called By      : 
*  Input          : 
*  Output         : 
*  Return         : 
*  Others         : 
*****************************************************
*/
uint32_t FontSearch(
						uint8_t * Char,
						uint32_t * Index,
						uint8_t * Buff,
						uint8_t H,
						uint8_t W,
						FontType_ Type
					)
{
	pFONT_MANAGE Temp = &FontManage;
	uint32_t Size = 0;
	research:
	{
		if(Temp->H == H && Temp->W == W)
		{
			Size = Temp->GetFont(Char,Index,Buff,Type);
			if(Size != 0x00)return Size;
		}
	}
	if(Temp->NEXT != 0x00)
	{
		Temp = Temp->NEXT;
		goto research;
	}
	return 0x00;
}

/*
****************************************************
*  Function       : LCD12864LLInit
*  Description    : 底层初始化
*  Calls          : 
*  Called By      : 
*  Input          : 
*  Output         : 
*  Return         : 
*  Others         : 
*****************************************************
*/
uint8_t LCD12864LLInit(void)
{
	MX_GPIO_Init();
}

/*
****************************************************
*  Function       : LCD12864_Command
*  Description    : 向LCD发送命令
*  Calls          : 
*  Called By      : 
*  Input          : Data:
*  Output         : 
*  Return         : 
*  Others         : 
*****************************************************
*/
void LCD12864_Command(uint8_t Data)
{
	LCD12864_CS(LOW);
	LCD12864_RS(LOW);
	LCD12864_RD(LOW);
	LCD12864_WR(LOW);
	LCD12864_DATA(Data);
	LCD12864_RD(HIGH);
	LCD12864_CS(HIGH);
	LCD12864_RD(LOW);
}
/*
****************************************************
*  Function       : LCD12864_Data
*  Description    : 向LCD发送数据
*  Calls          : 
*  Called By      : 
*  Input          : Data:
*  Output         : 
*  Return         : 
*  Others         : 
*****************************************************
*/
void LCD12864_Data(uint8_t Data)
{
	LCD12864_CS(LOW);
	LCD12864_RS(HIGH);
	LCD12864_RD(LOW);
	LCD12864_WR(LOW);
	LCD12864_DATA(Data);
	LCD12864_RD(HIGH);
	LCD12864_CS(HIGH);
	LCD12864_RD(LOW);
}
/*
****************************************************
*  Function       : LCD12864_Delay
*  Description    : 简单延迟函数，延迟精度未知
*  Calls          : 
*  Called By      : 
*  Input          : 
*  Output         : 
*  Return         : 
*  Others         : 
*****************************************************
*/
void LCD12864_Delay(uint8_t cnt)
{
	while(cnt --);
}

/*
****************************************************
*  Function       : LCD12864_Init
*  Description    : 初始化LCD
*  Calls          : 
*  Called By      : 
*  Input          : 
*  Output         : 
*  Return         : 
*  Others         : 
*****************************************************
*/
void LCD12864_Init(void)
{
	LCD12864LLInit();
	FontInit();
	
	LCD12864_CS(LOW);
	
	/*低电平复位*/
	LCD12864_RES(LOW); 
	LCD12864_Delay(20);
	 /*复位完毕*/
	LCD12864_RES(HIGH);
	
	LCD12864_Delay(20);
	/*软复位*/
	LCD12864_Command(0xe2); 
	LCD12864_Delay(50);
	/*升压步聚 1*/
	LCD12864_Command(0x2c); 
	LCD12864_Delay(50);
	/*升压步聚 2*/
	LCD12864_Command(0x2e); 
	LCD12864_Delay(50);
	/*升压步聚 3*/
	LCD12864_Command(0x2f); 
	LCD12864_Delay(50);
	/*粗调对比度，可设置范围 0x20～0x27*/
	LCD12864_Command(0x24); 
	/*微调对比度*/
	LCD12864_Command(0x81); 
	/*0x1a,微调对比度的值，可设置范围 0x00～0x3f 1f*/
	LCD12864_Command(0x1a); 
	/*1/9 偏压比（bias）*/
	LCD12864_Command(0xa2);
	/*行扫描顺序：从上到下*/	
	LCD12864_Command(0xc0); 
	/*列扫描顺序：从左到右*/
	LCD12864_Command(0xa1); 
	/*起始行：第一行开始*/
	LCD12864_Command(0x40);
	/* 清空显示 */
	LCD12864_ClearScreen(0x00);
	/*开显示*/	
	LCD12864_Command(0xaf); 
	
	LCD12864_CS(HIGH);
}
/*
****************************************************
*  Function       : LCD12864_Addr
*  Description    : 设定地址
*  Calls          : 
*  Called By      : 
*  Input          : 
						page(1~8):页地址
						column(1~128)
*  Output         : 
*  Return         : 
*  Others         : 
*****************************************************
*/
void LCD12864_Addr(uint8_t page,uint8_t column)
{
	//LCD12864_CS(LOW);
	column = column + 3;
	page = page - 1;
	LCD12864_Command(0xb0 + page); 
	/*设置页地址。每页是 8 行。一个画面的 64 行被分成 8 个页。我们平常所说
	的第 1 页，在 LCD 驱动 IC 里是第 0 页，所以在这里减去 1*/
	LCD12864_Command(((column>>4)&0x0f)+0x10); //设置列地址的高 4 位
	LCD12864_Command(column&0x0f); //设置列地址的低 4 位
}
/*
****************************************************
*  Function       : LCD12864_ClearScreen
*  Description    : 清屏
*  Calls          : 
*  Called By      : 
*  Input          : 
*  Output         : 
*  Return         : 
*  Others         : 
*****************************************************
*/
void LCD12864_ClearScreen(uint8_t Data)
{
	uint8_t i,j;
	
	for(i = 0;i < 8;i ++)
	{
		for(j = 0;j < 128;j ++)
		{
			JLX12864G.LcdRam[i][j] = Data;
		}
	}
	
	for(i = 0;i < 8;i ++)
	{
		for(j = 0;j < 2;j ++)
		{
			JLX12864G.BitMapNeedUpdate[i][j] = 0xFF;
		}
	}
	
	LCD12864Sync();
}
/*
****************************************************
*  Function       : LCD12864_TestDisplay
*  Description    : LCD测试屏幕
*  Calls          : 
*  Called By      : 
*  Input          : Data1:第一个数据Data2:第二个数据
*  Output         : 
*  Return         : 
*  Others         : 
*****************************************************
*/
void LCD12864_TestDisplay(uint8_t Data1,uint8_t Data2)
{
	uint8_t i,j;
	
	for(i = 0;i < 8;i ++)
	{
		for(j = 0;j < 128;j ++)
		{
			JLX12864G.LcdRam[i][j] = j % 2 == 0 ? Data1:Data2;
		}
	}
	for(i = 0;i < 8;i ++)
	{
		for(j = 0;j < 2;j ++)
		{
			JLX12864G.BitMapNeedUpdate[i][j] = 0xFF;
		}
	}

	LCD12864Sync();
}
/*
****************************************************
*  Function       : LCD12864_Graphic
*  Description    : 显示一幅128*64的图片
*  Calls          : 
*  Called By      : 
*  Input          : 
					X_Start:1-64
					X_End:1-64
					Y_Start:1-128
					Y_End:1-128
*  Output         : 
*  Return         : 
*  Others         : 
						ZJYC:一定要注意你取得字模的大小，否则显示出问题！！！！！！！！！！！！！
						有些软件说是32*32的其实是31*31的！！！！！！！！！！！
*****************************************************
*/
void LCD12864_Graphic(uint16_t X_Start,uint16_t X_End,uint16_t Y_Start,uint16_t Y_End,uint8_t * Buff,uint8_t Set)
{
	LCD12864RamWrite(X_Start,X_End,Y_Start,Y_End,Buff,Set);
	LCD12864Sync();
}

/*
****************************************************
*  Function       : LCD12864RamWrite
*  Description    : 将数据写入显存
*  Calls          : 
*  Called By      : 
*  Input          : 
						X_Start:1-64
						X_End:1-64
						Y_Start:1-128
						Y_End:1-128
						Buff:数据缓冲
						Set:画点还是消点
*  Output         : 
						改变了JLX12864G的BitMapNeedUpdate和BitMapCrack
*  Return         : 成功返回0
*  Others         : 写此函数的初衷：（1）使用显存后期方便调试和管理
					（2）解决了因只能8位写入而造成的一些阻碍
					2016--08--22--11--15--59：
					修正BUG：不能画（x,128）的点
*****************************************************
*/
uint8_t LCD12864RamWrite(
							uint16_t X_Start,
							uint16_t X_End,
							uint16_t Y_Start,
							uint16_t Y_End,
							uint8_t * Buff,
							uint8_t Set)
{
	uint16_t i,j,k = 0,m = 0,n = 0,l = 0;
	uint8_t Temp;
	
	//越界返回错误
	if(X_End > 64 || X_Start > 64 || Y_End > 128 || Y_Start > 128)return 0x01;
	if(X_Start > X_End || Y_Start > Y_End)return 0x02;
	X_Start--;
	X_End--;
	Y_Start--;
	Y_End--;
	
	l =  Y_End - Y_Start + 1;
	
	for(i = X_Start;i <= X_End;i ++,n ++)
	{
		k = (n / 8) * l;
		for(j = Y_Start;j <= Y_End;j ++)
		{
			/* 位图 */
			JLX12864G.BitMapNeedUpdate[i / 8][j / 8 / 8] |= ( 1 << (j > 64 ? (j - 64) / 8 : j / 8));
			/* 填充显存 */
			Temp = JLX12864G.LcdRam[i / 8][j];
			if(Set & LCD12864_NORMAL)
			{
				if(Set & LCD12864_SET)Temp |= (*(Buff + k) & (1 << ((n) % 8))) ? (1 << ((i) % 8)) : 0;
				if(Set & LCD12864_CLR)Temp &= ~(*(Buff + k) & (1 << ((n) % 8))) ? (1 << ((i) % 8)) : 0;
				JLX12864G.LcdRam[i / 8][j] = Temp;
			}
			if(Set & LCD12864_REVERSE)
			{
				if(Set & LCD12864_SET)Temp |= (*(Buff + k) & (1 << ((n) % 8))) ? 0 : (1 << ((i) % 8));
				if(Set & LCD12864_CLR)Temp &= ~(*(Buff + k) & (1 << ((n) % 8))) ? 0 : (1 << ((i) % 8));	
				JLX12864G.LcdRam[i / 8][j] = Temp;				
			}
			k++;
		}
	}
	
	return 0x00;
}
/*
****************************************************
*  Function       : LCD12864Sync
*  Description    : 同步显存到LCD
*  Calls          : 
*  Called By      : 
*  Input          : 
*  Output         : 
*  Return         : 
*  Others         : 依据BitMapNeedUpdate信息
					2016--08--22--11--14--00:
					发现LCD的一个轻微缺陷（BUG）只要是拉低CS，过一会再拉高，LCD就会画一个点
*****************************************************
*/
uint8_t LCD12864Sync(void)
{
	uint16_t i,j,k,m;

	for(i = 0;i < 8;i ++)
	{
		for(j = 0;j < 2;j ++)
		{
			if(JLX12864G.BitMapNeedUpdate[i][j] == 0)continue;
			
			for(k = 0;k < 8;k ++)
			{
				if(JLX12864G.BitMapNeedUpdate[i][j] & (1 << k))
				{
					//LCD12864_CS(LOW);
					LCD12864_Addr(i + 1,8 * (j * 8 + k) + 1);
					for(m = 0;m < 8;m ++)
					{
						LCD12864_Data(JLX12864G.LcdRam[i][8 * (j * 8 + k) + m]);
					}
					JLX12864G.BitMapNeedUpdate[i][j] &= ~(1 << k);
					
				}
			}
		}
	}
    //LCD12864_CS(HIGH);
	return 0x00;
}
/*
****************************************************
*  Function       : LCD12864SetPixel
*  Description    : 画点函数
*  Calls          : 
*  Called By      : 
*  Input          : x y：坐标color颜色（0xff黑色，0x00白色）
*  Output         : 
*  Return         : 
*  Others         : 
*****************************************************
*/
uint8_t LCD12864SetPixel(uint8_t x,uint8_t y,uint8_t color,uint8_t Set)
{
	uint8_t temp = 0x00;
	if(color == 0xFF)temp = 0xff;
	if(color == 0x00)temp = 0x00;
	LCD12864RamWrite(x,x,y,y,&temp,Set);
}

