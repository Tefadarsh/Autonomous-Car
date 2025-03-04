
#include <avr/io.h>
#define F_CPU 16000000UL
#include <util/delay.h>
#include "DIO_Interface.h"
#include "mTIMER2.h"
#include "mSERVO.h"


void init_Servo(){
    init_TIMER2(TIMER2_FPWM_Mode,TIMER2_Prescaling_1024);
}


void Servo_degree(uint8 degree){
    int8 OCR_value= ((4/2.99999)*(degree))+85;
    TIMER2_CompareMode_PWM(TIMER2_noninverting_mode,OCR_value);  //0degree cor to 85 and 90degree cor to 205
    //_delay_ms(1000); //so that i can see the change in the angle from 0 to 90
}




void Servo_btw_0to90_Smoothly(){
    
    for(int i=85 ; i<=205 ; i++){
           TIMER2_CompareMode_PWM(TIMER2_noninverting_mode,i);
           _delay_ms(8); // control speed of rotation
       }
       _delay_ms(500); // rest half second at 0 position
       
       for(int i=205 ; i>=85 ; i--){
           TIMER2_CompareMode_PWM(TIMER2_noninverting_mode,i);
           _delay_ms(8); // control speed of rotation
       }
       _delay_ms(500); // rest half second at 90 position
}
