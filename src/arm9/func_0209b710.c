// PURPOSE: Gets the current length of this object's animation.

extern unsigned int Animation_GetCurrentLength(void *animation);

void func_0209b710(void *object) {
    Animation_GetCurrentLength(*(void **)((char *)object + 0x24));
    asm {
        mov r0, r0, lsl #4
        mov r0, r0, lsr #16
    }
}
