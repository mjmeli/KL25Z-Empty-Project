/*----------------------------------------------------------------------------
 *      
 *----------------------------------------------------------------------------
 *      Name:    BLINKY.C
 *      Purpose: Bare Metal example program
 *----------------------------------------------------------------------------
 *      
 *      Copyright (c) 2006-2014 KEIL - An ARM Company. All rights reserved.
 *---------------------------------------------------------------------------*/

#include "MKL25Z4.h"                    // Device header
#include "Blinky.h"

const uint32_t led_mask[] = {1UL << 18, 1UL << 19, 1UL << 1};
unsigned int counter = 0;

/*----------------------------------------------------------------------------
  Function that initializes LEDs
 *----------------------------------------------------------------------------*/
void LED_Initialize(void) {

  SIM->SCGC5    |= (1UL <<  10) | (1UL <<  12);      /* Enable Clock to Port B & D */ 
  PORTB->PCR[18] = (1UL <<  8);                      /* Pin PTB18 is GPIO */
  PORTB->PCR[19] = (1UL <<  8);                      /* Pin PTB19 is GPIO */
  PORTD->PCR[1]  = (1UL <<  8);                      /* Pin PTD1  is GPIO */

  FPTB->PDOR = (led_mask[0] | led_mask[1] );          /* switch Red/Green LED off  */
  FPTB->PDDR = (led_mask[0] | led_mask[1] );          /* enable PTB18/19 as Output */

  FPTD->PDOR = led_mask[2];            /* switch Blue LED off  */
  FPTD->PDDR = led_mask[2];            /* enable PTD1 as Output */
}

volatile uint32_t msTicks;                            /* counts 1ms timeTicks */
/*----------------------------------------------------------------------------
  SysTick_Handler
 *----------------------------------------------------------------------------*/
void SysTick_Handler(void) {
  msTicks++;                        /* increment counter necessary in Delay() */
}

/*------------------------------------------------------------------------------
  delays number of tick Systicks (happens every 1 ms)
 *------------------------------------------------------------------------------*/
__INLINE static void Delay (uint32_t dlyTicks) {
  uint32_t curTicks;

  curTicks = msTicks;
  while ((msTicks - curTicks) < dlyTicks);
}

/*----------------------------------------------------------------------------
  Function that turns on Red LED
 *----------------------------------------------------------------------------*/
void LEDRed_On (void) {
  FPTD->PSOR   = led_mask[LED_BLUE];   /* Blue LED Off*/
  FPTB->PSOR   = led_mask[LED_GREEN];  /* Green LED Off*/
  FPTB->PCOR   = led_mask[LED_RED];    /* Red LED On*/
}

/*----------------------------------------------------------------------------
  Function that turns on Green LED
 *----------                 ------------------------------------------------------------------*/
void LEDGreen_On (void) {
  FPTB->PSOR   = led_mask[LED_RED];     /* Red LED Off*/
  FPTD->PSOR   = led_mask[LED_BLUE];    /* Blue LED Off*/
  FPTB->PCOR   = led_mask[LED_GREEN];   /* Green LED On*/
}

/*----------------------------------------------------------------------------
  Function that turns on Blue LED
 *----------------------------------------------------------------------------*/
void LEDBlue_On (void) {
  FPTB->PSOR   = led_mask[LED_GREEN];   /* Green LED Off*/
  FPTB->PSOR   = led_mask[LED_RED];     /* Red LED Off*/
  FPTD->PCOR   = led_mask[LED_BLUE];    /* Blue LED On*/
}

/*----------------------------------------------------------------------------
  Function that turns all LEDs off
 *----------------------------------------------------------------------------*/
void LED_Off (void) {
  FPTB->PSOR   = led_mask[LED_GREEN];   /* Green LED Off*/
  FPTB->PSOR   = led_mask[LED_RED];     /* Red LED Off*/
  FPTD->PSOR   = led_mask[LED_BLUE];    /* Blue LED Off*/
}

/*----------------------------------------------------------------------------
 *        Thread 1 'phaseA': Phase A output
 *---------------------------------------------------------------------------*/
void phaseA (void) {
		static unsigned int local = 0;
	  LEDRed_On();
		Delay(0x500);                     /* delay                  */
		counter++;
		if (counter > 0x0F) {
			counter = 0;
		}
		local = counter;
		local++;
}

/*----------------------------------------------------------------------------
 *        Thread 2 'phaseB': Phase B output
 *---------------------------------------------------------------------------*/
void phaseB (void) {
		LEDBlue_On();
    Delay(0x500);                          /* delay 1000ms                  */
}

/*----------------------------------------------------------------------------
 *        Thread 3 'phaseC': Phase C output
 *---------------------------------------------------------------------------*/
void phaseC (void) {
    LEDGreen_On();
    Delay(0x500);                          /* delay 1000ms                  */
}

/*----------------------------------------------------------------------------
 *        Thread 4 'phaseD': Phase D output
 *---------------------------------------------------------------------------*/
void phaseD (void) {
  	LED_Off();
    Delay(0x500);                          /* delay 1000ms                  */
}
