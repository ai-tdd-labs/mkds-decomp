// PURPOSE: Starts a pending operation if no operation is already active.
// The two arguments are saved for the operation that is probably started here.
// Interrupts protect the active flag while it is checked and set.

typedef unsigned int u32;

typedef struct PendingOperation {
    int active;
    void *arg0;
    void *arg1;
} PendingOperation;

extern PendingOperation data_02180414;
extern u32 Os_DisableIrq(void);
extern void Os_RestoreIrq(u32 irqState);
extern int func_0214ef00(PendingOperation *operation);

int func_0214f1f4(void *arg0, void *arg1)
{
    u32 irqState = Os_DisableIrq();

    if (data_02180414.active != 0) {
        Os_RestoreIrq(irqState);
        return 1;
    }

    data_02180414.active = 1;
    Os_RestoreIrq(irqState);

    data_02180414.arg0 = arg0;
    data_02180414.arg1 = arg1;

    if (func_0214ef00(&data_02180414) != 0) {
        return 0;
    }

    return 3;
}
