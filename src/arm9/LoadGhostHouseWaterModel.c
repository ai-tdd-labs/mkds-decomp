/* PURPOSE: Loads the ghost-house water model buffers.
 * Creates the shared water context and configures it with fixed water settings.
 * The exact meaning of the numeric setup values is probably renderer-specific.
 * It then finds the two model files and gives the finished context to its setup routine.
 */
typedef struct WaterContext {
    unsigned char padding_00[0x60];
    void *water_model_a; /* 0x60 */
    void *water_model_c; /* 0x64 */
} WaterContext;

extern void *GetActiveExecutionContext(void);
extern void *ExecutionContext_GetHeapHandle(void *context);
extern void *Mem_AllocateHeap(void *heap, int size);
extern void func_020d9cf4(int, int, int, int, int, int, int, int, int, int, int, int, int, int, int);
extern void *FormatFindMapObjFileBuffer_from_thumb(void *name);
extern void func_020d4980(WaterContext *context);

extern WaterContext *data_0217b678;
extern int data_0216bd14;
extern int data_0216bd2c;

void LoadGhostHouseWaterModel(void) {
    data_0217b678 = Mem_AllocateHeap(ExecutionContext_GetHeapHandle(GetActiveExecutionContext()), 0x180);

    func_020d9cf4(0, 0, 0x63000, 0x4D000,
                   0x1E000, 0x7FFF, 0x3FFF, 0x1C2,
                   0x78, 0x1E, 1, 0xF, 0x19, 0x10, 0);

    data_0217b678->water_model_a = FormatFindMapObjFileBuffer_from_thumb(&data_0216bd14);
    data_0217b678->water_model_c = FormatFindMapObjFileBuffer_from_thumb(&data_0216bd2c);
    func_020d4980(data_0217b678);
}
