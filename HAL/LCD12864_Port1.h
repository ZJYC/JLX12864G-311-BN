/*
****************************************************
*  File name          : LCD12864_Port1.h
*  Author             : 5A4A5943
*  Version            : V0.0.1
*  Date               : 
*  Description        : 接口1，用于旧版C020
*  Function List      : 
*  History            : 
*****************************************************
*/
#ifndef __LCD12864_PORT1_H__
#define __LCD12864_PORT1_H__

#include "LCD12864_L1.H"

void DisplayMess(uint8_t sit, uint8_t *p, uint8_t lenth);
void ClrDisplay(void);
void ClrRAMDisplay(void);
void DisplayNum(uint8_t x, uint8_t y, const uint8_t *num);
void ClrFirstList(void);
void dzDisplayPicture2(uint8_t x, uint8_t y, uint8_t img);

#endif





































