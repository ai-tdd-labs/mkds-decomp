/*
PURPOSE: Reserves the next slot in a transfer queue.
This returns zero when the queue is full and one after reserving a slot.
It advances the queue's validated index and increments its pending count.
*/

typedef unsigned short u16;

typedef struct StructTEQ {
    unsigned char unknown_00[0xA];
    u16 validatedIndex;
    u16 pendingCount;
} StructTEQ;

extern int StructTEQ_IsTEQSubListFull(StructTEQ *queue);
extern u16 StructTEQ_IncrementValidateIndex(StructTEQ *queue, u16 index);

int StructTEQ_ReserveTEQSub(StructTEQ *queue)
{
    if (StructTEQ_IsTEQSubListFull(queue)) {
        return 0;
    }

    queue->validatedIndex =
        StructTEQ_IncrementValidateIndex(queue, queue->validatedIndex);
    queue->pendingCount++;
    return 1;
}
