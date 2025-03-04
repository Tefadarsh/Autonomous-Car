
#include <avr/io.h>
#define F_CPU 16000000UL 
#include <util/delay.h>
#include "DIO_Interface.h"
#include "mUltraSonic.h"
#include "mTIMER0.h"


void init_UltraSonic(){
    
    DIO_SET_PIN_DIR(&PORTA,PA0,OUTPUT);
    DIO_SET_PIN_DIR(&PORTD,PD2,INPUT);
    _delay_ms(20);
}

void UtraSonic_Trigger_Pulse(){
    
    DIO_SET_PIN_VALUE(&PORTA,PA0,HIGH);
    _delay_us(15);
    DIO_SET_PIN_VALUE(&PORTA,PA0,LOW);
    
}

uint16 UtraSonic_Distance_Measuerment(){
    
    
    uint16 Pulse_Duration=0;
    //init_TIMER0(TIMER0_Normal_Mode,TIMER0_Prescaling_8);
    UtraSonic_Trigger_Pulse();
    //init_TIMER0(TIMER0_Normal_Mode,TIMER0_Prescaling_8);

        // Wait for Echo Pulse
        while (!(PIND & (1 << PD2)));  // Wait for HIGH
        
        TCNT0=0; // start counting from beginning
        counter=0;
        init_TIMER0(TIMER0_Normal_Mode,TIMER0_Prescaling_8);
        //init_TIMER0(TIMER0_Normal_Mode,TIMER0_No_Clock);
        //TCCR0 |= TIMER0_No_Clock;
        while (PIND & (1 << PD2));  // Wait for LOW
        TCCR0 |= TIMER0_No_Clock;
        Pulse_Duration=((TCNT0 >> 1) + 128*counter ); //Duration in microseconds
        
        
        return (uint16)(Pulse_Duration/58); //convert to cm
}
