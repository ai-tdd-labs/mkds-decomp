// PURPOSE: Waits until the cartridge operation can proceed safely.
// The first argument is probably an operation context and the second records lock state.
// It retries after briefly restoring interrupts when the cartridge operation requests it.

typedef unsigned short u16;
typedef unsigned int u32;

typedef struct OSLockWord {
    char pad[4];
    u16 ownerId;
} OSLockWord;

extern u32 Os_DisableIrq(void);
extern u16 Os_Lock_GetOwnerId(OSLockWord *lock);
extern int Operation_CartArm9(void *context);
extern void Os_RestoreIrq(u32 irqState);
extern void WaitByLoop(int count);

void func_0200c4c0(void *context, u32 *state)
{
    do {
        state[1] = Os_DisableIrq();
        state[0] = Os_Lock_GetOwnerId((OSLockWord *)0x027fffe8) & 0x40;
        if (state[0] != 0) {
            break;
        }
        if (Operation_CartArm9(context) == 0) {
            break;
        }
        Os_RestoreIrq(state[1]);
        WaitByLoop(1);
    } while (1);
}
