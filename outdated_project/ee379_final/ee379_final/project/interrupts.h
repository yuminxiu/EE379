#ifndef INTERRUPTS_H
#define INTERRUPTS_H
#include "xscugic.h"
extern XScuGic GIC;

void initIntrSystem(XScuGic *IntcInstancePtr);

#endif
