
#include <avr/io.h>
#define F_CPU 16000000UL 
#include <util/delay.h>
#include "DIO_Interface.h"
#include "mMotor_Driver.h"



void init_MotorDriver(){
    
    //Enables
    DIO_SET_PIN_DIR(&PORTD,PD4,OUTPUT);
    DIO_SET_PIN_DIR(&PORTD,PD5,OUTPUT);
    //H
    DIO_SET_PIN_DIR(&PORTC,PC3,OUTPUT);
    DIO_SET_PIN_DIR(&PORTC,PC4,OUTPUT);
    DIO_SET_PIN_DIR(&PORTC,PC5,OUTPUT);
    DIO_SET_PIN_DIR(&PORTC,PC6,OUTPUT);
    _delay_ms(50);
}


void Motor_Enable(uint8 Enable){
    
    switch(Enable){
        case Motor1_Enable:
            DIO_SET_PIN_VALUE(&PORTD,PD4,HIGH);
            break;
        case Motor2_Enable:
            DIO_SET_PIN_VALUE(&PORTD,PD5,HIGH);
            break;
        case Motor_1and2_Enable:
            DIO_SET_PIN_VALUE(&PORTD,PD4,HIGH);
            DIO_SET_PIN_VALUE(&PORTD,PD5,HIGH);
            break;
        default:
            
            break;
        _delay_ms(20);
    }
    
}


void Motor_Disable(uint8 Disable){
    
    switch(Disable){
        case Motor1_Disable:
            DIO_SET_PIN_VALUE(&PORTD,PD4,LOW);
            break;
        case Motor2_Disable:
            DIO_SET_PIN_VALUE(&PORTD,PD5,LOW);
            break;
        case Motor_1and2_Disable:
            DIO_SET_PIN_VALUE(&PORTD,PD4,LOW);
            DIO_SET_PIN_VALUE(&PORTD,PD5,LOW);
            break;
        default:
            
            break;
        _delay_ms(20);
    }
}



void Motor_1_Rotate_CW(){
    
    DIO_SET_PIN_VALUE(&PORTC,PC3,HIGH);
    DIO_SET_PIN_VALUE(&PORTC,PC4,LOW);
    
}

void Motor_1_Rotate_CCW(){
    
    DIO_SET_PIN_VALUE(&PORTC,PC3,LOW);
    DIO_SET_PIN_VALUE(&PORTC,PC4,HIGH);
    
}

void Motor_2_Rotate_CW(){
    
    DIO_SET_PIN_VALUE(&PORTC,PC5,HIGH);
    DIO_SET_PIN_VALUE(&PORTC,PC6,LOW);
    
}

void Motor_2_Rotate_CCW(){
    
    DIO_SET_PIN_VALUE(&PORTC,PC5,LOW);
    DIO_SET_PIN_VALUE(&PORTC,PC6,HIGH);
    
}


 void Motor_Stop(uint8 Motor){
    
    switch(Motor){
        
        case Motor1_Stop:
            DIO_SET_PIN_VALUE(&PORTC,PC3,HIGH);
            DIO_SET_PIN_VALUE(&PORTC,PC4,HIGH);
            break;
        case Motor2_Stop:
            DIO_SET_PIN_VALUE(&PORTC,PC5,HIGH);
            DIO_SET_PIN_VALUE(&PORTC,PC6,HIGH);
            break;
        case Motor_1and2_Stop:
            DIO_SET_PIN_VALUE(&PORTC,PC3,LOW);
            DIO_SET_PIN_VALUE(&PORTC,PC4,LOW);
            DIO_SET_PIN_VALUE(&PORTC,PC5,LOW);
            DIO_SET_PIN_VALUE(&PORTC,PC6,LOW);
            break;
        default:
            
            break;
    }
    
}
