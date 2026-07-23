/* PURPOSE: Loads the bubble effect model/texture and its animation.
 * Fetches the "mkd_ef_bubble" nsbmd file, registers it via
 * func_020ea588, applies polygon-id light flags to the resulting
 * model, allocates a heap block for an animation object, loads the
 * matching nsbta texture-animation file, and finally starts the
 * animation looping via SomeAnimationLoadWrapper/Animation_SetLoop.
 * Arguments/return: none (void). */

extern void *FormatFindMapObjFileBuffer_from_thumb(void *name);
extern void func_020ea588(void *slot, void *buf, int flag);
extern void Model_SetPolygonIdLightFlagsEmi(void *model, int polygonId, int flags, int emi);
extern void *GetActiveExecutionContext(void);
extern void *ExecutionContext_GetHeapHandle(void *ctx);
extern void *Mem_AllocateHeap(void *heap, unsigned int size);
extern void SomeAnimationLoadWrapper_from_thumb(int a0, void *a1, void *a2, void *a3, void *a4);
extern void Animation_SetLoop(void *anim, int a1, int a2);

extern int data_0216bfd0; /* "mkd_ef_bubble.nsbmd" */
extern void *data_0217b770;
extern void *data_0217b778;
extern int data_0216bfe4; /* "mkd_ef_bubble.nsbta" */

void LoadBubbleEffectModel(void) {
    void *nsbmdBuf;
    void *nsbtaBuf;
    void *ctx;
    void *heap;

    nsbmdBuf = FormatFindMapObjFileBuffer_from_thumb(&data_0216bfd0);
    func_020ea588(&data_0217b770, nsbmdBuf, 0);

    Model_SetPolygonIdLightFlagsEmi(data_0217b770, 0x3f, 2, 0x294a);

    ctx = GetActiveExecutionContext();
    heap = ExecutionContext_GetHeapHandle(ctx);
    data_0217b778 = Mem_AllocateHeap(heap, 0x38);

    nsbtaBuf = FormatFindMapObjFileBuffer_from_thumb(&data_0216bfe4);

    SomeAnimationLoadWrapper_from_thumb(1, data_0217b770, data_0217b778, nsbmdBuf, nsbtaBuf);

    Animation_SetLoop(data_0217b778, 0, 1);
}
