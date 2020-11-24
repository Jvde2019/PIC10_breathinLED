
/******************************************************************************/
/* \file structcmd.h                                                          */
/* \brief A Documented file.                                                  */
/* Details.                                                                   */
/*                                                                            */
/* ********* BreathingLED  PIC10F206  ****************                        */
/* IDE:           MPLAB X 3.65                                                */ 
/* Compiler:      XC8 V1.38                                                   */
/* File:          main.c                                                      */ 
/* Project:       2017 11 Nr. 002                                             */
/* Tested Device: PIC10F206                                                   */
/* DeviceID:                                                                  */
/* DeviceID_Rev:                                                              */ 
/*                                                                            */
/* Author: jm                                                                 */
/* This Software is free for private use. Any commercial use is prohibited.   */
/* you free to redistribute it or modify the code way you wish.               */ 
/*                                                                            */
/*                                                                            */
/* The author will not be responsible for any loss or liability whatsoever.   */
/* In any circumstances jm shall not be liable for any                        */
/* special, incidental or consequential damages, for any reason whatsoever.   */
/* No guarantee or warranty whatsoever.                                       */
/* UNTER VERWENDUNG VON CODETEILEN AUS:                                       */                                       
/******************************************************************************/

/******************************************************************************/
/* Includes                                                                   */
/******************************************************************************/
#include <xc.h>
#include <stdint.h>        // Includes uint16_t definition                
#include <stdbool.h>       // Includes true/false definition                  

/******************************************************************************/
/* Constants                                                                  */
/******************************************************************************/
#define FALSE 0
#define TRUE  1
#define _XTAL_FREQ 40000000
#define LED1       GPIObits.GP0    // Pin5 (PDIP8)
#define LED2       GPIObits.GP1    // Pin4 (PDIP8)

/******************************************************************************/
/* Global Variables                                                           */
/* Variables uintxxx Types needs <stdint.h>                                   */
/******************************************************************************/       
uint8_t LEDDuty = 0, delay =0, delayset= 3 ; 
bool    incDuty = 1;

/******************************************************************************/
/* Main Program                                                               */
/******************************************************************************/

/* TODO <INSERT USER APPLICATION CODE HERE> */

void init(){
   OPTION    = 0xC4 ;   //C3 --> 4,2 C4 --> 8,4ms PWM Periode, pull-ups disable
   CMCON0    = 0    ;   // GP0, GP1 - digital
   TRISGPIO  = 0x0c ;   // GP0, GP1 - Output
}//init

void pwm(void){    
   
    if (TMR0 == 1){                    // timeroverflow StartPWM Period
        LED1 = 1;   
        LED2 = 0;
        delay ++;                      // delayset Anzahl wieoft ein PWM-Wert
        if (delay >= delayset) {       // ausgegeben wird
            delay = 0;
          if (incDuty){                // if 1 Puls --> verlängern 
            LEDDuty++;
            if (LEDDuty >= 253) {      // Maximpuls ?
               incDuty = !incDuty;     // andere Richtung
            }      
          }
          else  {                      // Puls --> verkürzen  
            LEDDuty--;
            if (LEDDuty <= 2) {        // Minimpuls ?
               incDuty = !incDuty;     // switch Direction
            }
          }
        }
    }  
    if (TMR0 == LEDDuty){
        LED1 = 0;
        LED2 = 1;
    }    
   }//pwm
   
   
int main(void)
{
   init(); 
   while(1)
     {   
       pwm();     
    }
}//main

// (-:  !! NO CODE behind this !! :-)
