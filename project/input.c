#include "input.h"
#include "xuartps.h"
#include "xparameters.h"

#define UART_BASEADDR XPAR_XUARTPS_0_BASEADDR
// XPAR_PS7_UART_1_BASEADDR


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
		else if(c == 'w' || c == 'W'){
			if(c == 'w' || c == 'W'){
				if (c =='s' || c == 'S'){
					if (c =='s' || c == 'S'){
						if ( c == 'a' || c == 'A'){
							if (c == 'd' || c =='D'){
								if ( c == 'a' || c == 'A'){
									if (c == 'd' || c =='D'){
										if (c == 'q' || c =='Q'){
											if (c == 'e' || c =='E'){
												if (c == ' '){
													input->cheat = true;
												}
											}
										}
									}
								}
							}
						}
					}
				}
			}
		}
										
																													
												
								
}







// TAKEN FROM LAB 5. UNSURE IF NEEDED AT ALL, BUT MAY NEED IF UART ISNT ALREADY ENABLED ON THE BOARD
XGpio input;

void buttonInterruptHandler(void *instancePointer) {
	//Read the button state using XGpio_DiscreteRead
	//Set dir based on which bit is a '1'
	switch_data = XGpio_DiscreteRead(&input,1);


	XGpio_InterruptClear(&input, 0xF); //Leave this line at the end of this function

}

XGpio_Initialize(&input, XPAR_AXI_GPIO_0_DEVICE_ID);
XGpio_SetDataDirection(&input, 1, 0xF); //1 = input, 0 = output
XScuGic_Connect(&GIC, GPIO_INT_ID, (Xil_ExceptionHandler) buttonInterruptHandler, &input);
XGpio_InterruptEnable (&input, XGPIO_IR_CH1_MASK);
XGpio_InterruptGlobalEnable (&input);
XScuGic_Enable (&GIC, GPIO_INT_ID);
XScuGic_SetPriorityTriggerType (&GIC, GPIO_INT_ID, 0x8, 0x3);
