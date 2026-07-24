// PURPOSE: Flushes pending sound commands and waits for the previous command list.
// Takes no arguments and returns no value.
// It preserves the current command-list value across the flush, then waits for it.

typedef unsigned int u32;

extern int func_02021114(void);
extern void Sound_FlushCommand(int flags);
extern void func_02021154(u32 tick);

void func_0212d968(void)
{
    int tick = func_02021114();

    Sound_FlushCommand(1);
    func_02021154(tick);
}
