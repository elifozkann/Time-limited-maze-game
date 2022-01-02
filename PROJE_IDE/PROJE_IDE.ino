/*
 * Project Name   : TIME-LIMITED MAZE GAME
 * Revision Date  : 02.01.2022
 * Author         : ELİF BEYZA ÖZKAN
 // -------------------------------------------------------------------
 Purpose          : The purpose is to enable adults to do brain training while having 
                    fun and to contribute to the development of fine motor skills of 
                    children while having fun

 // -------------------------------------------------------------------
 System Input     :
                    1) Joystick           : To control the motion of servo motors

 System Output    :
                    1) MG90S Servo Motors : To make the maze move
                    2) LED                : To show if time is up

 // --------------------------------------------------------------------
 System Work      : The movement of the maze is provided by MG90S Servo Motors, 
                    servo motors are controlled by 2-axis joystick, and whenn 
                    the second value reaches 5530, a red warning is provided

 // --------------------------------------------------------------------
 */

// ----------------------------------------------------------------------

// LIBRARY
#include <Servo.h>

// DEFINITIONS  
Servo servo1;                                 // The name of the first servo motor is servo1        
Servo servo2;                                 // The name of the second servo motor is servo2
int joyX = 0;                                 // x axis is connected to the Analog 0 pin
int joyY = 1;                                 // y axis is connected to the Analog 1 pin
  
int servoVal;                                 // The name of the variable that will angle our servo motors      
int second;                                   // The name of time

// ----------------------------------------------------------------------

// SETUP CODE AREA
void setup()
{
  servo1.attach(3);                           // Servo motor 1 is connected to the Digital 3 pin
  servo2.attach(5);                           // Servo motor 2 is connected to the Digital 5 pin
  pinMode(13,OUTPUT);                         // Set the pin to be OUTPUT 
  cli();                                      // Stop interrupts for till we make the settings
  /*1. First we reset the control register to amke sure we start with everything disabled.*/
  TCCR2A = 0;                                 // Reset entire TCCR2A register
  TCCR2B = 0;                                 // Reset entire TCCR2B register
  /*2. We set the prescalar to the desired value by changing the CS10 CS12 and CS12 bits. */
  TCCR2B |= B00000111;                        
  TIMSK2 |= B00000100;                         
  /*3. We enable compare match mode on register B*/
  OCR2B = 127;                                // Finally we set compare register B to this value       
  
  sei();                                      // Enable back the interrupts
}

ISR(TIMER2_COMPB_vect){ 
  TCNT2=0;                                    // Reset Timer 2 value to 0
 second=second+1;

// If the second is equal to 5535 the led will turn on
if(second==5535)
{
digitalWrite(13,HIGH);                        // LED is on 
second=0;
 }
}
// -------------------------------------------------------------------

// MAIN CODE AREA    
void loop()
{
  servoVal = analogRead(joyX);                // To read the data from the X-axis of the joystick module and define it to the servo Value variable             
  servoVal = map(servoVal, 10, 1023, 0, 15);  // To convert the data from the joystick module between 0 and 15 degree angles
  servo1.write(servoVal);                     // To print the value we converted between 0 and 15 degree angles on the servo banana.

  servoVal = analogRead(joyY);                // To read the data from the Y-axis of the joystick module and define it to the servo Value variable
  servoVal = map(servoVal,10, 1023, 17 , 34); // To convert the data from the joystick module between 17 and 34 degree angles
  servo2.write(servoVal);                     // To print the value we converted between 17 and 34 degree angles on the servo banana.

} 
