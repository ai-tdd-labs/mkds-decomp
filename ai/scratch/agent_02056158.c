// PURPOSE: Creates the global AA04 work block for the current race.
// The heap argument supplies memory for the work block.
// A larger aligned buffer is probably needed for race modes three and five.
// The work fields are reset before the block is used.

typedef unsigned char u8;
typedef unsigned short u16;

typedef struct RaceConfig {
    int field_0x0;
    int field_0x4;
    int field_0x8;
    int mode;
} RaceConfig;

typedef struct GlobalAA04 {
    int field_0x0;
    void *buffer;
    u16 field_0x8;
    u8 field_0xa;
    u8 pad_0xb;
    int field_0xc;
} GlobalAA04;

extern RaceConfig *gRaceConfig;
extern GlobalAA04 *data_0217aa04;
extern int data_02175614;
extern void *Mem_AllocateHeap(void *heap, unsigned int size);
extern void *Mem_AllocateHeapAligned(void *heap, unsigned int size,
                                    int alignment);

void InitializeGlobalAA04(void *heap)
{
    data_0217aa04 = Mem_AllocateHeap(heap, 0x10);

    if (gRaceConfig->mode == 3 || gRaceConfig->mode == 5) {
        data_0217aa04->buffer = Mem_AllocateHeapAligned(heap, 0x400, 0x20);
    } else {
        data_0217aa04->buffer = 0;
    }

    data_0217aa04->field_0x8 = 0;
    data_0217aa04->field_0xa = 0;
    data_0217aa04->field_0xc = 0x1000;
    data_0217aa04->field_0x0 = 0;

    if (data_02175614 == 0) {
        data_0217aa04->field_0x0 = 0;
    }
}
