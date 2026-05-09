#include "input.h"

#include "xuartps.h"
#include "xparameters.h"
#include "xgpio.h"
#include "xscugic.h"

#include "interrupts.h"

#define UART_BASEADDR XPAR_XUARTPS_0_BASEADDR
#define GPIO_INT_ID   XPAR_FABRIC_AXI_GPIO_0_IP2INTC_IRPT_INTR

const char cheat_code[] = "wwssadadqek";
int cheat_index = 0;

XGpio button;
volatile int button_data = 0;

void init_input(struct Input *input) {
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
    XGpio_SetDataDirection(&button, 1, 0xF);

    init_button_interrupts();
}

void buttonInterruptHandler(void *instancePointer) {
    XGpio *gpio = (XGpio *)instancePointer;

    button_data = XGpio_DiscreteRead(gpio, 1);

    XGpio_InterruptClear(gpio, XGPIO_IR_CH1_MASK);
}

void init_button_interrupts(void) {
    XGpio_InterruptEnable(&button, XGPIO_IR_CH1_MASK);
    XGpio_InterruptGlobalEnable(&button);

    XScuGic_Connect(&GIC,
                    GPIO_INT_ID,
                    (Xil_ExceptionHandler)buttonInterruptHandler,
                    &button);

    XScuGic_Enable(&GIC, GPIO_INT_ID);

    XScuGic_SetPriorityTriggerType(&GIC,
                                   GPIO_INT_ID,
                                   0x8,
                                   0x3);
}

void update_input(struct Input *input) {
    input->left = false;
    input->right = false;
    input->up = false;
    input->down = false;
    input->shoot = false;
    input->pause = false;
    input->restart = false;
    input->key_pressed = 0;

    while (XUartPs_IsReceiveData(UART_BASEADDR)) {
        char c = XUartPs_ReadReg(UART_BASEADDR, XUARTPS_FIFO_OFFSET);

        input->key_pressed = c;

        if (c == 'a' || c == 'A') input->left = true;
        else if (c == 'd' || c == 'D') input->right = true;
        else if (c == 'w' || c == 'W') input->up = true;
        else if (c == 's' || c == 'S') input->down = true;
        else if (c == ' ') input->shoot = true;
        else if (c == 'p' || c == 'P') input->pause = true;
        else if (c == 'k' || c == 'K') input->restart = true;

        if (c >= 'A' && c <= 'Z') {
            c = c + ('a' - 'A');
        }

        if (c == cheat_code[cheat_index]) {
            cheat_index++;

            if (cheat_code[cheat_index] == '\0') {
                input->cheat = true;
                cheat_index = 0;
            }
        } else {
            cheat_index = (c == cheat_code[0]) ? 1 : 0;
        }
    }


    int buttons = XGpio_DiscreteRead(&button, 1);

    if (buttons & 0x1) input->left = true;
    if (buttons & 0x2) input->right = true;
    if (buttons & 0x4) input->shoot = true;
    if (buttons & 0x8) input->pause = true;

    if ((buttons & 0x1) && (buttons & 0x2)) {
        input->cheat = true;
    }

    button_data = 0;
}
