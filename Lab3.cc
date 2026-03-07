/*
	----------------------------------------------------------------------
	University at Buffalo, EE379, Spring 2020
	----------------------------------------------------------------------
	File Name: Lab3.cc
	Description: Strating point for Lab 3 code - include MTDS libraries.

	Revision History:
	Date      By          Change
	----------------------------------------------------------------------
	20200707  cvfritz     Original

*/

#include <MyDisp.h>
#include <xgpio.h>
#define clrPink 0x00FFC0CBul


int main() {
	MYDISP display;
	display.begin();
	display.clearDisplay(clrWhite);

	XGpio input;
	int cx = 120;
	int cy = 160;
	int w = 20;
	int vx = 10;
	int vy = 8;
	int delay = 300000;
	int count = 0;
	int switch_data;
	int mode = 0;
	uint32_t color;
	int edge = 0;
	int shape = 0;
	MDFNG finger0;

	 XGpio_Initialize(&input, XPAR_AXI_GPIO_0_DEVICE_ID); // initialize input XGpio variable


	  XGpio_SetDataDirection(&input, 1, 0xF);  // Switch inputs


	while(true){
		switch_data = XGpio_DiscreteRead(&input, 1);
		int btn0 = (switch_data & 0x01);

		if (btn0){
			mode++;
		}
		if (mode > 3){
			mode = 0;
		}

		switch(mode){
		case 0: color = clrPink; break;
		case 1: color = clrCyan; break;
		case 2: color = clrMagenta; break;
		case 3: color = clrYellow; break;

		}

		//////////////////////////////////////////////////
		
		display.clearDisplay(clrWhite);//set foreground to white		
		cy += vy;
		cx += vx;
		edge = 0; 
		
		if ((cx <= w/2 || cx >= 240 - w/2)){
			vx = -vx;
			edge = 1;
		}
		
		if ((cy <= w/2 || cy >= 320 - w/2)){
			vy = -vy;
			edge = 1;
		}
//// change shape on edge touch
		if (edge){
			shape++;
			if (shape > 5){
				shape = 0;
			}
		}
		
		display.setForeground(color); //set foreground color to color the color of square
		switch(shape){
			case 0: display.drawRectangle(true, cx-10, cy-10, cx+10, cy+10); break; // square
			case 1:
				display.drawRectangle(true,cx-2,cy-10,cx+2,cy+10);
				display.drawRectangle(true,cx-10,cy-2,cx+10,cy+2);
				break; // cross
			case 2: display.drawEllipse(true, cx, cy, 10, 10); break; // circle
			case 3:
					display.drawEllipse(true, cx, cy, 10, 10);
					display.setForeground(clrWhite);
					display.drawEllipse(true, cx+4, cy, 10, 10);
					display.setForeground(color);
			break;
			case 4:
				display.drawLine(cx-10, cy, cx+10, cy);
				display.drawLine(cx, cy-10, cx, cy+10);
				display.drawLine(cx-7, cy-7, cx+7, cy+7);
				display.drawLine(cx-7, cy+7, cx+7, cy-7);
			break;
			case 5:
				display.drawEllipse(cx-10, cy-10, cx, cy);
				display.drawEllipse(cx, cy-10, cx+10, cy);
				display.drawRectangle(true, cx-10, cy-5, cx+10, cy+10);
			break;
		}
	
		
		for(count =0; count < delay; count ++);
	}


}

// Trapezoid
			// P = a + b1 + c + b2
			// A = 1/2h(b1+b2)

//plus sign
			//drawRectangle(true,cx-2,cy-20,cx+2,cy+20);
			//drawRectangle(true,cx-20,cy-2,cx+20,cy+2);


/// replace btn w/following for touch display. place at top of the loop

display.checkTouch();
display.getFinger(0, &finger0);

if (finger.st == FINGER_DOWN){
	mode ++;
	if (mode > 3){
		mode = 0;
	}
}






