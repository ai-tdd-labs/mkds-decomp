/* PURPOSE: Initializes the race HUD models and animation lookup tables.
 *
 * Loads the main, cloud, lap-count, and final-lap billboard resources. It also
 * builds five sampled motion tables and creates the two model/animation sets
 * used by the HUD. The setup is skipped for scene 6.
 */

typedef unsigned short u16;
typedef long long fx64;

typedef struct RaceConfig {
    int field_00;
    int field_04;
    int field_08;
    int sceneId;
} RaceConfig;

typedef struct BillboardModel {
    unsigned char unknown_00[0x14];
    unsigned int flags;
} BillboardModel;

typedef struct HudModelResource {
    void *modelName;
    void *animationName1;
    void *animationName2;
} HudModelResource;

typedef struct HudModelSlot {
    void *model;
    void *animation1;
    void *animation2;
    int field_0c;
} HudModelSlot;

typedef struct LapBillboardSlot {
    unsigned char unknown_00[0x0c];
    BillboardModel *model;
} LapBillboardSlot;

extern RaceConfig *gRaceConfig;

extern char data_0216c374[];
extern char data_0216c384[];
extern char data_0216c394[];
extern char data_0216c3a4[];
extern char data_0216c3b4[];
extern char data_0216c3c4[];
extern HudModelResource data_0216c324[];

extern short data_0215d4b4[];
extern short *data_0217b8a0;
extern short *data_0217b8a4;
extern short *data_0217b8a8;
extern short *data_0217b8e0;
extern int data_0217b8e8;
extern short *data_0217b904;

extern BillboardModel data_0217ba00;
extern BillboardModel data_0217ba2c;
extern LapBillboardSlot data_0217bae8[];
extern BillboardModel *data_0217baf4;
extern BillboardModel *data_0217bb04;
extern HudModelSlot data_0217bb08[];

extern void *GetActiveExecutionContext(void);
extern void *ExecutionContext_GetHeapHandle(void *context);
extern void *Mem_AllocateHeap(void *heap, unsigned int size);
extern void *find_buf_fn_from_thumb(void *name);
extern fx64 Multiply64(fx64 left, fx64 right);

extern void BillboardModel_CreateFromNsbmdNsbtp_from_thumb(
    BillboardModel *destination, void *modelBuffer, void *textureBuffer,
    int parameters);
extern void BillboardModel_AllocateFromNsbmdNsbtp_from_thumb(
    BillboardModel **destination, void *modelBuffer, void *textureBuffer,
    int parameters);
extern void BillboardModel_SomeFn(BillboardModel *model);
extern void Model_CreateFromNsbmd(void *model, void *modelBuffer);
extern void Model_SetPolygonIdLightFlagsEmi(void *model, int polygonId,
                                             int lightFlags, int emission);
extern void Model_SetCullMode(void *model, int mode);
extern void SomeAnimationLoadWrapper_from_thumb(int animationType, void *model,
                                                 void *animation,
                                                 void *modelBuffer,
                                                 void *animationBuffer);
extern void Animation_SetLoop(void *animation, int index, int loop);

void func_020e7460(void)
{
    void *heap;
    void *mainModelBuffer;
    void *mainTextureBuffer;
    void *cloudModelBuffer;
    void *hudModelBuffer;
    void *lapModelBuffer;
    void *lapTextureBuffer;
    int angle;
    int sample;
    int tableIndex;
    short sine;
    HudModelResource *resource;
    HudModelSlot *slot;
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
            (short)(Multiply64((fx64)sine, 0x4cLL) >> 12);

        sine = data_0215d4b4[((u16)(angle + 0xa218) >> 4) * 2];
        tableIndex =
            (u16)((Multiply64((fx64)sine, 0xb60b60b60bLL) +
                   0x80000000000LL) >>
                  44) >>
            4;
        data_0217b8a8[sample] = data_0215d4b4[tableIndex * 2];
        data_0217b8a0[sample] = data_0215d4b4[tableIndex * 2 + 1];

        sine = data_0215d4b4[((u16)(angle + 0x1554) >> 4) * 2];
        data_0217b8e0[sample] =
            (short)((Multiply64((fx64)sine, 0x19aLL) >> 12) + 0xe66);

        sine = data_0215d4b4[((u16)(angle + 0xbbb0) >> 4) * 2];
        data_0217b904[sample] =
            (short)((Multiply64((fx64)sine, 0x19aLL) >> 12) + 0x119a);

        angle += 0x444;
    }

    data_0217b8e8 = 0;
    resource = data_0216c324;
    slot = data_0217bb08;
    lightFlags = 2;
    for (slotIndex = 2; slotIndex < 4; slotIndex++, resource++, slot++) {
        if (resource->modelName != 0) {
            slot->model = Mem_AllocateHeap(heap, 0x6c);
            hudModelBuffer = find_buf_fn_from_thumb(resource->modelName);
            Model_CreateFromNsbmd(slot->model, hudModelBuffer);
            Model_SetPolygonIdLightFlagsEmi(slot->model, 0x3f, lightFlags,
                                             0x294a);
            Model_SetCullMode(slot->model, 3);
        } else {
            slot->model = 0;
        }

        if (resource->animationName1 != 0) {
            slot->animation1 = Mem_AllocateHeap(heap, 0x38);
            SomeAnimationLoadWrapper_from_thumb(
                0, slot->model, slot->animation1, hudModelBuffer,
                find_buf_fn_from_thumb(resource->animationName1));
            Animation_SetLoop(slot->animation1, 0, 1);
        } else {
            slot->animation1 = 0;
        }

        if (resource->animationName2 != 0) {
            slot->animation2 = Mem_AllocateHeap(heap, 0x38);
            SomeAnimationLoadWrapper_from_thumb(
                4, slot->model, slot->animation2, hudModelBuffer,
                find_buf_fn_from_thumb(resource->animationName2));
            Animation_SetLoop(slot->animation2, 0, 1);
        } else {
            slot->animation2 = 0;
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
