// PURPOSE: Waits for the sound command system to reach a requested tick.
// The tick is supplied by the caller.
// It drains replies and requests command processing while waiting.

typedef unsigned int u32;

extern int func_020210c0(u32 tick);
extern int Sound_CommandReceiveAndReply(int command);
extern void SoundInternal_RequestCommandProc(void);

void func_02021154(u32 tick)
{
    int command;

    if (func_020210c0(tick)) {
        return;
    }

    command = 0;
    while (Sound_CommandReceiveAndReply(command) != 0) {
    }

    if (func_020210c0(tick)) {
        return;
    }

    SoundInternal_RequestCommandProc();

    if (func_020210c0(tick)) {
        return;
    }

    command = 1;
    do {
        Sound_CommandReceiveAndReply(command);
    } while (func_020210c0(tick) == 0);
}
