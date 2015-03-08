/*----------------------------------------------------------------------------
 *      
 *----------------------------------------------------------------------------
 *      Name:    BLINKY.H
 *      Purpose: Bare Metal example program header
 *----------------------------------------------------------------------------
 *      
 *      Copyright (c) 2006-2014 KEIL - An ARM Company. All rights reserved.
 *---------------------------------------------------------------------------*/

#define LED_NUM     3                   /* Number of user LEDs                */
#define LED_RED    0
#define LED_GREEN  1
#define LED_BLUE	 2
#define LED_A      0
#define LED_B      1
#define LED_C      2
#define LED_D      3
#define LED_CLK    4

void LED_Initialize(void);
void SysTick_Handler(void);
void phaseA (void);
void phaseB (void);
void phaseC (void);
void phaseD (void);
