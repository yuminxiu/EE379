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
	XGpio input;
	int led_val = 0;
	int count = 0;
	int mode = 0; // 0..3
	int all;
	int speed = 0;
	int delay;
	int switch_data;

  XGpio_Initialize(&input, XPAR_AXI_GPIO_0_DEVICE_ID); // initialize input XGpio variable
  XGpio_Initialize(&output, XPAR_AXI_GPIO_1_DEVICE_ID);	// initialize output XGpio variable


  XGpio_SetDataDirection(&input, 1, 0xF);  // Switch inputs
  XGpio_SetDataDirection(&output, 1, 0x0);		        // LED outputs, 0 = output 1 = input
	

  while (true) {
    switch_data = XGpio_DiscreteRead(&input, 1);
	  if (switch_data & 0x1){
		  mode++;
	  }
		  
	  if (mode > 3){
		  mode = 0;
		  led_val = 0;
		  all = 0;
	  }
	  if (switch_data & 0x02) {
		  speed ++;
	  }
	  if (speed > 3){
		  speed = 0;
	  }
	switch(speed){
		case 0: delay = ONE_SEC / 4; break;
		case 1: delay = ONE_SEC / 2; break;
		case 2: delay = ONE_SEC / 10; break;
		case 3: delay = ONE_SEC * 2; break;
		// default: delay = ONE_SEC; break;
	}

	switch(mode){
	  case 0: // Mode 1: Left -> Right, wrap
		  for (int i = 3; i >= 0; i--){
			  led_val = (1 << i);
			  XGpio_DiscreteWrite(&output,1 ,led_val);
			  for (count = 0; count < delay; count++);
		  }
		  break;

	  case 1: // Mode 2: Right -> Left, wrap
		  for (int i = 0; i < 4; i++){
			  led_val = (1 << i);
			  XGpio_DiscreteWrite(&output,1 ,led_val);
			  for (count = 0; count < delay; count++);
		  }
		  break;

	  case 2: // Mode 3: Back and forth
		  for (int i = 3; i >= 0; i--){
			  led_val = (1 << i);
			  XGpio_DiscreteWrite(&output,1 ,led_val);
			  for (count = 0; count < delay; count++);
		  }
		  for (int i = 0; i < 4; i++){
			  led_val = (1 << i);
			  XGpio_DiscreteWrite(&output,1 ,led_val);
			  for (count = 0; count < delay; count++);
		  }
		  break;

	  case 3: // All 4 together
		  all = !all;
		  if (all) {
		  XGpio_DiscreteWrite(&output,1 , 0xF);}
		  else { XGpio_DiscreteWrite(&output,1,0x0);}
		  for (count = 0; count < delay; count++);
		  break;
  	  }

  }
  return 0;
}



