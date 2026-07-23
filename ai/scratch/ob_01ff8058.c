/* func_01ff8058 == OS_IrqHandler_ThreadSwitch (NitroSDK, ITCM)
 * Source: pokediamond/arm9/lib/NitroSDK/src/OS_irqHandler.c
 * Hand-written ARM asm in the original SDK ("asm void" function) - not
 * regular C. Transcribed straight from the target disassembly; matches the
 * pokediamond source almost verbatim except the first few instructions are
 * reordered (2005-vs-2006 NitroSDK revision difference between games).
 */
#pragma thumb off

extern int OSi_IrqThreadQueue;
extern int OSi_ThreadInfo;
extern void Arm_MathContext_Save(void);
extern void Arm_MathContext_Load(void);

asm void func_01ff8058(void)
{
    mov r2, #0x1
    mov r3, #0x0
    ldr ip, =OSi_IrqThreadQueue
    ldr ip, [ip]
    cmp ip, #0x0
    beq L_80A8
L_8070:
    str r2, [ip, #0x64]
    str r3, [ip, #0x78]
    str r3, [ip, #0x7c]
    ldr r0, [ip, #0x80]
    str r3, [ip, #0x80]
    mov ip, r0
    cmp ip, #0x0
    bne L_8070
    ldr ip, =OSi_IrqThreadQueue
    str r3, [ip]
    str r3, [ip, #0x4]
    ldr ip, =OSi_ThreadInfo
    mov r1, #0x1
    strh r1, [ip]
L_80A8:
    ldr ip, =OSi_ThreadInfo
    ldrh r1, [ip]
    cmp r1, #0x0
    ldreq pc, [sp], #0x4
    mov r1, #0x0
    strh r1, [ip]
    mov r3, #0xd2
    msr CPSR_c, r3
    add r2, ip, #0x8
    ldr r1, [r2]
L_80D0:
    cmp r1, #0x0
    ldrneh r0, [r1, #0x64]
    cmpne r0, #0x1
    ldrne r1, [r1, #0x68]
    bne L_80D0
    cmp r1, #0x0
    bne L_80F8
L_80EC:
    mov r3, #0x92
    msr CPSR_c, r3
    ldr pc, [sp], #0x4
L_80F8:
    ldr r0, [ip, #0x4]
    cmp r1, r0
    beq L_80EC
    ldr r3, [ip, #0xC]
    cmp r3, #0x0
    beq L_8120
    stmdb sp!, {r0, r1, ip}
    mov lr, pc
    bx r3
    ldmia sp!, {r0, r1, ip}
L_8120:
    str r1, [ip, #0x4]
    mrs r2, SPSR
    str r2, [r0, #0x0]!
    stmdb sp!, {r0, r1}
    add r0, r0, #0x0
    add r0, r0, #0x48
    ldr r1, =Arm_MathContext_Save
    blx r1
    ldmia sp!, {r0, r1}
    ldmib sp!, {r2, r3}
    stmib r0!, {r2, r3}
    ldmib sp!, {r2, r3, ip, lr}
    stmib r0!, {r2-r14}^
    stmib r0!, {lr}
    mov r3, #0xd3
    msr CPSR_c, r3
    stmib r0!, {sp}
    stmdb sp!, {r1}
    add r0, r1, #0x0
    add r0, r0, #0x48
    ldr r1, =Arm_MathContext_Load
    blx r1
    ldmia sp!, {r1}
    ldr sp, [r1, #0x44]
    mov r3, #0xd2
    msr CPSR_c, r3
    ldr r2, [r1, #0x0]!
    msr SPSR_fc, r2
    ldr lr, [r1, #0x40]
    ldmib r1!, {r0-r14}^
    nop
    stmda sp!, {r0, r1, r2, r3, ip, lr}
    ldmia sp!, {pc}
}
