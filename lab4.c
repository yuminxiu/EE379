    .global main
    .text
main:
	LDR R2, =0x41210000 //XPAR_AXI_GPIO_1_BASEADDR + XGPIO_DATA_OFFSET
	LDR R0, =0x41210004 //XPAR_AXI_GPIO_1_BASEADDR + XGPIO_TRI_OFFSET
	MOV R1, #0x00
	STR R1, [R0]		//Set direction of all pins to output
	B main_loop

delay:
	MOV R4, #0			// int R4;
delay_loop:
	ADD R4, R4, #1		// for(R4 = 0; R4 < R1; R4++);
	CMP R4, R1
	BLT delay_loop
	MOV PC, LR 			//return


RTL:
	MOV R3, #1
	STR R3, [R2] 		//turn on LED - write 1 to data register
	LDR R1, =33333333
	BL delay			//delay(333333333)
	MOV R3, #0
	STR R3, [R2]		//turn off LED - write 0 to data register
	BL delay
	MOV R3, #2
	STR R3, [R2]
	LDR R1, =33333333
	BL delay
	MOV R3, #0
	STR R3, [R2]
	BL delay
	MOV R3, #4
	STR R3, [R2]
	LDR R1, =33333333
	BL delay
	MOV R3, #0
	STR R3, [R2]
	BL delay
	MOV R3, #8
	STR R3, [R2]
	LDR R1, =33333333
	BL delay
	MOV R3, #0
	STR R3, [R2]
	BL delay
	MOV PC, LR


LTR:
	MOV R3, #8
	STR R3, [R2] 		//turn on LED - write 1 to data register
	LDR R1, =33333333
	BL delay			//delay(333333333)
	MOV R3, #0
	STR R3, [R2]		//turn off LED - write 0 to data register
	BL delay
	MOV R3, #4
	STR R3, [R2]
	LDR R1, =33333333
	BL delay
	MOV R3, #0
	STR R3, [R2]
	BL delay
	MOV R3, #2
	STR R3, [R2]
	LDR R1, =33333333
	BL delay
	MOV R3, #0
	STR R3, [R2]
	BL delay
	MOV R3, #1
	STR R3, [R2]
	LDR R1, =33333333
	BL delay
	MOV R3, #0
	STR R3, [R2]
	BL delay
	MOV PC, LR
	
BNF:
	BL RTL
	BL LTR
	B BNF

ALL:
	MOV R3, #15
	STR R3, [R2] 		//turn on LED - write 1 to data register
	LDR R1, =33333333
	BL delay			//delay(333333333)
	MOV R3, #0
	STR R3, [R2]		//turn off LED - write 0 to data register
	BL delay
	MOV PC, LR

main_loop:
	check pushbutton
	if mode == 1
	if mode == 2
	if mode == 3
	if mode == 4
	repeat

MOV r3,#1
str r3, [r2]
ldr r1, =33333333
bl delay
cmp r3, #8
lsl r3, r3, #1
B label

