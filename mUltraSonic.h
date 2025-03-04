/* 
 * File:   mUltraSonic.h
 * Author: Moustafa Yasser
 *
 * Created on February 3, 2025, 6:34 PM
 */

#ifndef MULTRASONIC_H
#define	MULTRASONIC_H

#define Servo_Turn_Left    100
#define Servo_Turn_Right   167
#define Servo_Stay_Middle  225 

extern volatile uint32 counter;

void init_UltraSonic();
void UtraSonic_Trigger_Pulse();
uint16 UtraSonic_Distance_Measuerment();

#endif	/* MULTRASONIC_H */

