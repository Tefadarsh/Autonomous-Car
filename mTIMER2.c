

#include <avr/io.h>
#include "DIO_Interface.h"
#include "mTIMER2.h"


void init_TIMER2(uint8 TIMER2_Mode , uint8 TIMER2_ClockSelect){
    switch(TIMER2_Mode){
        case TIMER2_Normal_Mode:
            TCCR2 &=~ ((1<<WGM20) | (1<<WGM21));
            break;
        case TIMER2_PWM_Mode:
            TCCR2 &=~ ((1<<WGM20) | (1<<WGM21));
            TCCR2 |= (1<<WGM20);
            break;
        case TIMER2_CTC_Mode:
            TCCR2 &=~ ((1<<WGM20) | (1<<WGM21));
            TCCR2 |= (1<<WGM21);
            break;
        case TIMER2_FPWM_Mode:
            TCCR2 &=~ ((1<<WGM20) | (1<<WGM21));
            TCCR2 |= ((1<<WGM21) | (1<<WGM20));
            break;
        default:
            
            break;
    }
    
    TCCR2 |= TIMER2_ClockSelect;
}


void TIMER2_Interrupt_EN(uint8 enable){
    TIMSK |= enable;
}


void TIMER2_COMP_VAL(uint8 value){
    OCR2 = value;
}

void TIMER2_CompareMode_nonPWM (uint8 Mode, uint8 COMP_value){
    
    DIO_SET_PIN_DIR(&PORTD,PD7,HIGH); //The OC2 value will not be visible on the port pin unless the data direction for the pin is set to output
    TIMER2_COMP_VAL(COMP_value);
    
    switch(Mode){
        case TIMER2_OC2_disconnected:
            TCCR2 &=~ ((1<<COM20) | (1<<COM21));
            break;
        case TIMER2_Toggle_OC2_on_COMP:
            TCCR2 &=~ ((1<<COM20) | (1<<COM21));
            TCCR2 |= (1<<COM20);
            break;
        case TIMER2_Clear_OC2_on_COMP:
            TCCR2 &=~ ((1<<COM20) | (1<<COM21));
            TCCR2 |= (1<<COM21);
            break;
        case TIMER2_Set_OC2_on_COMP:
            TCCR2 &=~ ((1<<COM20) | (1<<COM21));
            TCCR2 |= ((1<<COM21) | (1<<COM20));
            break;
        default:
            
            break;
    }
}


void TIMER2_CompareMode_PWM (uint8 Mode, uint8 COMP_value){
    
    DIO_SET_PIN_DIR(&PORTD,PD7,HIGH); //The OC2 value will not be visible on the port pin unless the data direction for the pin is set to output
    TIMER2_COMP_VAL(COMP_value);
    
    switch(Mode){
        case TIMER2_noninverting_mode:
            TCCR2 &=~ ((1<<COM20) | (1<<COM21));
            TCCR2 |= (1<<COM21);
            break;
        case TIMER2_inverting_mode:
            TCCR2 &=~ ((1<<COM20) | (1<<COM21));
            TCCR2 |= ((1<<COM21) | (1<<COM20));
            break;
        default:
            
            break;
    }
}
