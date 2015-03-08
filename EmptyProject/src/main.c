/*----------------------------------------------------------------------------
 *      
 * Main.c
 * 
 * Main function should be located inside this file.
 *
 *---------------------------------------------------------------------------*/
 
#include "MKL25Z4.h"
#include "Blinky.h"
 
int main (void) {
	// Do not delete
	SystemCoreClockUpdate();
	 
	// Example program (safe to delete)
  LED_Initialize();           /* Initialize the LEDs           */
	SysTick_Config(10000);			//turn SysTick timer on
  while(1){
		phaseA();			//Red LED on
		phaseB();			//Blue LED on
		phaseC();			//Green LED on
		phaseD();			//all LEDs OFF
	}
}
