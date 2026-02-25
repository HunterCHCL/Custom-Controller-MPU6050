/*
 * OLED.h
 *
 *  Created on: Feb 2, 2026
 *      Author: HunterCHCL
 */

#ifndef INC_OLED_H_
#define INC_OLED_H_

#include "i2c.h"
#include "OLED_Font.h"

void OLED_Clear();
void OLED_SetCursor(uint8_t Y, uint8_t X);
void OLED_ShowChar(uint8_t Line, uint8_t Column, char Char);
void OLED_ShowString(uint8_t Line, uint8_t Column, char *String);
void OLED_ShowNum(uint8_t Line, uint8_t Column, uint32_t Number, uint8_t Length);
void OLED_ShowFloat(uint8_t Line, uint8_t Column, float Number, uint8_t Length);
void OLED_Init(void);
void OLED_WriteCommand(uint8_t CMD);
void OLED_WriteData(uint8_t Data);

#endif /* INC_OLED_H_ */
