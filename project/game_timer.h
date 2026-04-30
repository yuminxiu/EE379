#ifndef GAMETIMER_H
#define GAMETIMER_H

#include "xscugic.h"
#include "xtmrctr.h"
#include "xil_types.h"


#define TIMER_INT_ID  XPAR_FABRIC_AXI_TIMER_0_INTERRUPT_INTR


#include <stdbool.h>

extern XTmrCtr timer;
extern volatile int timer_tick = 0;

void init_game_timer(XScuGic *GIC);
void timerInterruptHandler(void *userParam, u8 TmrCtrNumber);

#endif
