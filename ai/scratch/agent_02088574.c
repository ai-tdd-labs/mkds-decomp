/* PURPOSE: Builds the model path for a kart tire.
 *
 * Formats the base path, tire directory, caller-supplied tire name, and
 * NSBMD extension into the shared path buffer before returning that buffer.
 * The original body is hand-written ARM so its vararg register order is kept.
 */
#pragma thumb off

extern char *data_02165ac8;
extern char *data_0217af24;
extern char gSharedPathBuffer[];
extern char data_02165f44[];
extern char data_02165f4c[];
extern int _snprintf(char *buf, unsigned int len, const char *fmt, ...);

asm void FormatKartTireNsbmdPath(void)
{
    stmdb sp!, {lr}
    sub sp, sp, #0xc
    ldr r0, =data_02165ac8
    ldr r3, =data_02165f44
    ldr r2, [r0]
    ldr r0, =data_0217af24
    str r2, [sp]
    str r1, [sp, #4]
    str r3, [sp, #8]
    ldr r3, [r0]
    ldr r0, =gSharedPathBuffer
    ldr r2, =data_02165f4c
    mov r1, #0x100
    bl _snprintf
    ldr r0, =gSharedPathBuffer
    add sp, sp, #0xc
    ldmia sp!, {lr}
    bx lr
}
