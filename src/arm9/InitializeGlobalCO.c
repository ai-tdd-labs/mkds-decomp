// PURPOSE: Sets up the shared race configuration memory.
// The supplied heap allocates the race configuration and its probably related data.
// It then initializes the RE and LU global systems using the same heap.

typedef struct RaceConfig {
    unsigned char unknown_000[0x3dc];
    void *unknown_3dc;
} RaceConfig;

extern void *Mem_AllocateHeap(void *heap, unsigned int size);
extern RaceConfig *gRaceConfig;
extern void InitializeGlobalRE(void *heap);
extern void InitializeGlobalLU(void *heap);

void InitializeGlobalCO(void *heap)
{
    gRaceConfig = (RaceConfig *)Mem_AllocateHeap(heap, 0x400);
    gRaceConfig->unknown_3dc = Mem_AllocateHeap(heap, 0x21);
    InitializeGlobalRE(heap);
    InitializeGlobalLU(heap);
}
