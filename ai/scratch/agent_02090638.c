// PURPOSE: Smoothly turns a kart's steering angle toward its requested direction.
// The kart supplies the requested steering value and driver-record index.
// Driver and course flags select the interpolation rate and may nudge the angle.
// The wrap correction probably chooses the shorter path around the 16-bit angle range.

#pragma thumb off

extern void *GetDriverEntry(int index);
extern unsigned char data_0217562a[];

asm void func_02090638(void *kart)
{
    stmdb sp!, {r4, r5, r6, lr}
    mov r4, r0
    ldrh r0, [r4, #0x24]
    bl GetDriverEntry
    ldr r1, [r0, #0x44]
    ldr r4, [r4, #0x20]
    ands r1, r1, #0x10
    mov r1, #0xb6
    mov r2, #0
    umull r5, ip, r4, r1
    mla ip, r4, r2, ip
    asr r4, r4, #0x1f
    mla ip, r4, r1, ip
    ldrne r3, =0x19a
    ldr r4, [r0, #0x78]
    mov r2, #0x800
    moveq r3, #0x52
    adds r6, r5, r2
    mov r1, #0x5c
    mul r2, r4, r1
    ldr r1, =data_0217562a
    add lr, r0, #0x200
    ldrh r4, [r1, r2]
    adc r5, ip, #0
    lsr r6, r6, #0xc
    orr r6, r6, r5, lsl #20
    and ip, r4, #0x20
    lsl ip, ip, #0x10
    ldrh r1, [lr, #0x36]
    lsl r2, r6, #0x10
    lsrs ip, ip, #0x10
    add r2, r1, r2, asr #16
    lsl r2, r2, #0x10
    addne r1, r1, #0xa0
    lsr r2, r2, #0x10
    strhne r1, [lr, #0x36]
    bne nudge_done
    and ip, r4, #0x10
    lsl ip, ip, #0x10
    lsrs ip, ip, #0x10
    subne r1, r1, #0xa0
    strhne r1, [lr, #0x36]
nudge_done:
    add r1, r0, #0x200
    ldrh r4, [r1, #0x36]
    ldr r1, =0x7fff
    subs r5, r2, r4
    rsbmi r2, r5, #0
    movpl r2, r5
    cmp r2, r1
    ble wrap_done
    cmp r5, #0
    ldrgt r1, =0xffff
    subgt r1, r1, r5
    rsbgt r5, r1, #0
    ldrle r1, =0xffff
    addle r5, r5, r1
wrap_done:
    smull r2, r1, r5, r3
    lsr r2, r2, #0xc
    orr r2, r2, r1, lsl #20
    add r1, r4, r2
    add r0, r0, #0x200
    strh r1, [r0, #0x36]
    ldmia sp!, {r4, r5, r6, lr}
    bx lr
}
