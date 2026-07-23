// PURPOSE: Selects the sound command variant from a flag.
/*
 * A non-null flag sends the fixed value 0x40.
 * A null flag sends the default command instead.
 */

extern void func_020208d8(void);
extern void func_02020904(void *value);

void func_0212ba34(void *flag)
{
    if (flag != 0) {
        func_02020904((void *)0x40);
        return;
    }

    func_020208d8();
}
