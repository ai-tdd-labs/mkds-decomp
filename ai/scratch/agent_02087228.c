// PURPOSE: Copies a racer graphics buffer into its display memory.
// The request supplies transfer sizes and receives the selected buffer pointers.
// The racer index selects character graphics and palette buffers.
// During a race, the destination's first color comes from the racer color table.

typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

typedef struct TransferRequest {
    u32 unused_00;
    u32 sourceSize;
    u16 copySize;
    u8 pad_0a[2];
    void *source;
    void *destination;
} TransferRequest;

typedef struct RacerBuffers {
    u8 pad_000[0x144];
    void *flushSource[8];
    void *copySource[8];
} RacerBuffers;

extern void *data_0217aed4;
extern RacerBuffers *data_0217aed0;
extern u8 *gRaceConfig;
extern u16 data_02155a28[];

extern void Mem_CpuCopy8(const void *source, void *destination, u32 size);
extern void Arm_FlushRange(void *buffer, u32 size);

void StructAERSubSub_Fn1_Sub1_from_thumb(TransferRequest *request, int racer)
{
    void *destination = data_0217aed4;
    RacerBuffers *buffers = data_0217aed0;
    void *flushSource = buffers->flushSource[racer];
    int color;

    Mem_CpuCopy8(
        buffers->copySource[racer],
        destination,
        request->copySize);

    color = 0x7fff;
    if (((signed char *)gRaceConfig)[0x58] != 0) {
        color = data_02155a28[
            *(int *)((u8 *)gRaceConfig + racer * 0x30 + 0x74)];
    }
    *(u16 *)destination = color;

    Arm_FlushRange(destination, request->copySize);
    Arm_FlushRange(flushSource, request->sourceSize);
    request->destination = destination;
    request->source = flushSource;
}
