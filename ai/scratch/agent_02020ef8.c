// PURPOSE: Removes and returns the next queued sound command.
// Interrupts are disabled while the command queue is changed.
// The tail pointer is cleared when the queue becomes empty.
// The exact command contents are probably handled by the caller.

typedef unsigned int u32;

typedef struct SoundCommandNode {
    struct SoundCommandNode *next;
} SoundCommandNode;

extern u32 Os_DisableIrq(void);
extern void Os_RestoreIrq(u32 state);
extern SoundCommandNode *data_021732c8;
extern SoundCommandNode *data_021732d8;

SoundCommandNode *Sound_AllocateCommandImpl(void)
{
    u32 irqState;
    SoundCommandNode *command;
    SoundCommandNode *next;

    irqState = Os_DisableIrq();
    command = data_021732c8;
    if (command == 0) {
        Os_RestoreIrq(irqState);
        return 0;
    }

    next = command->next;
    data_021732c8 = next;
    if (next == 0) {
        data_021732d8 = 0;
    }
    Os_RestoreIrq(irqState);
    return command;
}
