typedef struct WaterEffectState {
    unsigned char unused_00[0x60];
    void *water_model_a;
    void *water_model_c;
} WaterEffectState;

extern void *GetActiveExecutionContext(void);
extern void *ExecutionContext_GetHeapHandle(void *context);
extern void *Mem_AllocateHeap(void *heap, int size);
extern void func_020d9cf4(
    int position_x,
    int position_y,
    int position_z,
    int extent_x,
    int extent_y,
    int extent_z,
    int height_limit,
    int step,
    int duration_a,
    int duration_b,
    int enabled,
    int mode,
    int speed_a,
    int speed_b,
    int loop);
extern void *FormatFindMapObjFileBuffer_from_thumb(void *name);
extern void func_020d4980(WaterEffectState *state);

extern WaterEffectState *data_0217b678;
extern int data_0216bda8;
extern int data_0216bdc4;

void func_020d9c54(void)
{
    data_0217b678 = Mem_AllocateHeap(
        ExecutionContext_GetHeapHandle(GetActiveExecutionContext()), 0x180);

    func_020d9cf4(
        0xe8000,
        0xc5000,
        0x50000,
        0x32000,
        0x3c000,
        0x7fff,
        0x3fff,
        0x1f4,
        0x12c,
        0x12c,
        1,
        5,
        10,
        10,
        1);

    data_0217b678->water_model_a =
        FormatFindMapObjFileBuffer_from_thumb(&data_0216bda8);
    data_0217b678->water_model_c =
        FormatFindMapObjFileBuffer_from_thumb(&data_0216bdc4);
    func_020d4980(data_0217b678);
}
