/* PURPOSE: Counts the sound commands in a waiting list.
 * This function takes no arguments and returns the number of linked entries.
 * It disables interrupts while walking the list so the sound system cannot
 * change the list during the count, then restores the previous IRQ state. */

typedef unsigned int u32;

typedef struct SoundCommandNode {
    struct SoundCommandNode *next;
} SoundCommandNode;

extern u32 Os_DisableIrq(void);
extern void Os_RestoreIrq(u32 irqState);
extern SoundCommandNode *data_021732d0;

int func_02021040(void)
{
    u32 irqState = Os_DisableIrq();
    SoundCommandNode *command = data_021732d0;
    int count = 0;

    while (command != 0) {
        command = command->next;
        count++;
    }

    Os_RestoreIrq(irqState);
    return count;
}
