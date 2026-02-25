/*
	----------------------------------------------------------------------
	University at Buffalo, EE379, Spring 2021	
	----------------------------------------------------------------------
	File Name: main.cc
	Description: Sample code for Lab 0 that demonstrates basic GPIO setup.
	
	Revision History:
	Date      By          Change
	----------------------------------------------------------------------
	20200128  cvfritz     Original

*/

#include <stdio.h>
#include <xgpio.h>
#define ONE_SEC 33000000

int main() {
	XGpio output;							

	int led_val = 0;
	int count = 0;

  XGpio_Initialize(&input, XPAR_AXI_GPIO_0_DEVICE_ID); // initialize input XGpio variable
	XGpio_Initialize(&output, XPAR_AXI_GPIO_1_DEVICE_ID);	// initialize output XGpio variable


  XGpio_SetDataDirection(&input, 1, 0xF);  // Swtich inputs
	XGpio_SetDataDirection(&output, 1, 0x0);		        // LED outputs, 0 = output 1 = input
	
  while (true) {
    switch_data = XGpio_DiscreteRead(&input, 1);
    if ( /*check if bit 0 is a 1 */ ) {
      // turn on LED
    }
    else {
      // turn off the LED
    }

	}

}

// to adjust speed, use count as a terminal. 
// 1. default speed 33000000
// 2. 2x fast 33000000 / 2
// 3. half speed 33000000 * 2
// 4. .25 speed 33000000 * .25

// use case statements to create a FSM w/ 4 modes
// Mode 1: Left -> Right, wrap
// Mode 2: Right -> Left, wrap
// Mode 3: Left -> Right -> Left, cont.
// Mode 4: All Flash together


