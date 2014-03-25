/*
  Use RB4:7 and RC0:7 for outputs (need 12 total, 4 per motor)
*/

/* Name: motors.c
   Purpose: Control 3 stepper motors for pipette array
   Author: David Spanos
   Revision: 0.1
     
   Based off pwm21.c (BMME 580 S13)   
   Use PCM 14 bit compiler
   See PIC16F1829 manual p. 217, 223 for PWM configuration
   See CCS C Manual p. 238-240
     
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


  
  
// SUBROUTINES
  
void init_ports(void) {
  SETUP_OSCILLATOR(OSC_4MHZ);
  SET_TRIS_C(0b00000000);      // Set PORTC<0:7> to all OUTPUTS
  SET_TRIS_A(0b00000010);      // Set PORTB<0:7> to all OUTPUTS, except for A2
  SETUP_ADC_PORTS(sAN2);       // Use AN2 (pin 17) for ADC
}
  
void init_pwm(void){
  SETUP_CCP4(CCP_PWM);
  setup_timer_2(T2_DIV_BY_1,0xc0,2);// Start timer 2.  PWM operates on timer 2 or 4.
                                    // Arguments are (prescale, period, postscale)            
  set_timer2(221);                  // Set maximum value Timer 2 will count to before toggling the output pin
                                    // 256-(0.000035/(4/4000000);
                                    // 4 mhz clock, no prescaler, set timer 2 to overflow in 35us
                                    // Must be 8 bit int                                                
  set_pwm4_duty(222);               // Set duty cycle.  222 = 100%
}
  
void init_ADC(void) {
  SETUP_ADC(ADC_CLOCK_INTERNAL);    // Fosc/4.  For 4 MHz, gives 1 us clock period.
  SET_ADC_CHANNEL(2);               // ADC reads from channel AN2 
  read_adc();
}
  
  
// PIC18F1829 goes here at RESET
  
void main() {
   init_ports();                    // Set up ports
   init_pwm();                      // Set up pulse width modulation
   init_ADC();             // Set up analog-to-digital conversion
   long voltage;
   while(1)                         // Infinite loop
   {
      delay_us(10);
      voltage = READ_ADC();
      unsigned int duty = voltage*222/256;
      set_pwm4_duty(duty);
   }
}





/**********code from syringe pump*************/
  
#define cutoff 128            // 2.5 volts
#define neutral_zone 25       // 0.5 volts
  
void motor1_fwd() {           //makes one revolution of motor 1                           
  int i;
  for (i=0; i<7; i++){
    delay_ms(10);
    Output_high(motor1_dir);
    Output_high(motor1_step);   
  }                                                        
}

void motor1_rev() {           //makes one revolution of motor 1                           
  int i;
  for (i=0; i<7; i++){
    delay_ms(10);
    Output_low(motor1_dir);
    Output_high(motor1_step);   
  }                                                        
}

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

void motor3_fwd() {           //makes one revolution of motor 1                           
  int i;
  for (i=0; i<7; i++){
    delay_ms(10);
    Output_high
    Output_high(motor1_step);   
  }                                                        
}

void motor3_rev() {           //makes one revolution of motor 1                           
  int i;
  for (i=0; i<7; i++){
    delay_ms(10);
    Output_high(motor1_step);   
  }                                                        
}
  
void Main() {
   Init_ADC();
     
   Int reading;
   motor_neut();
     
   While(1) {
      Reading = read_adc();
      If (reading<(cutoff-neutral_zone/2))
         drive(0);
      Else if (reading>(cutoff+neutral_zone/2))
         drive(2);
      Else
         drive(1);
   }
} 