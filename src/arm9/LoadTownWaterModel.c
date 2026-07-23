/*
PURPOSE: Loads the town water model buffers.

The function probably creates the shared water context for the town course.
It allocates the context, passes fixed water settings to the setup routine,
loads the two named model files, and stores their buffers in the context.
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
extern int data_0216bd58;
extern int data_0216bd6c;

void LoadTownWaterModel(void) {
    data_0217b678 = Mem_AllocateHeap(ExecutionContext_GetHeapHandle(GetActiveExecutionContext()), 0x180);

    func_020d9cf4(0, 0, 0x29000, 0x1E000,
                   0xB000, 0x4E20, 0x3FFF, 0x12C,
                   0x78, 0x1E, 1, 0xD, 0x19, 0x10, 0);

    data_0217b678->water_model_a = FormatFindMapObjFileBuffer_from_thumb(&data_0216bd58);
    data_0217b678->water_model_c = FormatFindMapObjFileBuffer_from_thumb(&data_0216bd6c);
    func_020d4980(data_0217b678);
}
