/* 
 * File:   mTIMER0.h
 * Author: Moustafa Yasser
 *
 * Created on December 10, 2024, 3:34 PM
 */

#ifndef MTIMER0_H
#define	MTIMER0_H

#include "DIO_Interface.h"

/*----TIMER0_Modes----*/
#define TIMER0_Normal_Mode 0
#define TIMER0_PWM_Mode    1
#define TIMER0_CTC_Mode    2
#define TIMER0_FPWM_Mode   3

/*----Clock Selection----*/
#define TIMER0_No_Clock              0
#define TIMER0_No_Prescaling         1
#define TIMER0_Prescaling_8          2
#define TIMER0_Prescaling_64         3
#define TIMER0_Prescaling_256        4
#define TIMER0_Prescaling_1024       5
#define TIMER0_EXT_Clock_FallEdge    6
#define TIMER0_EXT_Clock_RiseEdge    7

/*----Interrupt Enable----*/
#define TOV0_Interrupt_EN 1
#define OCF0_Interrupt_EN 2

/*----COM_nonPWM----*/
#define TIMER0_OC0_disconnected   0
#define TIMER0_Toggle_OC0_on_COMP 1
#define TIMER0_Clear_OC0_on_COMP  2
#define TIMER0_Set_OC0_on_COMP    3

/*----COM_PWM----*/
#define TIMER0_noninverting_mode  0
#define TIMER0_inverting_mode     1

/*----Functions Declaration----*/

void init_TIMER0 (uint8 TIMER0_Mode , uint8 TIMER0_ClockSelect);
void TIMER0_Interrupt_EN(uint8 enable); //whether it is the interrupt from TOV or OCF 
void TIMER0_COMP_VAL(uint8 value);
void TIMER0_CompareMode_nonPWM (uint8 Mode, uint8 COMP_value); //is not recommended to use Normal Mode, since this will occupy too much of the CPU time
void TIMER0_CompareMode_PWM (uint8 Mode, uint8 COMP_value);

#endif	/* MTIMER0_H */

