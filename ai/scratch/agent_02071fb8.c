// PURPOSE: Prepares a driver to exchange race state over the network.
// The driver provides the initial position and Y rotation.
// Two tracking lists are reset and thirty history records are allocated from
// the supplied heap, then every record is placed on the free list.

typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

typedef struct VecFx32 {
    int x;
    int y;
    int z;
} VecFx32;

typedef struct IntrusiveListWrapper {
    void *head;
    void *tail;
    u16 count;
    u16 linkOffset;
} IntrusiveListWrapper;

typedef struct NetworkHistoryEntry {
    u8 data[0x24];
} NetworkHistoryEntry;

typedef struct DriverNetworkState {
    VecFx32 position;                    /* 0x00 */
    u16 yRotation;                       /* 0x0c */
    u16 previousYRotation;               /* 0x0e */
    VecFx32 previousPosition;            /* 0x10 */
    u32 field1c;                         /* 0x1c */
    u32 field20;                         /* 0x20 */
    u32 field24;                         /* 0x24 */
    u32 field28;                         /* 0x28 */
    u32 flags;                           /* 0x2c */
    u32 previousFlags;                   /* 0x30 */
    VecFx32 field34;                     /* 0x34 */
    u16 field40;                         /* 0x40 */
    u8 padding42[2];
    u32 field44;                         /* 0x44 */
    u32 field48;                         /* 0x48 */
    u8 padding4c[0x10];
    u16 field5c;                         /* 0x5c */
    u8 padding5e[2];
    u32 field60;                         /* 0x60 */
    u32 field64;                         /* 0x64 */
    u8 padding68[0x18];
    IntrusiveListWrapper activeEntries; /* 0x80 */
    IntrusiveListWrapper freeEntries;   /* 0x8c */
    VecFx32 field98;                     /* 0x98 */
    u32 fielda4;                         /* 0xa4 */
    VecFx32 fielda8;                     /* 0xa8 */
    u16 fieldb4;                         /* 0xb4 */
} DriverNetworkState;

typedef struct DriverContext {
    u8 padding00[0x80];
    VecFx32 position;                    /* 0x80 */
    u8 padding8c[0x236 - 0x8c];
    u16 yRotation;                       /* 0x236 */
    u8 padding238[0x514 - 0x238];
    DriverNetworkState *networkState;    /* 0x514 */
} DriverContext;

extern const VecFx32 data_02154f94;
extern void IntrusiveListWrapper_InitializeEmpty(
    IntrusiveListWrapper *list, int linkOffset);
extern void *Mem_AllocateHeap(void *heap, unsigned int size);
extern void IntrusiveListWrapper_InsertLast(
    IntrusiveListWrapper *list, void *item);

void DriverContext_CreateNetworkState(DriverContext *context, void *heap)
{
    VecFx32 resetVector;
    u16 entryIndex;
    DriverNetworkState *state;

    state = context->networkState;
    if (state == 0) {
        return;
    }

    state->position = context->position;
    state->previousPosition = state->position;
    state->previousYRotation = context->yRotation;
    state->yRotation = state->previousYRotation;

    entryIndex = 0;
    state->field1c = 0;
    state->field20 = 0;
    state->field24 = 0;
    state->field28 = 0;
    state->previousFlags = 0;
    state->flags = state->previousFlags;

    resetVector = data_02154f94;
    state->field34 = resetVector;
    state->field44 = 0;
    state->field48 = 0;
    state->field40 = 0;
    state->field5c = 0;
    state->field60 = 0;
    state->field64 = 0;
    state->field98 = resetVector;
    state->fielda8 = resetVector;
    state->fieldb4 = 0;

    IntrusiveListWrapper_InitializeEmpty(&state->activeEntries, entryIndex);
    IntrusiveListWrapper_InitializeEmpty(&state->freeEntries, entryIndex);

    {
        NetworkHistoryEntry *entries;
        IntrusiveListWrapper *freeList;

        entries = Mem_AllocateHeap(heap, 0x438);
        freeList = &state->freeEntries;
        do {
            IntrusiveListWrapper_InsertLast(freeList, &entries[entryIndex]);
            entryIndex++;
        } while (entryIndex < 0x1e);
    }
}
