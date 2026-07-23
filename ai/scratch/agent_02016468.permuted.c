// PURPOSE: Adds a transfer request to the global transfer queue.

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
    unsigned short readIndex;
    unsigned short writeIndex;
    unsigned short count;
    unsigned short padding_0e;
    u32 queuedSize;
} StructTEQ;

extern StructTEQ data_02173220;

extern int StructTEQ_IsTEQSubListFull(StructTEQ *queue);
extern StructTEQSub *StructTEQ_GetNextFreeTEQSub(StructTEQ *queue);
extern int StructTEQ_ReserveTEQSub(StructTEQ *queue);

int AllocateReserveTEQSub(int command, u32 offset, void *destination, u32 size)
{
    StructTEQ *queue = &data_02173220;
    StructTEQSub *entry;

    if (StructTEQ_IsTEQSubListFull(queue)) {
        return 0;
    }

    entry = StructTEQ_GetNextFreeTEQSub(queue);
    entry->command = command;
    entry->destination = destination;
    entry->offset = offset;
    entry->size = size;
    StructTEQ_ReserveTEQSub(queue);
    queue->queuedSize += entry->size;
    return 1;
}
