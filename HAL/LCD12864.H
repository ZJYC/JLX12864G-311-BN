
#ifndef __LCD12864_H__
#define __LCD12864_H__

/* ����ͷ�ļ� */

#include "stm32f1xx_hal.h"
#include "tim.h"
#include "gpio.h"

/* �궨�� */
#define   HIGH	                GPIO_PIN_SET
#define   LOW	                GPIO_PIN_RESET

#define LCD12864_RD_Pin             GPIO_PIN_11
#define LCD12864_RD_GPIO_Port       GPIOB
#define LCD12864_WR_Pin             GPIO_PIN_12
#define LCD12864_WR_GPIO_Port       GPIOB
#define LCD12864_RS_Pin             GPIO_PIN_13
#define LCD12864_RS_GPIO_Port       GPIOB
#define LCD12864_RES_Pin            GPIO_PIN_14
#define LCD12864_RES_GPIO_Port      GPIOB
#define LCD12864_CS_Pin             GPIO_PIN_15
#define LCD12864_CS_GPIO_Port       GPIOB
#define LCD12864_DATA_Port          GPIOD

#define   LCD12864_CS(X)	    {                                                                                       \
                                    if((X) == HIGH)HAL_GPIO_WritePin(LCD12864_CS_GPIO_Port,LCD12864_CS_Pin,HIGH);      \
                                    else HAL_GPIO_WritePin(LCD12864_CS_GPIO_Port,LCD12864_CS_Pin,LOW);                 \
									LCD12864_Delay(0);\
                                }
#define   LCD12864_RES(X)	    {                                                                                       \
                                    if((X) == HIGH)HAL_GPIO_WritePin(LCD12864_RES_GPIO_Port,LCD12864_RES_Pin,HIGH);    \
                                    else HAL_GPIO_WritePin(LCD12864_RES_GPIO_Port,LCD12864_RES_Pin,LOW);               \
									LCD12864_Delay(0);\
                                }
#define   LCD12864_RS(X)	    {                                                                                       \
                                    if((X) == HIGH)HAL_GPIO_WritePin(LCD12864_RS_GPIO_Port,LCD12864_RS_Pin,HIGH);       \
                                    else HAL_GPIO_WritePin(LCD12864_RS_GPIO_Port,LCD12864_RS_Pin,LOW);                  \
									LCD12864_Delay(0);\
                                }
#define   LCD12864_WR(X)	    {                                                                                       \
                                    if((X) == HIGH)HAL_GPIO_WritePin(LCD12864_WR_GPIO_Port,LCD12864_WR_Pin,HIGH);       \
                                    else HAL_GPIO_WritePin(LCD12864_WR_GPIO_Port,LCD12864_WR_Pin,LOW);                  \
									LCD12864_Delay(0);\
                                }
#define   LCD12864_RD(X)		{																						\
								if((X) == HIGH)HAL_GPIO_WritePin(LCD12864_RD_GPIO_Port,LCD12864_RD_Pin,HIGH);			\
                                else HAL_GPIO_WritePin(LCD12864_RD_GPIO_Port,LCD12864_RD_Pin,LOW);						\
								LCD12864_Delay(0);\
}

#define   LCD12864_DATA(X)      {                                                                                       \
                                    HAL_GPIO_WritePin(LCD12864_DATA_Port,(X)&0x00FF,HIGH);                              \
                                    HAL_GPIO_WritePin(LCD12864_DATA_Port,~((X)|0xFF00),LOW);                            \
									LCD12864_Delay(0);\
                                }
/* �Դ� */
typedef struct JLX12864G_Struct
{
	/* ��Ҫ���� */
	uint8_t BitMapNeedUpdate[8][128/8/8];
	/* ���ڸ��� */
	uint8_t BitMapUpdating[8][128/8/8];
	/* ������ͻ*/
	uint8_t BitMapCrack[8][128/8/8];
	/* �Դ� */
	uint8_t LcdRam[8][128];
}JLX12864G_;


#define LCD12864_SET		(1 << 0)/* ���� */
#define LCD12864_CLR		(1 << 1)/* ���� */
#define LCD12864_REVERSE	(1 << 2)/* ��ɫ */
#define LCD12864_NORMAL		(1 << 3)/* ���� */

typedef enum _FontType_
{
	None = 0,	//��
	Array = 1,	//����(Ƭ��flash������RAM)
	Flash = 2	//Ƭ��flash
}FontType_;


/* �ֿ���� */
typedef struct FONT_Manage_
{
	/* ���ɵ����� */
	struct FONT_Manage_ * NEXT;
	/* �ֿ�����--��������*/
	FontType_ FontType;
	/* �ߺͿ�--�������� */
	uint8_t H;
	uint8_t W;
	/* �Դ�����--��ȡ�ֿ����������ǻ��� */
	uint32_t (*GetFont)(uint8_t * Char,uint32_t * Index,uint8_t * Buff,FontType_ Type);
	/* 
		���
		Buff ��0 ���ֿ��ȡ�� Buff�У�һ��Ҫ��֤Buff�㹻��
		Buff Ϊ 0 �򽫵�ַ���ص�Index�С�
		������Σ����᷵�ض�ȡ�˶��ٸ��ֽڣ����ط� 0 Ϊ����
		Char�����ֵ�2���ֽڵ�ASCII�붼����128����ĸ�����ֵ��ֽڶ�С��128
	*/
}FONT_MANAGE,*pFONT_MANAGE;


void 	LCD12864_ClearScreen(uint8_t Data);
uint8_t LCD12864Sync(void);
uint8_t LCD12864RamWrite(uint16_t X_Start,uint16_t X_End,uint16_t Y_Start,uint16_t Y_End,uint8_t * Buff,uint8_t Set);
uint8_t LCD12864SetPixel(uint8_t x,uint8_t y,uint8_t color,uint8_t Set);
uint8_t LCD12864LLInit(void);
void LCD12864_Graphic(uint16_t X_Start,uint16_t X_End,uint16_t Y_Start,uint16_t Y_End,uint8_t * Buff,uint8_t Set);




#endif





