.global main
.text

main:

    LDR R2, =0x41210000
    LDR R3, =0x41210004
    LDR R6, =0x41200000

    MOV R1, #0
    STR R1, [R3]

    MOV R7, #0
    MOV R4, #1
    MOV R8, #0

main_loop:

    LDR R5, [R6]
    AND R5, R5, #1

    CMP R5, #1
    BNE run_mode

    ADD R7, R7, #1
    CMP R7, #4
    BLE run_mode

    MOV R7, #0


run_mode:

    CMP R7, #0
    BEQ mode_off

    CMP R7, #1
    BEQ mode_blink

    CMP R7, #2
    BEQ mode_shift_right

    CMP R7, #3
    BEQ mode_shift_left

    CMP R7, #4
    BEQ mode_bounce


mode_off:
    MOV R4, #0
    STR R4, [R2]
    B delay_and_repeat


mode_blink:
    EOR R4, R4, #15
    STR R4, [R2]
    B delay_and_repeat


mode_shift_right:

    LSR R4, R4, #1
    CMP R4, #0
    BNE store_led

    MOV R4, #8

store_led:
    STR R4, [R2]
    B delay_and_repeat


mode_shift_left:

    LSL R4, R4, #1
    CMP R4, #16
    BLT store_led

    MOV R4, #1
    STR R4, [R2]
    B delay_and_repeat


mode_bounce:

    STR R4, [R2]

    CMP R8, #0
    BEQ shift_right


shift_left:

    LSL R4, R4, #1
    CMP R4, #8
    BNE delay_and_repeat

    MOV R8, #0
    B delay_and_repeat


shift_right:

    LSR R4, R4, #1
    CMP R4, #1
    BNE delay_and_repeat

    MOV R8, #1


delay_and_repeat:

    LDR R1, =33333333
    BL delay
    B main_loop


delay:

    MOV R0, #0

delay_loop:

    ADD R0, R0, #1
    CMP R0, R1
    BLT delay_loop

    MOV PC, LR
