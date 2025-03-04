#include <avr/io.h>
#include "DIO_Interface.h"


void DIO_SET_PORT_DIR(volatile uint8* PORTx , uint8 DIR){
    
    *(PORTx-1)=DIR;  
    
    /*switch(PORT){
            case 'A':      
                DDRA= DIR;
                break;
            
            case 'B':
                DDRB= DIR;
                break;

            case 'C':
                DDRC= DIR;
                break;
            case 'D':
                DDRD= DIR;
                break;
                
            default:
                //if invalid port is passed
                break;
    }*/
}




void DIO_SET_PIN_DIR(volatile uint8* PORTx , uint8 PIN, uint8 DIR){
    if(PIN>7){
        //invalid pin is passed
        return;
    }
    PORTx--;  
    
    switch(DIR){
        case OUTPUT :
            
            *PORTx |=(1<<PIN);
            break;
            
            /*switch(PORT){
                case 'A':
                    DDRA |= (1<<PIN);
                    break;
            
                case 'B':
                    DDRB |= (1<<PIN);
                    break;

                case 'C':
                    DDRC |= (1<<PIN);
                    break;
                
                case 'D':
                    DDRD |= (1<<PIN);
                    break;
                
                default:
                    //if invalid port is passed
                    break;
            }
            break;  */
            
        case INPUT :
            
            *PORTx &= ~(1<<PIN);
            break;
            
            /*switch(PORT){
                case 'A':
                    DDRA &= ~(1<<PIN);
                    break;
            
                case 'B':
                    DDRB &= ~(1<<PIN);
                    break;

                case 'C':
                    DDRC &= ~(1<<PIN);
                    break;
                
                case 'D':
                    DDRD &= ~(1<<PIN);
                    break;
                
                default:
                    //if invalid port is passed
                    break;
            }
            break; */
        
        default :
            // if invalid dir is passed
            break;
    }
    
    
}



void DIO_SET_PORT_VALUE(volatile uint8* PORTx  , uint8 Val){
    
    *PORTx=Val;
    
    /*switch(PORT){
            case 'A':      
                PORTA= Val;
                break;
            
            case 'B':
                PORTB= Val;
                break;

            case 'C':
                PORTC= Val;
                break;
            case 'D':
                PORTD= Val;
                break;
                
            default:
                //if invalid port is passed
                break;
    }  */
}



void DIO_SET_PIN_VALUE(volatile uint8* PORTx , uint8 PIN, uint8 Val ){
    if(PIN>7){
        //invalid pin is passed
        return;
    }
    
    switch(Val){
        case HIGH :
            *PORTx |= (1<<PIN);
            break;
            
            /*switch(PORT){
                case 'A':
                    PORTA |= (1<<PIN);
                    break;
            
                case 'B':
                    PORTB |= (1<<PIN);
                    break;

                case 'C':
                    PORTC |= (1<<PIN);
                    break;
                
                case 'D':
                    PORTD |= (1<<PIN);
                    break;
                
                default:
                    //if invalid port is passed
                    break;
            }
            break;  */
            
        case LOW :
            *PORTx &= ~(1<<PIN);
            break;
            
            /*switch(PORT){
                case 'A':
                    PORTA &= ~(1<<PIN);
                    break;
            
                case 'B':
                    PORTB &= ~(1<<PIN);
                    break;

                case 'C':
                    PORTC &= ~(1<<PIN);
                    break;
                
                case 'D':
                    PORTD &= ~(1<<PIN);
                    break;
                
                default:
                    //if invalid port is passed
                    break;
            }
            break; */
        
        default :
            // if invalid val is passed
            break;
    }
}



void DIO_READ_PORT(volatile uint8* PORTx, uint8* Val){
    *Val= *(PORTx-2);
    
    /*switch(PORT){
            case 'A': 
                //*Val= *(PORT-2);
                *Val=PINA;
                break;
            
            case 'B':
                *Val=PINB;
                break;

            case 'C':
                *Val=PINC;
                break;
            case 'D':
                *Val=PIND;
                break;
                
            default:
                //if invalid port is passed
                break;
    } */
}




void DIO_READ_PIN(volatile uint8* PORTx, uint8 PIN, uint8* Val){
    if(PIN>7){
        //invalid pin is passed
        return;
    }
    PORTx-=2;
    
    *Val= (*PORTx &= (1<<PIN)) ? HIGH : LOW;
    
    /*switch(PORT){
            case 'A':      
                *Val=(PINA & (1<<PIN)) ? HIGH : LOW;
                break;
            
            case 'B':
                *Val=(PINB & (1<<PIN)) ? HIGH : LOW;
                break;

            case 'C':
                *Val=(PINC & (1<<PIN)) ? HIGH : LOW;
                break;
            case 'D':
                *Val=(PIND & (1<<PIN)) ? HIGH : LOW;
                break;
                
            default:
                //if invalid port is passed
                break;
    } */
}



void DIO_Toggel_PIN(volatile uint8* PORTx, uint8 PIN){
    if(PIN>7){
        //invalid pin is passed
        return;
    }
    
    *PORTx ^= (1<<PIN);
    
    /*switch(PORT){
            case 'A':      
                PORTA ^= (1<<PIN);
                break;
            
            case 'B':
                PORTB ^= (1<<PIN);
                break;

            case 'C':
                PORTC ^= (1<<PIN);
                break;
            case 'D':
                PORTD ^= (1<<PIN);
                break;
                
            default:
                //if invalid port is passed
                break;
    } */
}