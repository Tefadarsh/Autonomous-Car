/* 
 * File:   mMotor_Driver.h
 * Author: Moustafa Yasser
 *
 * Created on January 31, 2025, 8:07 PM
 */

#ifndef MMOTOR_DRIVER_H
#define	MMOTOR_DRIVER_H

#define Motor1_Enable       0
#define Motor2_Enable       1
#define Motor_1and2_Enable  2 

#define Motor1_Disable       0
#define Motor2_Disable       1
#define Motor_1and2_Disable  2 


#define Motor1_Stop       0
#define Motor2_Stop       1
#define Motor_1and2_Stop  2


void init_MotorDriver();
void Motor_Enable(uint8 Enable);
void Motor_Disable(uint8 Disable);
void Motor_1_Rotate_CW();
void Motor_1_Rotate_CCW();
void Motor_2_Rotate_CW();
void Motor_2_Rotate_CCW();
void Motor_Stop(uint8 Motor);

#endif	/* MMOTOR_DRIVER_H */

