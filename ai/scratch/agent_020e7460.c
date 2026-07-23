// PURPOSE: Builds the race HUD models and motion tables.
// The function loads the HUD billboard resources and prepares five sampled
// lookup tables. It also creates two model-and-animation slots and probably
// skips the work in the scene that does not display the race HUD.

typedef signed short s16;
typedef unsigned short u16;
typedef signed long long s64;

typedef struct RaceConfig {
    int field_00;
    int field_04;
    int field_08;
    int sceneId;
} RaceConfig;

typedef struct BillboardModel {
    unsigned char pad_00[0x14];
    unsigned int flags;
} BillboardModel;

typedef struct HudResource {
    void *modelName;
    void *animationName0;
    void *animationName4;
} HudResource;

typedef struct HudSlot {
    void *model;
    void *animation0;
    void *animation4;
    int field_0c;
} HudSlot;

typedef struct LapBillboardSlot {
    unsigned char pad_00[0x0c];
    BillboardModel *model;
} LapBillboardSlot;

extern RaceConfig *gRaceConfig;

extern char data_0216c374[];
extern char data_0216c384[];
extern char data_0216c394[];
extern char data_0216c3a4[];
extern char data_0216c3b4[];
extern char data_0216c3c4[];
extern HudResource data_0216c324[];

extern s16 data_0215d4b4[];
extern s16 *data_0217b8a0;
extern s16 *data_0217b8a4;
extern s16 *data_0217b8a8;
extern s16 *data_0217b8e0;
extern int data_0217b8e8;
extern s16 *data_0217b904;

extern BillboardModel data_0217ba00;
extern BillboardModel data_0217ba2c;
extern LapBillboardSlot data_0217bae8[];
extern BillboardModel *data_0217baf4;
extern BillboardModel *data_0217bb04;
extern HudSlot data_0217bb08[];

extern void *GetActiveExecutionContext(void);
extern void *ExecutionContext_GetHeapHandle(void *context);
extern void *Mem_AllocateHeap(void *heap, unsigned int size);
extern void *find_buf_fn_from_thumb(void *name);
extern s64 Multiply64(s64 left, s64 right);

extern void BillboardModel_CreateFromNsbmdNsbtp_from_thumb(
    BillboardModel *model, void *nsbmd, void *nsbtp, void *config);
extern void BillboardModel_AllocateFromNsbmdNsbtp_from_thumb(
    BillboardModel **model, void *nsbmd, void *nsbtp, void *config);
extern void BillboardModel_SomeFn(BillboardModel *model);
extern void Model_CreateFromNsbmd(void *model, void *nsbmd);
extern void Model_SetPolygonIdLightFlagsEmi(
    void *model, int polygonId, int lightFlags, int emission);
extern void Model_SetCullMode(void *model, int mode);
extern void SomeAnimationLoadWrapper_from_thumb(
    int type, void *model, void *animation, void *modelBuffer,
    void *animationBuffer);
extern void Animation_SetLoop(void *animation, int index, int loop);

void func_020e7460(void)
{
    void *heap;
    void *mainModelBuffer;
    void *mainTextureBuffer;
    void *cloudModelBuffer;
    void *modelBuffer;
    void *lapModelBuffer;
    void *lapTextureBuffer;
    int angle;
    int sample;
    int tableIndex;
    s16 sine;
    HudResource *resource;
    HudSlot *slot;
    int slotIndex;
    int lightFlags;

    heap = ExecutionContext_GetHeapHandle(GetActiveExecutionContext());

    if (gRaceConfig->sceneId == 6) {
        return;
    }

    mainModelBuffer = find_buf_fn_from_thumb(data_0216c374);
    mainTextureBuffer = find_buf_fn_from_thumb(data_0216c384);
    BillboardModel_CreateFromNsbmdNsbtp_from_thumb(
        &data_0217ba2c, mainModelBuffer, mainTextureBuffer, 0);
    BillboardModel_SomeFn(&data_0217ba2c);
    data_0217ba2c.flags |= 0xc0;

    cloudModelBuffer = find_buf_fn_from_thumb(data_0216c394);
    BillboardModel_CreateFromNsbmdNsbtp_from_thumb(
        &data_0217ba00, cloudModelBuffer, 0, 0);
    BillboardModel_SomeFn(&data_0217ba00);
    data_0217ba00.flags |= 0xc0;

    data_0217b8a4 = Mem_AllocateHeap(heap, 0x78);
    data_0217b8a8 = Mem_AllocateHeap(heap, 0x78);
    data_0217b8a0 = Mem_AllocateHeap(heap, 0x78);
    data_0217b8e0 = Mem_AllocateHeap(heap, 0x78);
    data_0217b904 = Mem_AllocateHeap(heap, 0x78);

    angle = 0;
    for (sample = 0; sample < 0x3c; sample++) {
        sine = data_0215d4b4[(angle >> 4) * 2];
        data_0217b8a4[sample] =
            (s16)(Multiply64((s64)sine, 0x4cLL) >> 12);

        sine = data_0215d4b4[((u16)(angle + 0xa218) >> 4) * 2];
        tableIndex =
            (u16)((Multiply64((s64)sine, 0xb60b60b60bLL) +
                   0x80000000000LL) >>
                  44) >>
            4;
        data_0217b8a8[sample] = data_0215d4b4[tableIndex * 2];
        data_0217b8a0[sample] = data_0215d4b4[tableIndex * 2 + 1];

        sine = data_0215d4b4[((u16)(angle + 0x1554) >> 4) * 2];
        data_0217b8e0[sample] =
            (s16)((Multiply64((s64)sine, 0x19aLL) >> 12) + 0xe66);

        sine = data_0215d4b4[((u16)(angle + 0xbbb0) >> 4) * 2];
        data_0217b904[sample] =
            (s16)((Multiply64((s64)sine, 0x19aLL) >> 12) + 0x119a);

        angle += 0x444;
    }

    data_0217b8e8 = 0;
    resource = data_0216c324;
    slot = data_0217bb08;
    lightFlags = 2;

    for (slotIndex = 2; slotIndex < 4; slotIndex++, resource++, slot++) {
        if (resource->modelName != 0) {
            slot->model = Mem_AllocateHeap(heap, 0x6c);
            modelBuffer = find_buf_fn_from_thumb(resource->modelName);
            Model_CreateFromNsbmd(slot->model, modelBuffer);
            Model_SetPolygonIdLightFlagsEmi(
                slot->model, 0x3f, lightFlags, 0x294a);
            Model_SetCullMode(slot->model, 3);
        } else {
            slot->model = 0;
        }

        if (resource->animationName0 != 0) {
            slot->animation0 = Mem_AllocateHeap(heap, 0x38);
            SomeAnimationLoadWrapper_from_thumb(
                0, slot->model, slot->animation0, modelBuffer,
                find_buf_fn_from_thumb(resource->animationName0));
            Animation_SetLoop(slot->animation0, 0, 1);
        } else {
            slot->animation0 = 0;
        }

        if (resource->animationName4 != 0) {
            slot->animation4 = Mem_AllocateHeap(heap, 0x38);
            SomeAnimationLoadWrapper_from_thumb(
                4, slot->model, slot->animation4, modelBuffer,
                find_buf_fn_from_thumb(resource->animationName4));
            Animation_SetLoop(slot->animation4, 0, 1);
        } else {
            slot->animation4 = 0;
        }
    }

    lapModelBuffer = find_buf_fn_from_thumb(data_0216c3a4);
    lapTextureBuffer = find_buf_fn_from_thumb(data_0216c3b4);
    BillboardModel_AllocateFromNsbmdNsbtp_from_thumb(
        &data_0217baf4, lapModelBuffer, lapTextureBuffer, 0);
    BillboardModel_SomeFn(data_0217bae8[0].model);
    data_0217bae8[0].model->flags |= 0xc0;

    lapModelBuffer = find_buf_fn_from_thumb(data_0216c3c4);
    BillboardModel_AllocateFromNsbmdNsbtp_from_thumb(
        &data_0217bb04, lapModelBuffer, 0, 0);
    BillboardModel_SomeFn(data_0217bae8[1].model);
    data_0217bae8[1].model->flags |= 0xc0;
}
