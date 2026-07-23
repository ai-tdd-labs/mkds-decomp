// PURPOSE: Appends a sound command node to the interrupt-protected pending queue.
typedef unsigned int u32;

typedef struct SoundCommandNode {
    struct SoundCommandNode *next;
} SoundCommandNode;

extern u32 Os_DisableIrq(void);
extern void Os_RestoreIrq(u32 irqState);

extern SoundCommandNode *data_021732d0;
extern SoundCommandNode *data_021732d4;

void func_020213a4(SoundCommandNode *node)
{
    u32 irqState = Os_DisableIrq();
    SoundCommandNode *last = data_021732d4;

    if (last == 0) {
        data_021732d4 = node;
        data_021732d0 = node;
    } else {
        last->next = node;
        data_021732d4 = node;
    }

    node->next = 0;
    Os_RestoreIrq(irqState);
}
