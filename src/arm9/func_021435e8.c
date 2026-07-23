// PURPOSE: Sets the wireless manager callback while interrupts are protected.
// The argument is probably a callback or notification pointer.
// It returns the wireless manager initialization status.
// A zero status allows the shared callback field to be updated.

typedef unsigned int u32;

typedef struct WmGlobal {
    char pad_00[0xc0];
    void *callback;
} WmGlobal;

extern u32 Os_DisableIrq(void);
extern void Os_RestoreIrq(u32 state);
extern int Wm_CheckInitialized(void);
extern WmGlobal *Wm_GetGlobal(void);

int func_021435e8(void *callback)
{
    u32 state;
    int status;

    state = Os_DisableIrq();
    status = Wm_CheckInitialized();
    if (status != 0) {
        Os_RestoreIrq(state);
        return status;
    }

    Wm_GetGlobal()->callback = callback; // Update the guarded shared field.
    Os_RestoreIrq(state);
    return 0;
}
