#include "game_timer.h"
#include "constants.h"

volatile int timer_tick = 0;

XTmrCtr timer;
//XScuGic GIC;
void timerInterruptHandler(void *userParam, u8 TmrCtrNumber) {

	timer_tick = 1; // flag for main loop


}

void init_game_timer(){
	
	XTmrCtr_Initialize (&timer, XPAR_AXI_TIMER_0_DEVICE_ID);
	XTmrCtr_SetHandler(&timer, ( XTmrCtr_Handler ) timerInterruptHandler, ( void*) 0x12345678 );
	XScuGic_Connect (&GIC, TIMER_INT_ID, ( Xil_InterruptHandler ) XTmrCtr_InterruptHandler, &timer);
	XScuGic_Enable (&GIC, TIMER_INT_ID );
	XScuGic_SetPriorityTriggerType (&GIC, TIMER_INT_ID, 0x0, 0x3 );
	XTmrCtr_SetOptions (&timer, 0, XTC_INT_MODE_OPTION | XTC_AUTO_RELOAD_OPTION);
	XTmrCtr_SetResetValue (&timer, 0, TIMER_RESET_VALUE); // defined in constants.h
	XTmrCtr_Start(&timer,0);

}
