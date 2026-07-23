/*
PURPOSE: Removes one queued transfer entry when the queue is not empty.
The argument is probably a transfer-entry queue with read and write indices.
On success, this advances the read index, decreases the queued-entry count,
and returns 1. If the queue is empty, it leaves the queue unchanged and returns 0.
*/

typedef unsigned short u16;

typedef struct StructTEQ {
    unsigned char unknown_00[8];
    u16 readIndex;
    u16 writeIndex;
    u16 count;
} StructTEQ;

extern int StructTEQ_IsCounterEmpty(StructTEQ *queue);
extern int StructTEQ_IncrementValidateIndex(StructTEQ *queue, u16 index);

int StructTEQ_TryPopTEQSub(StructTEQ *queue)
{
    if (StructTEQ_IsCounterEmpty(queue)) {
        return 0;
    }

    queue->readIndex = StructTEQ_IncrementValidateIndex(queue, queue->readIndex);
    queue->count--;
    return 1;
}
