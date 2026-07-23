// PURPOSE: Checks whether a selected metatile has flag value one.

#pragma thumb on

extern void CellBank_GetMetatileEntry(void);

asm int func_02124ae4(int index, void *cell_bank, void *records)
{
    push {lr}
    sub sp, #4
    add r2, #8
    lsl r0, r0, #3
    add r2, r2, r0
    add r0, r1, #0
    ldr r1, [r2, #4]
    lsl r1, r1, #0x10
    lsr r1, r1, #0x10
    blx CellBank_GetMetatileEntry
    ldr r0, [r0, #4]
    ldrh r1, [r0]
    ldr r0, =0xc00
    and r1, r0
    asr r0, r1, #0xa
    cmp r0, #1
    bne L_not_one
    mov r0, #1
    add sp, #4
    pop {r3}
    bx r3
L_not_one:
    mov r0, #0
    add sp, #4
    pop {r3}
    bx r3
}
