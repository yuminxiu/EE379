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
#define clrPink 0x00FFC0CBul
#define ONE_SEC 33000000


int main() {
	MYDISP display;
	display.begin();
	display.clearDisplay(clrWhite);


	int cx = 120;
	int cy = 160;
	int w = 20;
	int vx = 10;
	int vy = 8;
	int delay = ONE_SEC/2;
	int count = 0;


	while(true){
		display.setForeground(clrWhite);//set foreground to white
		display.drawRectangle(true, cx-10, cy-10, cx+9, cy+9);
		cy += vy;
		cx += vx;
		//display.drawRectangle(true, 110, 150, 129, 169);//draw rectangle centered at (cx,cy)
		if ((cx < 0 || cx > 240 - w/2)) vx = -vx;
		if ((cy < 0|| cy > 320 - w/2)) vy = -vy;
		display.setForeground(clrPink); //set foreground color to color the color of square
		display.drawRectangle(true, cx-10, cy-10, cx+9, cy+9);

		//display.drawRectangle(true, 110, 170, 130, 150); //draw rectangle centered at (cx,cy)
		for(count =0; count < delay; count ++);
	}


}

// Trapezoid
			// P = a + b1 + c + b2
			// A = 1/2h(b1+b2)

//plus sign
			//drawRectangle(true,118,140,122,180);
			//drawRectangle(true,100,158,140,162);

