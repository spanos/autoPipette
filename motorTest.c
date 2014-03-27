/* Name: motorTest.c
   Purpose: Simple program to test setup with 
   Author: David Spanos
   Revision: 0.1
     
   Circuit configuration:
   Internal Oscillator with I/O on PGM and PGD, osc speed = 4.0 MHz, 1 us instruction cycle
                  PIC16F1829 8SOIC Pinout:
                  __________     __________
                 |          [___]          |
       +Vbatt 1- | +5V                 GND |-20 -Ground
                 |                         |
              2- | RA5     RA0,AN0,PGD,DAC |-19
                 |                         |
              3- | RA4,AN3     RA1,AN1,PGC |-18
                 |                         |
              4- | /MCLR,RA3       RA2,AN2 |-17
                 |                         |
green LED <<< 5- | RC5, CCP1           RC0 |-16
                 |                         |
              6- | RC4                 RC1 |-15
                 |                         |
              7- | RC3                 RC2 |-14
                 |                         |
              8- | RC6                 RB4 |-13
                 |                         |
              9- | RC7                 RB5 |-12
                 |                         |
             10- | RB7                 RB6 |-11
                 |_________________________|
*/
  
  
#device PIC16F1829 ADC=8  
#include <16F1829-h.h>         // Use my own version of the 1829 header file
#include <STDLIB.H>            // look in the PIC C User Manual to see what this library contains
#include <MATH.H>              // look in the PIC C User Manual to see what this library contains
#use delay (clock=4000000)     // 4 MHz, 1 us instruction cycle, CHECK TIMING DELAYS!
#fuses INTRC_IO, NOWDT, NOMCLR, PUT
                               // Set for internal oscillator operation with RA6 and RA7 as digital I/O,
                               // Disable the WDT. Later setup WDT = 2048 ms WDT, ref 16F1829.h to find syntax
                               // Disable the /MCLR pin so that it can be used as general I/O
                               // Enable the Power-Up Timer, allows power supply to stabilize at start-up        
#define PIN_B4
#define motor2_dir PIN_B5
#define motor2_step PIN_B6
#define motor1_step PIN_B7

#define motor3_dir PIN_C0
#define motor3_step PIN_C1
#define PIN_C2
#define PIN_C3
#define PIN_C4
#define PIN_C5
#define PIN_C6             
#define motor1_dir PIN_C7
  
void motor2_fwd() {           //makes one revolution of motor 1                           
  int i;
  for (i=0; i<7; i++){
    delay_ms(10);
    Output_high(motor2_dir);
    Output_high(motor2_step);   
  }                                                        
}

void motor2_rev() {           //makes one revolution of motor 1                           
  int i;
  for (i=0; i<7; i++){
    delay_ms(10);
    Output_low(motor2_dir);
    Output_high(motor2_step);   
  }                                                        
}

void Main() {
  While(1) {
    motor2_fwd();
  }
}