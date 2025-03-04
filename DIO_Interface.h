/* 
 * File:   DIO_Interface.h
 * Author: Moustafa Yasser
 *
 * Created on November 18, 2024, 9:38 PM
 */

/*#ifndef DIO_INTERFACE_H
#define	DIO_INTERFACE_H



#endif	/* DIO_INTERFACE_H */

typedef unsigned char uint8;
typedef char int8;
typedef unsigned short int uint16;
typedef short int int16;
typedef unsigned int uint32;
typedef int int32;

#define INPUT_PORT 0x00
#define OUTPUT_PORT 0xFF
#define OUTPUT 1
#define INPUT 0
#define HIGH 1
#define LOW 0
#define OFF      0
#define ON     1


//PORT LEVEL
void DIO_SET_PORT_DIR(volatile uint8* PORTx , uint8 DIR);
void DIO_SET_PIN_DIR(volatile uint8* PORTx , uint8 PIN, uint8 DIR);
void DIO_SET_PORT_VALUE(volatile uint8* PORTx  , uint8 Val);
void DIO_SET_PIN_VALUE(volatile uint8* PORTx , uint8 PIN, uint8 Val);
void DIO_READ_PORT(volatile uint8* PORTx, uint8* Val);
void DIO_READ_PIN(volatile uint8* PORTx, uint8 PIN, uint8* Val);
void DIO_Toggel_PIN(volatile uint8* PORTx, uint8 PIN);
