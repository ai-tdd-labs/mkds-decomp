// PURPOSE: Finalizes the buffer when its pending transfer is ready.
// The input probably holds a buffer pointer, a halfword transfer count, and a state flag.
// When the flag is ready, it writes the byte count, clears the flag, and cleans the buffer.

typedef unsigned short u16;

typedef struct TransferState {
    void *buffer;
    u16 count;
    u16 padding;
    int state;
} TransferState;

extern void DC_SomeClean(void *buffer, int size);

void func_0204a928(TransferState *transfer) {
    if (transfer->state != 1) {
        return;
    }

    *(int *)transfer->buffer = transfer->count << 1;
    transfer->state = 0;
    DC_SomeClean(transfer->buffer, 0xDCC);
}
