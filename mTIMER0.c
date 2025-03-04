
#include <avr/io.h>
#include "DIO_Interface.h"
#include "mTIMER0.h"


void init_TIMER0 (uint8 TIMER0_Mode , uint8 TIMER0_ClockSelect){
    switch(TIMER0_Mode){
        case TIMER0_Normal_Mode:
            TCCR0 &=~ ((1<<WGM00) | (1<<WGM01));
            break;
        case TIMER0_PWM_Mode:
            TCCR0 &=~ ((1<<WGM00) | (1<<WGM01));
            TCCR0 |= (1<<WGM00);
            break;
        case TIMER0_CTC_Mode:
            TCCR0 &=~ ((1<<WGM00) | (1<<WGM01));
            TCCR0 |= (1<<WGM01);
            break;
        case TIMER0_FPWM_Mode:
            TCCR0 &=~ ((1<<WGM00) | (1<<WGM01));
            TCCR0 |= ((1<<WGM01) | (1<<WGM00));
            break;
        default:
            
            break;
    }
    TCCR0 &= 0xF8;
    TCCR0 |= TIMER0_ClockSelect;
}


void TIMER0_Interrupt_EN(uint8 enable){
    TIMSK |= enable;
}


void TIMER0_COMP_VAL(uint8 value){
    OCR0 = value;
}

void TIMER0_CompareMode_nonPWM (uint8 Mode, uint8 COMP_value){
    
    DIO_SET_PIN_DIR(&PORTB,PB3,HIGH); //The OC0 value will not be visible on the port pin unless the data direction for the pin is set to output
    TIMER0_COMP_VAL(COMP_value);
    
    switch(Mode){
        case TIMER0_OC0_disconnected:
            TCCR0 &=~ ((1<<COM00) | (1<<COM01));
            break;
        case TIMER0_Toggle_OC0_on_COMP:
            TCCR0 &=~ ((1<<COM00) | (1<<COM01));
            TCCR0 |= (1<<COM00);
            break;
        case TIMER0_Clear_OC0_on_COMP:
            TCCR0 &=~ ((1<<COM00) | (1<<COM01));
            TCCR0 |= (1<<COM01);
            break;
        case TIMER0_Set_OC0_on_COMP:
            TCCR0 &=~ ((1<<COM00) | (1<<COM01));
            TCCR0 |= ((1<<COM01) | (1<<COM00));
            break;
        default:
            
            break;
    }
}


void TIMER0_CompareMode_PWM (uint8 Mode, uint8 COMP_value){
    
    DIO_SET_PIN_DIR(&PORTB,PB3,HIGH); //The OC0 value will not be visible on the port pin unless the data direction for the pin is set to output
    TIMER0_COMP_VAL(COMP_value);
    
    switch(Mode){
        case TIMER0_noninverting_mode:
            TCCR0 &=~ ((1<<COM00) | (1<<COM01));
            TCCR0 |= (1<<COM01);
            break;
        case TIMER0_inverting_mode:
            TCCR0 &=~ ((1<<COM00) | (1<<COM01));
            TCCR0 |= ((1<<COM01) | (1<<COM00));
            break;
        default:
            
            break;
    }
}