/*
PURPOSE: Processes every pending transfer in the global transfer queue.
The function removes queued entries one at a time and handles each entry.
Afterward, it subtracts the entry's transfer size from the queue's total.
*/

typedef unsigned short u16;
typedef unsigned int u32;

typedef struct StructTEQSub {
    int command;
    void *destination;
    u32 offset;
    u32 size;
} StructTEQSub;

typedef struct StructTEQ {
    StructTEQSub *entries;
    int capacity;
    u16 readIndex;
    u16 writeIndex;
    u16 count;
    u16 padding_0e;
    u32 queuedSize;
} StructTEQ;

extern StructTEQ data_02173220;

extern StructTEQSub *StructTEQ_GetTopUsedTEQSub(StructTEQ *queue);
extern int StructTEQ_TryPopTEQSub(StructTEQ *queue);
extern void StructTEQSub_HandleTEQSub(StructTEQSub *entry);

void HandleAllGlobalTEQSubs(void)
{
    StructTEQ *queue = &data_02173220;
    StructTEQSub *entry = StructTEQ_GetTopUsedTEQSub(queue);

    if (!StructTEQ_TryPopTEQSub(queue)) {
        return;
    }

    u32 *queuedSize = &queue->queuedSize;

    do {
        StructTEQSub_HandleTEQSub(entry);
        *queuedSize -= entry->size;
        entry = StructTEQ_GetTopUsedTEQSub(queue);
    } while (StructTEQ_TryPopTEQSub(queue));
}
