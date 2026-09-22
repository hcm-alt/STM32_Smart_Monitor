#ifndef __OLED_H
#define __OLED_H

#include "main.h"

void OLED_WriteCommand(uint8_t command);
void OLED_Init(void);
void OLED_Clear(void);
void OLED_WriteData(uint8_t data); 
void OLED_SetCursor(uint8_t page,uint8_t column);
void OLED_ShowChar(uint8_t page,uint8_t column,char ch);
void OLED_ShowString(uint8_t page,uint8_t column,const char *str);
#endif