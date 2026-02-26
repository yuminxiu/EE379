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
	int mode = 0; // 0..3
	int dir = 1;
	int all;
	int speed = 0;
	int delay;

  XGpio_Initialize(&input, XPAR_AXI_GPIO_0_DEVICE_ID); // initialize input XGpio variable
	XGpio_Initialize(&output, XPAR_AXI_GPIO_1_DEVICE_ID);	// initialize output XGpio variable


  XGpio_SetDataDirection(&input, 1, 0xF);  // Swtich inputs
	XGpio_SetDataDirection(&output, 1, 0x0);		        // LED outputs, 0 = output 1 = input
	
  while (true) {
    switch_data = XGpio_DiscreteRead(&input, 1);
	  if (switch_data & 0x01){
		  mode++;
		  
		  if (mode == 4)
			  mode = 0;
		  led_val = 0;
		  all = 0;
		  dir = 1;
		  XGpio_DiscreteRead(&input,1) &0x01); // turn on LED
	  }
	  if (switch_data & 0x02) {
		  speed ++;
		  
	  if (speed == 3)
		  speed = 0;
		  XGpio_DiscreteRead(&input,1) &0x02);
	  }
	switch(speed){
		case 0: delay = ONE_SEC / 4;
		case 1: delay = ONE_SEC / 2;
		case 2: delay = ONE_SEC / 10;
		case 3: delay = ONE_SEC * 2;
		default: delay = ONE_SEC;
	}
	  switch(mode){
		  case 0: // Mode 1: Left -> Right, wrap
			  XGpio_DiscreteWrite(&output,1 ,(1<< led_val));
			  led_val++;
			  if (led_val == 8)
				  led_val = 0;
			  break;

		  case 1: // Mode 2: Right -> Left, wrap

			  XGpio_DiscreteWrite(&output, 1, (1 << led_val));
			  led_val --;
			  if (led_val < 0)
				  led_val = 7;
			  break;

		  case 2: // Mode 3: Back and forth
			  XGpio_DiscreteWrite(&output,1 , (1 << led_val);
			  led_val += dir;
			  if (led_val == 7)
				  dir = -1;
			  if (led_val == 0)
				  dir = 1;
			  break;

		  case 3: // All 4 together
			  all = !all;
			  if (all) {
			  XGpio_DiscreteWrite(&output,1 , 0xF);}
			  else { XGpio_DiscreteWrite(&output,1,0x0);}
	for (count = 0; count < delay; count++);
	}
return 0;
}



