/*
PURPOSE: Creates the water effect resources for the current map object.

The argument probably describes a map object; its word at offset 0x8 is kept
with three water-effect model buffers.  The function allocates a 16-byte
resource record, stores it globally, loads the three named files, and then
initializes the completed record.
*/

typedef unsigned int u32;

typedef struct {
    unsigned char unused[8];
    void *map_object;
} WaterEffectSource;

typedef struct {
    void *map_object;
    void *nsbmd;
    void *nsbca;
    void *nsbma;
} WaterEffectResources;

extern void *GetActiveExecutionContext(void);
extern void *ExecutionContext_GetHeapHandle(void *context);
extern void *Mem_AllocateHeap(void *heap, u32 size);
extern void *FindFileBuffer_CRS_CST_from_thumb(void *name);
extern void func_020d4970(WaterEffectResources *resources);

extern WaterEffectResources *data_0217b674;
extern int data_0216bccc;
extern int data_0216bce4;
extern int data_0216bcfc;

void func_020d98a4(WaterEffectSource *source) {
    data_0217b674 = Mem_AllocateHeap(ExecutionContext_GetHeapHandle(GetActiveExecutionContext()), 0x10);
    data_0217b674->map_object = source->map_object;
    data_0217b674->nsbmd = FindFileBuffer_CRS_CST_from_thumb(&data_0216bccc);
    data_0217b674->nsbca = FindFileBuffer_CRS_CST_from_thumb(&data_0216bce4);
    data_0217b674->nsbma = FindFileBuffer_CRS_CST_from_thumb(&data_0216bcfc);
    func_020d4970(data_0217b674);
}
