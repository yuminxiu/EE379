#ifndef INTERRUPTS_H
#define INTERRUPTS_H

extern XScuGic GIC;

void initIntrSystem(XScuGic *IntcInstancePtr);

#endif
