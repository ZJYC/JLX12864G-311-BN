
#include "LCD12864.h"
/*
****************************************************
*  File name          : LCD12864.c
*  Author             : 5A4A5943
*  Version            : V1.0
*  Date               : 
*  Description        : 
*  Function List      : 
						void LCD12864_Init(void)
						void LCD12864_ClearScreen(uint8_t Data)
						void LCD12864_TestDisplay(uint8_t Data1,uint8_t Data2)
						void LCD12864_Graphic(uint16_t X_Start,uint16_t X_End,uint16_t Y_Start,uint16_t Y_End,uint8_t * Buff)
						uint8_t LCD12864RamWrite(uint16_t X_Start,uint16_t X_End,uint16_t Y_Start,uint16_t Y_End,uint8_t * Buff)
						uint8_t LCD12864Sync(void)
						uint8_t LCD12864SetPixel(uint8_t x,uint8_t y,uint8_t color)
*  History            : 
						2016--08--22--11--04--29��
						���ӻ��㺯��LCD12864SetPixel�����Գɹ�
						
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
*  Description    : ��������
*  Calls          : 
*  Called By      : 
*  Input          : Head������ͷ  Added���¼�Ԫ��
*  Output         : 
*  Return         : ʧ�ܷ��ط� 0 ֵ
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
*  Description    : �ֿ��ʼ��
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
*  Description    : ��ģ����
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
*  Description    : �ײ��ʼ��
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
*  Description    : ��LCD��������
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
*  Description    : ��LCD��������
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
*  Description    : ���ӳٺ������ӳپ���δ֪
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
*  Description    : ��ʼ��LCD
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
	
	/*�͵�ƽ��λ*/
	LCD12864_RES(LOW); 
	LCD12864_Delay(20);
	 /*��λ���*/
	LCD12864_RES(HIGH);
	
	LCD12864_Delay(20);
	/*����λ*/
	LCD12864_Command(0xe2); 
	LCD12864_Delay(50);
	/*��ѹ���� 1*/
	LCD12864_Command(0x2c); 
	LCD12864_Delay(50);
	/*��ѹ���� 2*/
	LCD12864_Command(0x2e); 
	LCD12864_Delay(50);
	/*��ѹ���� 3*/
	LCD12864_Command(0x2f); 
	LCD12864_Delay(50);
	/*�ֵ��Աȶȣ������÷�Χ 0x20��0x27*/
	LCD12864_Command(0x24); 
	/*΢���Աȶ�*/
	LCD12864_Command(0x81); 
	/*0x1a,΢���Աȶȵ�ֵ�������÷�Χ 0x00��0x3f 1f*/
	LCD12864_Command(0x1a); 
	/*1/9 ƫѹ�ȣ�bias��*/
	LCD12864_Command(0xa2);
	/*��ɨ��˳�򣺴��ϵ���*/	
	LCD12864_Command(0xc0); 
	/*��ɨ��˳�򣺴�����*/
	LCD12864_Command(0xa1); 
	/*��ʼ�У���һ�п�ʼ*/
	LCD12864_Command(0x40);
	/* �����ʾ */
	LCD12864_ClearScreen(0x00);
	/*����ʾ*/	
	LCD12864_Command(0xaf); 
	
	LCD12864_CS(HIGH);
}
/*
****************************************************
*  Function       : LCD12864_Addr
*  Description    : �趨��ַ
*  Calls          : 
*  Called By      : 
*  Input          : 
						page(1~8):ҳ��ַ
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
	/*����ҳ��ַ��ÿҳ�� 8 �С�һ������� 64 �б��ֳ� 8 ��ҳ������ƽ����˵
	�ĵ� 1 ҳ���� LCD ���� IC ���ǵ� 0 ҳ�������������ȥ 1*/
	LCD12864_Command(((column>>4)&0x0f)+0x10); //�����е�ַ�ĸ� 4 λ
	LCD12864_Command(column&0x0f); //�����е�ַ�ĵ� 4 λ
}
/*
****************************************************
*  Function       : LCD12864_ClearScreen
*  Description    : ����
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
*  Description    : LCD������Ļ
*  Calls          : 
*  Called By      : 
*  Input          : Data1:��һ������Data2:�ڶ�������
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
*  Description    : ��ʾһ��128*64��ͼƬ
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
						ZJYC:һ��Ҫע����ȡ����ģ�Ĵ�С��������ʾ�����⣡������������������������
						��Щ����˵��32*32����ʵ��31*31�ģ���������������������
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
*  Description    : ������д���Դ�
*  Calls          : 
*  Called By      : 
*  Input          : 
						X_Start:1-64
						X_End:1-64
						Y_Start:1-128
						Y_End:1-128
						Buff:���ݻ���
						Set:���㻹������
*  Output         : 
						�ı���JLX12864G��BitMapNeedUpdate��BitMapCrack
*  Return         : �ɹ�����0
*  Others         : д�˺����ĳ��ԣ���1��ʹ���Դ���ڷ�����Ժ͹���
					��2���������ֻ��8λд�����ɵ�һЩ�谭
					2016--08--22--11--15--59��
					����BUG�����ܻ���x,128���ĵ�
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
	
	//Խ�緵�ش���
	if(X_End > 64 || X_Start > 64 || Y_End > 128 || Y_Start > 128)return 0x01;
	
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
			/* λͼ */
			JLX12864G.BitMapNeedUpdate[i / 8][j / 8 / 8] |= ( 1 << (j > 64 ? (j - 64) / 8 : j / 8));
			/* ����Դ� */
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
*  Description    : ͬ���Դ浽LCD
*  Calls          : 
*  Called By      : 
*  Input          : 
*  Output         : 
*  Return         : 
*  Others         : ����BitMapNeedUpdate��Ϣ
					2016--08--22--11--14--00:
					����LCD��һ����΢ȱ�ݣ�BUG��ֻҪ������CS����һ�������ߣ�LCD�ͻửһ����
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
*  Description    : ���㺯��
*  Calls          : 
*  Called By      : 
*  Input          : x y������color��ɫ��0xff��ɫ��0x00��ɫ��
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
