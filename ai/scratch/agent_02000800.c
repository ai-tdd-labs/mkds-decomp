// PURPOSE: Starts the ARM9 and hands control to the game.
// Disables interrupts, prepares the processor modes and their stacks, and clears startup memory.
// It then initializes copied regions and static constructors before jumping to main.
// This low-level entry sequence is written as assembly because C cannot express its control-register setup.

extern void Crt0_InitializePU(void);
extern void Crt0_MemorySet32(unsigned int value, void *destination, unsigned int size);
extern void Crt0_DecompressFlushCode(void *source);
extern void Crt0_RegionCopy(void);
extern void Crt0_Reset32sAndAlphaFlags(void);
extern void NtrStartup(void);
extern void Crt0_RunInitArray(void);
extern unsigned int BuildInfo[];
extern void main(void);

asm void Entry(void)
{
    mov     ip, #0x04000000
    str     ip, [ip, #0x208]
    bl      Crt0_InitializePU
    mov     r0, #0x13
    msr     cpsr_c, r0
    ldr     r0, =0x027e0000
    add     r0, r0, #0x3fc0
    mov     sp, r0
    mov     r0, #0x12
    msr     cpsr_c, r0
    ldr     r0, =0x027e0000
    add     r0, r0, #0x3fc0
    sub     r0, r0, #0x40
    sub     sp, r0, #4
    ldr     r1, =0x00000c00
    sub     r1, r0, r1
    mov     r0, #0x1f
    msr     cpsr_fsxc, r0
    sub     sp, r1, #4
    mov     r0, #0
    ldr     r1, =0x027e0000
    mov     r2, #0x4000
    bl      Crt0_MemorySet32
    mov     r0, #0
    ldr     r1, =0x05000000
    mov     r2, #0x400
    bl      Crt0_MemorySet32
    mov     r0, #0x200
    ldr     r1, =0x07000000
    mov     r2, #0x400
    bl      Crt0_MemorySet32
    ldr     r1, =BuildInfo
    ldr     r0, [r1, #0x14]
    bl      Crt0_DecompressFlushCode
    bl      Crt0_RegionCopy
    ldr     r0, =BuildInfo
    ldr     r1, [r0, #0x0c]
    ldr     r2, [r0, #0x10]
    mov     r3, r1
    mov     r0, #0
clear_bss:
    cmp     r1, r2
    strlo   r0, [r1], #4
    blo     clear_bss
    bic     r1, r3, #0x1f
flush_bss:
    mcr     p15, 0, r0, c7, c10, 4
    mcr     p15, 0, r1, c7, c5, 1
    mcr     p15, 0, r1, c7, c14, 1
    add     r1, r1, #0x20
    cmp     r1, r2
    blt     flush_bss
    ldr     r1, =0x027fff9c
    str     r0, [r1]
    ldr     r1, =0x027e0000
    add     r1, r1, #0x3fc0
    add     r1, r1, #0x3c
    ldr     r0, =0x01ff8000
    str     r0, [r1]
    bl      Crt0_Reset32sAndAlphaFlags
    bl      NtrStartup
    bl      Crt0_RunInitArray
    ldr     r1, =main
    ldr     lr, =0xffff0000
    bx      r1
}
