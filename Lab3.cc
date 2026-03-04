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

int main() {
	MYDISP display;
	display.begin();
	display.clearDisplay(clrWhite);

	int cx = 120;
	int cy = 160;
	int w = 20;
	int vx - 10;
	int vy - 8;


	while(true){
		display.setForeground(clrWhite);//set foreground to white
		display.drawRectangle(bool fill, int 110, int 150, int 129, int 169);//draw rectangle centered at (cx,cy)
		if (cy <320 - w/2) cy += 5;
		display.setForeground(clrPink); //set foreground color to color the color of square
		display.drawRectangle(bool fill, int 110, int 170, int 130, int 150); //draw rectangle centered at (cx,cy)
		//wait about 0.5 sec
	}


}


