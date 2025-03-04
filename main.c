/*
 * File:   main.c
 * Author: Moustafa Yasser
 *
 */


//#include <README>
#include <avr/io.h>
#define F_CPU 16000000UL 
#include <util/delay.h>
#include <avr/interrupt.h>
#include "DIO_Interface.h"
#include "mLCD4.h"
#include "mTIMER0.h"
#include "mTIMER1.h"
#include "mTIMER2.h"
#include "mSERVO.h"
#include "mUSART.h"
#include "mEEPROM.h"
#include "mMotor_Driver.h"
#include "mUltraSonic.h"



#include "FreeRTOS/Source/include/FreeRTOS.h"
#include "FreeRTOS/Source/include/FreeRTOSConfig.h"
#include "FreeRTOS/Source/include/task.h"
//#include "FreeRTOS/Source/include/queue.h"
//#include "FreeRTOS/Source/include/semphr.h"



TaskHandle_t Task1_Handler=NULL;
TaskHandle_t Task2_Handler=NULL;
TaskHandle_t Task3_Handler=NULL;
TaskHandle_t Task4_Handler=NULL;


uint8 str1[]= "Move Forward"; 
uint8 str2[]= "Move Backward";
uint8 str3[]= "Turn Right";
uint8 str4[]= "Turn Left";
uint8 str5[]= "Car Stops";
uint8 str6[]= "Rotate Right";
uint8 str7[]= "Rotate Left";


volatile uint32 counter=0;
volatile uint8 Received;
uint8 flag=1;
uint8 FLAG=0;

/*-----Functions Relative to Autonomous Car----- */

void Car_turn_left();
void Car_turn_Right();
void Car_Move_Backwards();   
void Car_Move_Forward();
void Car_Autonomous();

/*-------------------------------------------------*/


/*-----Functions Relative to Controlling the Car----- */

void ControllingCar_MoveForward();
void ControllingCar_MoveBackward();
void ControllingCar_RotateRight();
void ControllingCar_RotateLeft();
void ControllingCar_TurnRight();
void ControllingCar_TurnLeft();
void ControllingCar_Stop();

/*----------------------------------------------------*/


ISR(TIMER0_OVF_vect){
    counter++;
}


ISR(USART_RXC_vect){

     Received = USART_READFrom_UDR_Reg();

}


void Task1(void *pvParameter){
      
      init_LCD4();
      init_USART(BaudRate_Asyn_9600);
      USART_EN_INT(USART_EN_RXCIE);
      init_UltraSonic();  
      init_Servo();
      init_MotorDriver();
      TIMER0_Interrupt_EN(TOV0_Interrupt_EN);  
      sei();
      
      vTaskDelete(NULL);
    
}




void Task2(void *pvParameter){
    
    DIO_SET_PIN_DIR(&PORTD,PD3,OUTPUT);
    
    while(1){  
        
        DIO_SET_PIN_VALUE(&PORTD,PD3,HIGH);
        vTaskDelay(5); 
        DIO_SET_PIN_VALUE(&PORTD,PD3,LOW);
        vTaskDelay(15);
        
    }
}


void Task3(void *pvParameter){
    
    
    while(1){
        
        vTaskDelay(1);
   
        if(FLAG){

            Car_Autonomous();
            
            }   
    }
}



void Task4(void *pvParameter){
    
    
    while(1){
       
        if(Received != 0){
        
          switch(Received){
            case 'A':
                ControllingCar_MoveForward();
                break;
            case 'B':
                ControllingCar_MoveBackward();
                break;
            case 'C':
                ControllingCar_RotateRight();
                break;
            case 'D':
                ControllingCar_RotateLeft();
                break;
            case 'E':
                FLAG=1;                    //This case responsible for entering Autonomous car
                break;
            case 'F':
                FLAG=0;                   //This case responsible for Controlling the car
                ControllingCar_Stop();
                break;
            case 'G':
                ControllingCar_TurnRight();
                break;
            case 'H':
                ControllingCar_TurnLeft();
                break;
            case 'Y':
                ControllingCar_Stop();
                break;                 
            default:

                  break;
            }
          Received=0;
        }
        vTaskDelay(200);
 
    }
}



    int main(void) {
     
     xTaskCreate(Task1, "Initialization", 100, NULL, 3, &Task1_Handler);
     xTaskCreate(Task2, "25%ofCarMSpeed", 100, NULL, 1, &Task2_Handler);
     xTaskCreate(Task3, "AutonomousCar ", 100, NULL, 1, &Task3_Handler);
     xTaskCreate(Task4, "ControllingCar", 100, NULL, 2, &Task4_Handler);
     vTaskStartScheduler();
      
      
    while (1) {
 
    }

}


/*-----Functions Relative to Autonomous Car----- */

void Car_turn_left(){
    Motor_1_Rotate_CCW(); 
    Motor_2_Rotate_CW();  
    vTaskDelay(700);
    Motor_Stop(Motor_1and2_Stop);
}

void Car_turn_Right(){
    Motor_1_Rotate_CW(); 
    Motor_2_Rotate_CCW();  
    vTaskDelay(700);
    Motor_Stop(Motor_1and2_Stop);
}


void Car_Move_Backwards(){
    Motor_1_Rotate_CCW();
    Motor_2_Rotate_CCW();
    vTaskDelay(1000); 
    Motor_Stop(Motor_1and2_Stop);
}


void Car_Move_Forward(){
    Motor_1_Rotate_CW();
    Motor_2_Rotate_CW();
}




void Car_Autonomous(){
        uint16 Distance=UtraSonic_Distance_Measuerment();
        
        if (Distance<=45){
            
            Motor_Stop(Motor_1and2_Stop);
            LCD4_Clear();
            LCD4_WriteStr(str5);
            vTaskDelay(1000);
            Servo_degree(Servo_Turn_Left);  
            vTaskDelay(1000);
            Distance=UtraSonic_Distance_Measuerment();
            
            if(Distance>45){
                
                Servo_degree(Servo_Stay_Middle); 
                LCD4_Clear();
                LCD4_WriteStr(str4);
                vTaskDelay(1000);
                Car_turn_left();
            }
            else{
                
                Servo_degree(Servo_Turn_Right); 
                vTaskDelay(1000);
                Distance=UtraSonic_Distance_Measuerment();
                
                if(Distance>45){
                
                    Servo_degree(Servo_Stay_Middle); 
                    LCD4_Clear();
                    LCD4_WriteStr(str3);
                    vTaskDelay(1000);
                    Car_turn_Right();
                }
                else{
                    
                    flag=1;
                    while(flag){
                        
                        Servo_degree(Servo_Stay_Middle); 
                        LCD4_Clear();
                        LCD4_WriteStr(str2);
                        vTaskDelay(1000);
                        Car_Move_Backwards();
                        LCD4_Clear();
                        LCD4_WriteStr(str5);
                        Servo_degree(Servo_Turn_Left);  
                        vTaskDelay(1000);
                        Distance=UtraSonic_Distance_Measuerment();
                        
                        if(Distance>45){
                            
                            Servo_degree(Servo_Stay_Middle); 
                            LCD4_Clear();
                            LCD4_WriteStr(str4);
                            vTaskDelay(1000);
                            flag=0;
                            Car_turn_left();
                            
                        }
                        else{
                            
                            Servo_degree(Servo_Turn_Right); 
                            vTaskDelay(1000);
                            Distance=UtraSonic_Distance_Measuerment();
                            
                            if(Distance>45){
                                
                                Servo_degree(Servo_Stay_Middle);
                                LCD4_Clear();
                                LCD4_WriteStr(str3);
                                vTaskDelay(1000);
                                flag=0;
                                Car_turn_Right();
                                
                            }
                        }
                                
                        
                        
                    }
                }
            }

        }
        else{
            
            LCD4_Clear();
            LCD4_WriteStr(str1);
            Car_Move_Forward();
            
        }
        vTaskDelay(100);    
}

/*--------------------------------------------------------------------------------------*/



/*-----Functions Relative to Controlling the Car----- */

void ControllingCar_MoveForward(){
    
    LCD4_Clear();
    LCD4_WriteStr(str1);
    Car_Move_Forward();
    
}


void ControllingCar_MoveBackward(){
    
    LCD4_Clear();
    LCD4_WriteStr(str2);
    Motor_1_Rotate_CCW();
    Motor_2_Rotate_CCW();
    
}


void ControllingCar_RotateRight(){
    
    LCD4_Clear();
    LCD4_WriteStr(str6);
    Motor_1_Rotate_CW(); 
    Motor_2_Rotate_CCW(); 
    vTaskDelay(400);
    Motor_Stop(Motor_1and2_Stop);
    
}


void ControllingCar_RotateLeft(){
    
    LCD4_Clear();
    LCD4_WriteStr(str7);
    Motor_1_Rotate_CCW(); 
    Motor_2_Rotate_CW();  
    vTaskDelay(400);
    Motor_Stop(Motor_1and2_Stop);
    
}


void ControllingCar_TurnRight(){
    
    LCD4_Clear();
    LCD4_WriteStr(str3);
    Motor_1_Rotate_CW();
    Motor_Stop(Motor2_Stop);
    
}


void ControllingCar_TurnLeft(){
    
    LCD4_Clear();
    LCD4_WriteStr(str4);
    Motor_2_Rotate_CW();
    Motor_Stop(Motor1_Stop);
    
}


void ControllingCar_Stop(){
    
    LCD4_Clear();
    LCD4_WriteStr(str5);
    Motor_Stop(Motor_1and2_Stop);
    Servo_degree(Servo_Stay_Middle);    //servo gets back to the middle
}

/*----------------------------------------------------*/