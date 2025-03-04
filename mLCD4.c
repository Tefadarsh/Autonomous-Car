
#include <avr/io.h>
#define F_CPU 16000000UL
#include <util/delay.h>

#include "DIO_Interface.h"
#include "mLCD4.h"
#include <stdlib.h>
#include <string.h>


void init_LCD4(){
    DIO_SET_PORT_DIR(LCD_DATA_PORT,0xF0);
    DIO_SET_PIN_DIR(LCD_CONTROL_PINS_PORT,RS,OUTPUT);
    DIO_SET_PIN_DIR(LCD_CONTROL_PINS_PORT,RW,OUTPUT);
    DIO_SET_PIN_DIR(LCD_CONTROL_PINS_PORT,EN,OUTPUT);
    _delay_ms(50); //LCD needs at min 40 ms to initiate 
    
    
    //LCD commands

    LCD4_WriteCmd(0x02);   //Return home
    _delay_ms(2);
    LCD4_WriteCmd(0x28);   //set 4bit, 2line, 5*7 Dots
    _delay_ms(2);
    LCD4_WriteCmd(0x0C);   //Display on
    _delay_ms(2);
    LCD4_WriteCmd(0x06);   //Entry Mode
    _delay_ms(2);
    LCD4_Clear();          //clear the display
     
    
}

void LCD4_WriteChar(uint8 data){
    
    *LCD_DATA_PORT = (*LCD_DATA_PORT & 0x0F) | (data & 0xF0); // here i pass the high nibble of data to the high nibble of port without affecting the rest of pins of that port
    DIO_SET_PIN_VALUE(LCD_CONTROL_PINS_PORT,RS,HIGH);
    _delay_us(1); //small delay to insure the setup of Register select
    LCD4_EN();
    *LCD_DATA_PORT = (*LCD_DATA_PORT & 0x0F) | (data<<4); // here i pass the low nibble of data to the high nibble of port without affecting the rest of pins of that port
    LCD4_EN();
    
    
    
}

void LCD4_WriteCmd(uint8 cmd){
    
    *LCD_DATA_PORT = (*LCD_DATA_PORT & 0x0F) | (cmd & 0xF0); // here i pass the high nibble of cmd to the high nibble of port without affecting the rest of pins of that port
    DIO_SET_PIN_VALUE(LCD_CONTROL_PINS_PORT,RS,LOW);
    _delay_us(1); //small delay to insure the setup of Register select
    LCD4_EN();
    *LCD_DATA_PORT = (*LCD_DATA_PORT & 0x0F) | (cmd<<4); // here i pass the low nibble of cmd to the high nibble of port without affecting the rest of pins of that port
    LCD4_EN();
    _delay_ms(2); //this average delay to insure that most of the cmds took their time of execution
    
}

void LCD4_WriteStr(uint8* str){
    for(uint8 i=0; str[i] != '\0' ; i++){
        LCD4_WriteChar(str[i]);
    }
}

void LCD4_WriteNum(int32 num){
    int8 arr[11];
    itoa(num,arr,10); //this function take any signed integer number and transfer it to array of chars
    LCD4_WriteStr(arr);  
}

void LCD4_EN(){
    DIO_SET_PIN_VALUE(LCD_CONTROL_PINS_PORT,EN,HIGH);
    _delay_us(50); //as min enable time ranges from 140 nano s to 1 micro s
    DIO_SET_PIN_VALUE(LCD_CONTROL_PINS_PORT,EN,LOW);
}

void LCD4_Clear(){
    LCD4_WriteCmd(0x01);
    _delay_ms(2);
}

void LCD4_Begining_SecondLine(){
    LCD4_WriteCmd(0xC0);
}

void LCD4_Begining_FirstLine(){
    LCD4_WriteCmd(0x80);
}




