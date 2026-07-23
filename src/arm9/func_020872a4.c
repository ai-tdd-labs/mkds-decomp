// PURPOSE: Prepares and processes the racers' emblem transfer requests.
// This function allocates four temporary graphics buffers and releases them afterward.
// It initializes four transfer requests for every active racer and submits the usable ones.
// Some field meanings are probable, but the observed sizes and offsets are exact.

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
    u8 pad_14[0x10];
} TransferRequest;

typedef struct RacerEntry {
    u8 pad_00[0x0c];
    u16 racer;
    u8 pad_0e[0x0e];
    TransferRequest *requests;
    u8 pad_20[6];
    u16 indicatorColor;
} RacerEntry;

typedef struct EmblemTransferState {
    u8 pad_000[0x20];
    int racerCount;
    u8 pad_024[0xa0];
    RacerEntry *racers[8];
    u8 pad_0e4[0xa4];
    void *transferSource;
} EmblemTransferState;

extern void *data_0217aec4;
extern void *data_0217aec8;
extern void *data_0217aecc;
extern EmblemTransferState *data_0217aed0;
extern void *data_0217aed4;
extern void *data_0217aedc;

extern void *GetActiveExecutionContext(void);
extern void *ExecutionContext_GetHeapHandle(void *context);
extern void *Mem_AllocateHeapAligned(void *heap, u32 size, int alignment);
extern void Mem_FreeHeap(void *heap, void *block);
extern void SetupDriverEmblems_from_thumb(void);
extern u16 GetVsRacerIndicatorColor_from_thumb(int racer);
extern void StructAERSubSub_Fn1_Sub1_from_thumb(TransferRequest *request, int racer);
extern void StructAERSubSub_Fn1_Sub2_from_thumb(TransferRequest *request, int racer);
extern void StructAERSubSub_Fn1_Sub3_from_thumb(TransferRequest *request, int racer);
extern void StructAERSubSub_Fn1_Sub4_from_thumb(TransferRequest *request, int racer);
extern void StructAERSubSub_SomeFn_from_thumb(TransferRequest *request);

void func_020872a4(void)
{
    u16 racer;
    void *heap;

    heap = ExecutionContext_GetHeapHandle(GetActiveExecutionContext());
    SetupDriverEmblems_from_thumb();

    data_0217aedc = 0;
    data_0217aed4 = Mem_AllocateHeapAligned(heap, 0x20, -4);
    data_0217aec4 = Mem_AllocateHeapAligned(heap, 0x100, -4);
    data_0217aec8 = Mem_AllocateHeapAligned(heap, 8, -4);
    data_0217aecc = Mem_AllocateHeapAligned(heap, 0x200, -4);

    for (racer = 0; racer < data_0217aed0->racerCount; racer++) {
        RacerEntry *entry = data_0217aed0->racers[racer];
        TransferRequest *request = entry->requests;
        TransferRequest *request1 = &request[1];
        TransferRequest *request3 = &request[3];

        request->sourceSize = 0x200;
        request->copySize = 0x20;
        request->destination = data_0217aed0->transferSource;

        entry->indicatorColor = GetVsRacerIndicatorColor_from_thumb(entry->racer);
        StructAERSubSub_Fn1_Sub1_from_thumb(request, entry->racer);
        StructAERSubSub_Fn1_Sub2_from_thumb(request1, entry->racer);
        StructAERSubSub_Fn1_Sub3_from_thumb(&request[2], entry->racer);
        StructAERSubSub_Fn1_Sub4_from_thumb(request3, entry->racer);

        StructAERSubSub_SomeFn_from_thumb(request);
        StructAERSubSub_SomeFn_from_thumb(request1);
        StructAERSubSub_SomeFn_from_thumb(&entry->requests[2]);
        if (request3->source != 0) {
            StructAERSubSub_SomeFn_from_thumb(request3);
        }
    }

    Mem_FreeHeap(heap, data_0217aecc);
    Mem_FreeHeap(heap, data_0217aec8);
    Mem_FreeHeap(heap, data_0217aec4);
    Mem_FreeHeap(heap, data_0217aed4);
}
