/* 
 * File:   mTIMER2.h
 * Author: Moustafa Yasser
 *
 * Created on December 17, 2024, 10:27 AM
 */

#ifndef MTIMER2_H
#define	MTIMER2_H

#include "DIO_Interface.h"

/*----TIMER0_Modes----*/
#define TIMER2_Normal_Mode 0
#define TIMER2_PWM_Mode    1
#define TIMER2_CTC_Mode    2
#define TIMER2_FPWM_Mode   3

/*----Clock Selection----*/
#define TIMER2_No_Clock              0
#define TIMER2_No_Prescaling         1
#define TIMER2_Prescaling_8          2
#define TIMER2_Prescaling_64         3
#define TIMER2_Prescaling_256        4
#define TIMER2_Prescaling_1024       5
#define TIMER2_EXT_Clock_FallEdge    6
#define TIMER2_EXT_Clock_RiseEdge    7

/*----Interrupt Enable----*/
#define TOV2_Interrupt_EN  64
#define OCF2_Interrupt_EN  128

/*----COM_nonPWM----*/
#define TIMER2_OC2_disconnected   0
#define TIMER2_Toggle_OC2_on_COMP 1
#define TIMER2_Clear_OC2_on_COMP  2
#define TIMER2_Set_OC2_on_COMP    3

/*----COM_PWM----*/
#define TIMER2_noninverting_mode  0
#define TIMER2_inverting_mode     1

/*----Functions Declaration----*/

void init_TIMER2(uint8 TIMER2_Mode , uint8 TIMER2_ClockSelect);
void TIMER2_Interrupt_EN(uint8 enable); //whether it is the interrupt from TOV or OCF 
void TIMER2_COMP_VAL(uint8 value);
void TIMER2_CompareMode_nonPWM (uint8 Mode, uint8 COMP_value); //is not recommended to use Normal Mode, since this will occupy too much of the CPU time
void TIMER2_CompareMode_PWM (uint8 Mode, uint8 COMP_value);

#endif	/* MTIMER2_H */

