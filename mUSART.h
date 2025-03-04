/* 
 * File:   mUSART.h
 * Author: Moustafa Yasser
 *
 * Created on December 20, 2024, 6:14 PM
 */

#ifndef MUSART_H
#define	MUSART_H


#include "DIO_Interface.h"

/*----Baud Rate Asyn----*/
#define BaudRate_Asyn_1M      0
#define BaudRate_Asyn_half_M  1
#define BaudRate_Asyn_250K    3
#define BaudRate_Asyn_115K    8
#define BaudRate_Asyn_77K     12
#define BaudRate_Asyn_58K     16
#define BaudRate_Asyn_38K     25
#define BaudRate_Asyn_19K     51
#define BaudRate_Asyn_14K     68
#define BaudRate_Asyn_9600    103
#define BaudRate_Asyn_4800    207
#define BaudRate_Asyn_2400    416

/*----Baud Rate syn----*/
#define BaudRate_syn_1M      7
#define BaudRate_syn_half_M  15
#define BaudRate_syn_250K    31
#define BaudRate_syn_115K    68
#define BaudRate_syn_77K     103
#define BaudRate_syn_58K     138
#define BaudRate_syn_38K     207
#define BaudRate_syn_19K     415
#define BaudRat_syne_14K     555
#define BaudRate_syn_9600    832
#define BaudRate_syn_4800    1665
#define BaudRate_syn_2400    3327

/*----Enable Interrupt----*/
#define USART_EN_RXCIE  RXCIE
#define USART_EN_TXCIE  TXCIE
#define USART_EN_UDRIE  UDRIE

void init_USART(uint16 BaudRate);
void init_USRT(uint16 BaudRate);
void Write_char_USART(uint8 data);
void Write_str_USART(uint8* str);
uint8 Read_char_USART();
void USART_EN_INT(uint8 Enable);
uint8 USART_READFrom_UDR_Reg();



#endif	/* MUSART_H */

