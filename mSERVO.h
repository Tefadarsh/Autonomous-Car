/* 
 * File:   mSERVO.h
 * Author: Moustafa Yasser
 *
 * Created on December 22, 2024, 4:12 AM
 */

#ifndef MSERVO_H
#define	MSERVO_H

#include "DIO_Interface.h"


void init_Servo();
void Servo_degree(uint8);
void Servo_btw_0to90_Smoothly();

#endif	/* MSERVO_H */

