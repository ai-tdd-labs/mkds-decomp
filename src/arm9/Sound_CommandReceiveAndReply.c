// PURPOSE: Receives finished sound commands and returns them to the free list.
// The flag selects blocking or polling behavior while waiting for a reply.
// A received command chain is appended to the reusable command list.
// The function returns that chain, or zero when polling finds no reply.

typedef unsigned int u32;
typedef signed int s32;

typedef struct SoundCommandNode SoundCommandNode;

struct SoundCommandNode {
    SoundCommandNode *next;
};

extern u32 Os_DisableIrq(void);
extern u32 Os_RestoreIrq(u32 state);
extern void Os_SpinWait(u32 cycles);
extern u32 func_02021834(void);

extern SoundCommandNode *data_021732c8;
extern u32 data_021732cc;
extern SoundCommandNode *data_021732d8;
extern s32 data_021732dc;
extern s32 data_021732e4;
extern SoundCommandNode *data_021732ec[];

const SoundCommandNode *Sound_CommandReceiveAndReply(u32 flags)
{
    u32 oldirq = Os_DisableIrq();

    if (flags & 1) {
        u32 tag = func_02021834();
        while (data_021732cc == tag) {
            (void)Os_RestoreIrq(oldirq);
            Os_SpinWait(100);
            oldirq = Os_DisableIrq();
            tag = func_02021834();
        }
    } else {
        u32 tag = func_02021834();
        if (data_021732cc == tag) {
            (void)Os_RestoreIrq(oldirq);
            return 0;
        }
    }

    SoundCommandNode *queueRead = data_021732ec[data_021732dc];

    if (++data_021732dc > 8) {
        data_021732dc = 0;
    }

    SoundCommandNode *cur = queueRead;
    while (cur->next != 0) {
        cur = cur->next;
    }

    if (data_021732d8 != 0) {
        data_021732d8->next = queueRead;
    } else {
        data_021732c8 = queueRead;
    }

    data_021732d8 = cur;
    data_021732e4--;
    data_021732cc++;

    (void)Os_RestoreIrq(oldirq);
    return queueRead;
}
