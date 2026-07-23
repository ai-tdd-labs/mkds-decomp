// PURPOSE: Saves the current state of a frame heap.
// The heap and a caller-provided state value are recorded in a new 16-byte entry.
// Returns zero when the entry cannot be allocated, otherwise links it as current.

typedef struct FrameHeapState {
    int value;
    void *previous;
    void *head;
    void *tail;
} FrameHeapState;

typedef struct FrameHeapData {
    void *previous;
    void *head;
    void *tail;
} FrameHeapData;

typedef struct FrameHeap {
    char pad[0x24];
    FrameHeapData data;
} FrameHeap;

extern void *Mem_Frame_AllocFromHead(void *heap, unsigned int size, int alignment);

int Mem_CreateFrameHeapState(FrameHeap *heap, int value)
{
    FrameHeapState *state;
    void *previous;
    FrameHeapData *data;

    data = &heap->data;
    previous = data->previous;
    state = Mem_Frame_AllocFromHead(data, 0x10, 4);
    if (state == 0) {
        return 0;
    }

    state->value = value;
    state->previous = previous;
    state->head = data->head;
    state->tail = data->tail;
    data->tail = state;

    return 1;
}
