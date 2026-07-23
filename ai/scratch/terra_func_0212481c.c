/* Copies each referenced metatile region to its TEQ reservation and marks its
 * source page in the destination entry.  It then reserves contiguous marked
 * source pages.  The original is an unusually register-sensitive Thumb body. */

#pragma thumb on

extern void CellBank_GetMetatileEntry(void);
extern void Arm_FlushRange(void);
extern void AllocateReserveTEQSub(void);
extern void data_0215d024(void);

asm void func_0212481c(void)
{
    push {r4, r5, r6, r7, lr}
    sub sp, #0x2c
    str r2, [sp]
    str r3, [sp, #4]
    ldr r2, [sp, #0x40]
    add r2, #8
    lsl r0, r0, #3
    add r2, r2, r0
    add r0, r1, #0
    ldr r1, [r2, #4]
    lsl r1, r1, #0x10
    lsr r1, r1, #0x10
    blx CellBank_GetMetatileEntry
    str r0, [sp, #0x14]
    ldr r1, [sp, #0x50]
    add r1, #8
    ldr r0, [sp, #0x48]
    lsl r0, r0, #3
    add r1, r1, r0
    ldr r0, [sp, #0x4c]
    ldr r1, [r1, #4]
    lsl r1, r1, #0x10
    lsr r1, r1, #0x10
    blx CellBank_GetMetatileEntry
    add r6, r0, #0
    ldr r0, [sp, #0x14]
    ldrh r0, [r0]
    str r0, [sp, #8]
    mov r2, #0
    add r1, sp, #0x1c
    str r2, [sp, #0x18]
L_zero:
    ldr r0, [sp, #0x18]
    strb r0, [r1]
    add r1, r1, #1
    add r2, r2, #1
    cmp r2, #0x10
    blt L_zero
    ldr r0, [sp, #8]
    cmp r0, #0
    ble L_after_parts
    ldr r4, [sp, #0x18]
L_part:
    ldr r0, [sp, #0x14]
    ldr r1, [r0, #4]
    add r0, r1, r4
    ldrh r7, [r0, #4]
    ldr r2, [r6, #4]
    add r2, r2, r4
    ldrh r3, [r2, #4]
    ldr r2, =0x3ff
    and r3, r2
    lsl r2, r3, #5
    str r2, [sp, #0xc]
    ldrh r0, [r0, #2]
    lsl r2, r0, #0x10
    ldr r0, =0xc0000000
    and r2, r0
    lsr r0, r2, #0x1e
    ldrh r2, [r1, r4]
    ldr r1, =0xc000
    and r2, r1
    lsr r1, r2, #0xe
    lsl r2, r1, #2
    ldr r1, =data_0215d024
    add r0, r1, r0
    ldrb r0, [r2, r0]
    lsl r5, r0, #5
    ldr r0, [sp]
    ldr r0, [r0, #0x14]
    add r2, r7, #0
    ldr r1, [pc, #0xb8]
    and r2, r1
    lsl r1, r2, #5
    add r0, r0, r1
    str r0, [sp, #0x10]
    add r1, r5, #0
    blx Arm_FlushRange
    ldr r0, [sp, #0x44]
    cmp r0, #0
    bne L_part_alt
    mov r0, #0x13
    ldr r1, [sp, #0xc]
    ldr r2, [sp, #0x10]
    add r3, r5, #0
    blx AllocateReserveTEQSub
    b L_mark
L_part_alt:
    mov r0, #0x23
    ldr r1, [sp, #0xc]
    ldr r2, [sp, #0x10]
    add r3, r5, #0
    blx AllocateReserveTEQSub
L_mark:
    ldr r0, =0xf000
    and r7, r0
    lsr r0, r7, #0xc
    mov r2, #1
    add r1, sp, #0x1c
    strb r2, [r1, r0]
    ldr r1, [r6, #4]
    add r3, r1, r4
    ldrh r2, [r3, #4]
    ldr r1, =0xffff0fff
    and r2, r1
    strh r2, [r3, #4]
    ldr r1, [r6, #4]
    add r2, r1, r4
    ldrh r1, [r2, #4]
    lsl r0, r0, #0xc
    orr r1, r0
    strh r1, [r2, #4]
    add r4, r4, #6
    ldr r0, [sp, #0x18]
    add r1, r0, #1
    str r1, [sp, #0x18]
    ldr r0, [sp, #8]
    cmp r1, r0
    blt L_part
L_after_parts:
    mov r1, #0
    add r0, r1, #0
    add r4, r1, #0
    add r5, sp, #0x1c
    mov r7, #0xe
    add r6, r1, #0
L_run:
    ldrb r2, [r5]
    cmp r2, #0
    beq L_flush
    add r2, r1, r0
    cmp r2, #0xf
    bge L_flush
    add r0, r0, #1
    b L_next
L_flush:
    cmp r0, #0
    ble L_no_run
    lsl r1, r1, #5
    ldr r2, [sp, #4]
    ldr r2, [r2, #0xc]
    add r2, r2, r1
    lsl r3, r0, #5
    ldr r0, [sp, #0x44]
    cmp r0, #0
    bne L_flush_alt
    add r0, r7, #0
    blx AllocateReserveTEQSub
    b L_reset
L_flush_alt:
    mov r0, #0x1e
    blx AllocateReserveTEQSub
L_reset:
    add r1, r4, #1
    add r0, r6, #0
    b L_next
L_no_run:
    add r1, r4, #1
L_next:
    add r5, r5, #1
    add r4, r4, #1
    cmp r4, #0x10
    blt L_run
    add sp, #0x2c
    pop {r4, r5, r6, r7}
    pop {r3}
    bx r3
    mov r8, r8
}
