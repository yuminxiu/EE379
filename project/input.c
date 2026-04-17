
XGpio input;

void buttonInterruptHandler(void *instancePointer) {
	//Read the button state using XGpio_DiscreteRead
	//Set dir based on which bit is a '1'
	switch_data = XGpio_DiscreteRead(&input,1);

	int btn0 = (switch_data & 0x01); // down
	int btn1 = (switch_data & 0x02); // up
	int btn2 = (switch_data & 0x04); // right
	int btn3 = (switch_data & 0x08); // up
	
	if (btn0 == 1){ dir = 3;}
	if (btn1 == 1){dir = 2;}
	if (btn2 ==1){dir = 1;}
	if (btn3 == 1){dir = 0;}
//change if statementst to if switch_data == 1...then ....
	XGpio_InterruptClear(&input, 0xF); //Leave this line at the end of this function

}

XGpio_Initialize(&input, XPAR_AXI_GPIO_0_DEVICE_ID);
XGpio_SetDataDirection(&input, 1, 0xF); //1 = input, 0 = output
XScuGic_Connect(&GIC, GPIO_INT_ID, (Xil_ExceptionHandler) buttonInterruptHandler, &input);
XGpio_InterruptEnable (&input, XGPIO_IR_CH1_MASK);
XGpio_InterruptGlobalEnable (&input);
XScuGic_Enable (&GIC, GPIO_INT_ID);
XScuGic_SetPriorityTriggerType (&GIC, GPIO_INT_ID, 0x8, 0x3);
