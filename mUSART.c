
#include <avr/io.h>
#include "DIO_Interface.h"
#include "mUSART.h"


void init_USART(uint16 BaudRate){
     
    //Set baud rate 
    UBRRH = (uint8)(BaudRate >> 8); 
    UBRRL = (uint8)BaudRate; 
    
    //default Mode is Asynchronous
    
    //default format frame is 8 bit
    
    //Enabling the Rx and Tx 
    UCSRB |= ((1<<TXEN)|(1<<RXEN));
    
    
    
}

void init_USRT(uint16 BaudRate){
    
    //Set baud rate 
    UBRRH = (uint8)(BaudRate >> 8);
    UBRRL = (uint8)BaudRate;
    
    //set Mode as synchronous
    UCSRC |= (1<<URSEL) | (1<<UMSEL);
    
    //default format frame is 8 bit
    
    //Enabling the Rx and Tx 
    UCSRB |= (1<<TXEN) | (1<<RXEN);
    
    // Set clock polarity
    UCSRC &=~ (1<<UCPOL);
    
    
}

void Write_char_USART(uint8 data){
    
    while(!(UCSRA & (1<<UDRE))); //When UDR is empty then you can write
    
    UDR = data;
}

void Write_str_USART(uint8* str){
    
    
    for(uint8 i=0; str[i]!='\0'; i++){
        
        Write_char_USART(str[i]);
    }
    
}

uint8 Read_char_USART(){
    
    while(!(UCSRA & (1<<RXC))); //when data is transfered from Rx shift register to UDR then you can read
    
    return UDR;
}


void USART_EN_INT(uint8 Enable){
    UCSRB |= (1 << Enable);
}

uint8 USART_READFrom_UDR_Reg(){
    return UDR;
}


