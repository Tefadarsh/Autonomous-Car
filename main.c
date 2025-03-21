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
#include "mTIMER0.h"
#include "mTIMER2.h"
#include "mUSART.h"

#include "mLCD4.h"
#include "mSERVO.h"
#include "mMotor_Driver.h"
#include "mUltraSonic.h"



#include "FreeRTOS/Source/include/FreeRTOS.h"
#include "FreeRTOS/Source/include/FreeRTOSConfig.h"
#include "FreeRTOS/Source/include/task.h"
#include "FreeRTOS/Source/include/queue.h"
//#include "FreeRTOS/Source/include/semphr.h"

QueueHandle_t xQueue=NULL;

TaskHandle_t Task1_Handler=NULL;
TaskHandle_t Task2_Handler=NULL;
TaskHandle_t Task3_Handler=NULL;
TaskHandle_t Task4_Handler=NULL;


uint8 str_MF[]= "Move Forward"; 
uint8 str_MB[]= "Move Backward";
uint8 str_TR[]= "Turn Right";
uint8 str_TL[]= "Turn Left";
uint8 str_S[] = "Car Stops";
uint8 str_RR[]= "Rotate Right";
uint8 str_RL[]= "Rotate Left";


volatile uint32 counter=0;
//volatile uint8 Received;
uint8 flag;                 //this flag used in Control part
//uint8 FLAG=0;                 //this flag used in Autonomous part

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
    
     BaseType_t xHigherPriorityTaskWoken = pdFALSE;
     
     uint8 data = USART_READFrom_UDR_Reg();
     xQueueSendFromISR(xQueue, &data, &xHigherPriorityTaskWoken);
     
     if(xHigherPriorityTaskWoken){
         portYIELD();
     }

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
        vTaskDelay(20);
        
    }
}


void Task3(void *pvParameter){
    
    
    while(1){
        
        //vTaskDelay(1);
   
        //if(FLAG){

            Car_Autonomous();
            
            //}   
    }
}



void Task4(void *pvParameter){
    
    uint8 Received;
    while(1){
       
        if(xQueueReceive(xQueue, &Received, portMAX_DELAY)==pdTRUE){
        
          switch(Received){
            case 'A':
                vTaskResume(Task2_Handler);
                ControllingCar_MoveForward();
                break;
            case 'B':
                vTaskResume(Task2_Handler);
                ControllingCar_MoveBackward();
                break;
            case 'C':
                vTaskResume(Task2_Handler);
                ControllingCar_RotateRight();
                break;
            case 'D':
                vTaskResume(Task2_Handler);
                ControllingCar_RotateLeft();
                break;
            case 'E':
                //FLAG=1;                    //This case responsible for entering Autonomous car
                vTaskResume(Task2_Handler);
                vTaskResume(Task3_Handler);
                break;
            case 'F':
                //FLAG=0;                   //This case responsible for Controlling the car
                vTaskSuspend(Task3_Handler);
                vTaskSuspend(Task2_Handler);
                ControllingCar_Stop();
                break;
            case 'G':
                vTaskResume(Task2_Handler);
                ControllingCar_TurnRight();
                break;
            case 'H':
                vTaskResume(Task2_Handler);
                ControllingCar_TurnLeft();
                break;
            case 'Y':
                vTaskSuspend(Task2_Handler);
                ControllingCar_Stop();
                break;                 
            default:

                  break;
            }
          //Received=0;
        }
        //vTaskDelay(200);
 
    }
}



    int main(void) {
     
     xTaskCreate(Task1, "Initialization", 100, NULL, 3, &Task1_Handler);
     xTaskCreate(Task2, "20%ofCarMSpeed", 100, NULL, 1, &Task2_Handler);
     xTaskCreate(Task3, "AutonomousCar ", 100, NULL, 1, &Task3_Handler);
     xTaskCreate(Task4, "ControllingCar", 100, NULL, 2, &Task4_Handler);
     
     xQueue=xQueueCreate(10, sizeof(uint8));
     
     vTaskSuspend(Task2_Handler);
     vTaskSuspend(Task3_Handler);
     
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
            LCD4_WriteStr(str_S);
            vTaskDelay(1000);
            Servo_degree(Servo_Turn_Left);  
            vTaskDelay(1000);
            Distance=UtraSonic_Distance_Measuerment();
            
            if(Distance>45){
                
                Servo_degree(Servo_Stay_Middle); 
                LCD4_Clear();
                LCD4_WriteStr(str_TL);
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
                    LCD4_WriteStr(str_TR);
                    vTaskDelay(1000);
                    Car_turn_Right();
                }
                else{
                    
                    flag=1;
                    while(flag){
                        
                        Servo_degree(Servo_Stay_Middle); 
                        LCD4_Clear();
                        LCD4_WriteStr(str_MB);
                        vTaskDelay(1000);
                        Car_Move_Backwards();
                        LCD4_Clear();
                        LCD4_WriteStr(str_S);
                        Servo_degree(Servo_Turn_Left);  
                        vTaskDelay(1000);
                        Distance=UtraSonic_Distance_Measuerment();
                        
                        if(Distance>45){
                            
                            Servo_degree(Servo_Stay_Middle); 
                            LCD4_Clear();
                            LCD4_WriteStr(str_TL);
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
                                LCD4_WriteStr(str_TR);
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
            LCD4_WriteStr(str_MF);
            Car_Move_Forward();
            
        }
        vTaskDelay(100);    
}

/*--------------------------------------------------------------------------------------*/



/*-----Functions Relative to Controlling the Car----- */

void ControllingCar_MoveForward(){
    
    LCD4_Clear();
    LCD4_WriteStr(str_MF);
    Car_Move_Forward();
    
}


void ControllingCar_MoveBackward(){
    
    LCD4_Clear();
    LCD4_WriteStr(str_MB);
    Motor_1_Rotate_CCW();
    Motor_2_Rotate_CCW();
    
}


void ControllingCar_RotateRight(){
    
    LCD4_Clear();
    LCD4_WriteStr(str_RR);
    Motor_1_Rotate_CW(); 
    Motor_2_Rotate_CCW(); 
    vTaskDelay(400);
    Motor_Stop(Motor_1and2_Stop);
    LCD4_Clear();
    LCD4_WriteStr(str_S);
    
}


void ControllingCar_RotateLeft(){
    
    LCD4_Clear();
    LCD4_WriteStr(str_RL);
    Motor_1_Rotate_CCW(); 
    Motor_2_Rotate_CW();  
    vTaskDelay(400);
    Motor_Stop(Motor_1and2_Stop);
    LCD4_Clear();
    LCD4_WriteStr(str_S);
    
}


void ControllingCar_TurnRight(){
    
    LCD4_Clear();
    LCD4_WriteStr(str_TR);
    Motor_1_Rotate_CW();
    Motor_Stop(Motor2_Stop);
    
}


void ControllingCar_TurnLeft(){
    
    LCD4_Clear();
    LCD4_WriteStr(str_TL);
    Motor_2_Rotate_CW();
    Motor_Stop(Motor1_Stop);
    
}


void ControllingCar_Stop(){
    
    LCD4_Clear();
    LCD4_WriteStr(str_S);
    Motor_Stop(Motor_1and2_Stop);
    Servo_degree(Servo_Stay_Middle);    //servo gets back to the middle
}

/*----------------------------------------------------*/