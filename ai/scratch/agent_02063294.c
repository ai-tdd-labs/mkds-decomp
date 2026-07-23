// PURPOSE: Updates the course animations that are currently enabled.

#pragma thumb off

extern unsigned char data_0217ab1c[];
extern unsigned char data_0217ab24[];
extern unsigned char data_0217ab5c[];
extern unsigned char data_0217ab94[];
extern void Animation_Update(void *animation);

asm void HandleCourseAnim(void)
{
    stmdb sp!, {lr}
    sub sp, sp, #4

    ldr r0, =data_0217ab1c
    ldrh r0, [r0, #0x20]
    cmp r0, #0
    beq skip_first
    ldr r0, =data_0217ab24
    bl Animation_Update

skip_first:
    ldr r0, =data_0217ab1c
    ldrh r0, [r0, #0x58]
    cmp r0, #0
    beq skip_second
    ldr r0, =data_0217ab5c
    bl Animation_Update

skip_second:
    ldr r0, =data_0217ab1c
    ldr r1, [r0, #4]
    cmp r1, #0
    dcd 0x028dd004
    dcd 0x08bd4000
    dcd 0x012fff1e
    ldrh r0, [r0, #0x90]
    cmp r0, #0
    dcd 0x028dd004
    dcd 0x08bd4000
    dcd 0x012fff1e
    ldr r0, =data_0217ab94
    bl Animation_Update
    add sp, sp, #4
    ldmia sp!, {lr}
    bx lr
}
