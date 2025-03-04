/* 
 * File:   mLCD4.h
 * Author: Moustafa Yasser
 *
 * Created on November 29, 2024, 6:14 PM
 */

#ifndef MLCD4_H
#define	MLCD4_H

#define RS PB1
#define RW PB2
#define EN PB3

#define LCD_DATA_PORT &PORTA
#define LCD_CONTROL_PINS_PORT &PORTB

void init_LCD4();
void LCD4_WriteChar(uint8 data);
void LCD4_WriteCmd(uint8 cmd);
void LCD4_WriteStr(uint8* str);
void LCD4_WriteNum(int32 num);
void LCD4_EN();
void LCD4_Clear();
void LCD4_Begining_SecondLine();
void LCD4_Begining_FirstLine();

#endif	/* MLCD4_H */

