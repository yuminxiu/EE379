#include "input.h"
#include "xuartps.h"
#include "xparameters.h"
#include "xgpio.h"

#define UART_BASEADDR XPAR_XUARTPS_0_BASEADDR
// XPAR_PS7_UART_1_BASEADDR

const char cheat_code[]= "wwssadadqe ";
int cheat_index = 0;
XGpio button;

void init_input(struct Input *input){
	input->left = false;
	input->right = false;
	input->up = false;
	input->down = false;
	input->shoot = false;
	input->pause = false;
	input->restart = false;
	input->key_pressed = 0;
	input->cheat = false;

	XGpio_Initialize(&button, XPAR_AXI_GPIO_0_DEVICE_ID);
	XGpio_SetDataDirection(&button, 1, 0xF); //1 = input, 0 = output
}

void update_input(struct Input *input){
	input->left = false;
	input->right = false;
	input->up = false;
	input->down = false;
	input->shoot = false;
	input->pause = false;
	input->restart = false;
	input->key_pressed = 0;
	input->cheat = false;

	if (XUartPs_IsReceiveData(UART_BASEADDR)) {
        char c = XUartPs_ReadReg(UART_BASEADDR, XUARTPS_FIFO_OFFSET);

        input->key_pressed = c;

		if ( c == 'a' || c == 'A'){
				input->left = true;
		}
		else if (c == 'd' || c =='D'){
			input->right = true;
		}

		else if (c == 'w' || c == 'W'){
			input->up = true;
		}

		else if (c =='s' || c == 'S'){
			input->down = true;
		}

		else if (c == ' '){
			input->shoot = true;
		}

		else if (c == 'p' || c == 'P'){
			input->pause = true;
		}

		else if (c == 'k' || c == 'K'){
			input->restart = true;
		}
		if (c >= 'A' && c <= 'Z') {
            c = c + ('a' - 'A'); //converts uppercase to lowercase letters
        }	

		if (c == cheat_code[cheat_index]){
			cheat_index++;

			if (cheat_code[cheat_index] == '\0'){
				input->cheat = true;
				cheat_index = 0;
			}
			else {
				cheat_index = 0;
			}
			
		}								

		int buttons = XGpio_DiscreteRead(&button,1);

		if (buttons & 0x1) input->left = true;
		if (buttons & 0x2) input->right = true;
		if (buttons & 0x4) input->shoot = true;
		if (buttons & 0x8) input->pause = true;
}


*/ void buttonInterruptHandler(void *instancePointer) {
	//Read the button state using XGpio_DiscreteRead
	//Set dir based on which bit is a '1';


	XGpio_InterruptClear(&button, 0xF); //Leave this line at the end of this function

}

XGpio_Initialize(&button, XPAR_AXI_GPIO_0_DEVICE_ID);
XGpio_SetDataDirection(&button, 1, 0xF); //1 = input, 0 = output
XScuGic_Connect(&GIC, GPIO_INT_ID, (Xil_ExceptionHandler) buttonInterruptHandler, &button);
XGpio_InterruptEnable (&button, XGPIO_IR_CH1_MASK);
XGpio_InterruptGlobalEnable (&button);
XScuGic_Enable (&GIC, GPIO_INT_ID);
XScuGic_SetPriorityTriggerType (&GIC, GPIO_INT_ID, 0x8, 0x3);
/*
