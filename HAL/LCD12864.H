
#ifndef __LCD12864_H__
#define __LCD12864_H__

/* 包含头文件 */

#include "stm32f1xx_hal.h"
#include "tim.h"
#include "gpio.h"

/* 宏定义 */
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
/* 显存 */
typedef struct JLX12864G_Struct
{
	/* 需要更新 */
	uint8_t BitMapNeedUpdate[8][128/8/8];
	/* 正在更新 */
	uint8_t BitMapUpdating[8][128/8/8];
	/* 发生冲突*/
	uint8_t BitMapCrack[8][128/8/8];
	/* 显存 */
	uint8_t LcdRam[8][128];
}JLX12864G_;


#define LCD12864_SET		(1 << 0)/* 画点 */
#define LCD12864_CLR		(1 << 1)/* 消点 */
#define LCD12864_REVERSE	(1 << 2)/* 反色 */
#define LCD12864_NORMAL		(1 << 3)/* 正常 */

typedef enum _FontType_
{
	None = 0,	//空
	Array = 1,	//数组(片内flash或者是RAM)
	Flash = 2	//片外flash
}FontType_;


/* 字库管理 */
typedef struct FONT_Manage_
{
	/* 构成单链表 */
	struct FONT_Manage_ * NEXT;
	/* 字库类型--方便搜索*/
	FontType_ FontType;
	/* 高和宽--方便搜索 */
	uint8_t H;
	uint8_t W;
	/* 自带函数--获取字库索引或者是缓冲 */
	uint32_t (*GetFont)(uint8_t * Char,uint32_t * Index,uint8_t * Buff,FontType_ Type);
	/* 
		这里：
		Buff 非0 则将字库读取到 Buff中，一定要保证Buff足够大
		Buff 为 0 则将地址返回到Index中。
		无论如何，都会返回读取了多少个字节，返回非 0 为正常
		Char：汉字的2个字节的ASCII码都大于128，字母和数字的字节都小于128
	*/
}FONT_MANAGE,*pFONT_MANAGE;


void 	LCD12864_ClearScreen(uint8_t Data);
uint8_t LCD12864Sync(void);
uint8_t LCD12864RamWrite(uint16_t X_Start,uint16_t X_End,uint16_t Y_Start,uint16_t Y_End,uint8_t * Buff,uint8_t Set);
uint8_t LCD12864SetPixel(uint8_t x,uint8_t y,uint8_t color,uint8_t Set);
uint8_t LCD12864LLInit(void);
void LCD12864_Graphic(uint16_t X_Start,uint16_t X_End,uint16_t Y_Start,uint16_t Y_End,uint8_t * Buff,uint8_t Set);




#endif






