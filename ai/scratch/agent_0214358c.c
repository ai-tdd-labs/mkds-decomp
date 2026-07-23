// PURPOSE: Sets two wireless manager callbacks while interrupts are protected.
// The first argument selects a callback slot, probably for a wireless event.
// It stores the two supplied pointers only when the wireless manager is ready.

typedef unsigned int u32;

typedef struct WmGlobal {
    char pad_00[0xc4];
    void *callback[16];
    void *callback2[16];
} WmGlobal;

extern u32 Os_DisableIrq(void);
extern void Os_RestoreIrq(u32 state);
extern int Wm_CheckInitialized(void);
extern WmGlobal *Wm_GetGlobal(void);

int func_0214358c(u32 index, void *callback, void *callback2)
{
    u32 state;
    int status;
    WmGlobal *global;

    state = Os_DisableIrq();
    status = Wm_CheckInitialized();
    if (status != 0) {
        Os_RestoreIrq(state);
        return status;
    }

    global = Wm_GetGlobal();
    global->callback[index] = callback;
    global->callback2[index] = callback2;
    Os_RestoreIrq(state);
    return 0;
}
