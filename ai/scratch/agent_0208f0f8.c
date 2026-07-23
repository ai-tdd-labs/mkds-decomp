/* PURPOSE: Initializes the award-track effect manager.
 *
 * Selects the race-specific resource and limits, allocates the manager's
 * object pools, links every object into its owning list, and prepares the
 * loaded texture dimensions used by the effect renderer.
 */

typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

typedef struct RaceConfig_0208f0f8 {
    int courseId;
    int field_04;
    int raceType;
    int mode;
} RaceConfig_0208f0f8;

typedef struct RaceContext_0208f0f8 {
    char pad_000[0xa4];
    void *effectHeap;
} RaceContext_0208f0f8;

typedef struct IntrusiveListWrapper_0208f0f8 {
    void *first;
    void *last;
    u16 count;
    u16 linkOffset;
} IntrusiveListWrapper_0208f0f8;

typedef struct AwardTrackGroup_0208f0f8 {
    char pad_00[8];
    IntrusiveListWrapper_0208f0f8 members;
    char pad_14[0x1c];
} AwardTrackGroup_0208f0f8;

typedef struct AwardTrackInstance_0208f0f8 {
    char data[0x1c];
} AwardTrackInstance_0208f0f8;

typedef struct LoadedAwardTexture_0208f0f8 {
    char pad_00[8];
    u32 field_08;
    char pad_0c[0x20];
    u32 field_2c;
} LoadedAwardTexture_0208f0f8;

typedef struct AwardTrackManager_0208f0f8 {
    IntrusiveListWrapper_0208f0f8 activeItems;
    IntrusiveListWrapper_0208f0f8 groups;
    IntrusiveListWrapper_0208f0f8 freeItems;
    char loadedModelTexture[0xc];
    LoadedAwardTexture_0208f0f8 *texture;
    u32 field_34;
} AwardTrackManager_0208f0f8;

typedef struct AwardRenderParameters_0208f0f8 {
    union {
        u32 packedWidth;
        u16 itemsPerGroup;
    } dimensions;
    char pad_04[0x14];
    u32 scaledHeight;
    u32 unitScale;
    u32 halfScale;
} AwardRenderParameters_0208f0f8;

extern RaceConfig_0208f0f8 *gRaceConfig;
extern RaceContext_0208f0f8 *data_0217aa10;
extern AwardTrackManager_0208f0f8 *data_0217b08c;

extern u8 data_021663d8;
extern u8 data_021663dc;
extern u16 data_021663e0;
extern u16 data_021663e4;
extern int data_021663e8;
extern void (*data_021663ec)(void);
extern int data_021663f0;
extern AwardRenderParameters_0208f0f8 data_021663f4;
extern char data_02166514[];
extern char data_02166530[];

extern void func_0208ecd8(void);
extern void func_0208ee40(void);
extern void *FindFileBuffer_MAR_EFT_from_thumb(const char *path);
extern void *Mem_AllocateHeap(void *heap, unsigned int size);
extern void IntrusiveListWrapper_InitializeEmpty(
    IntrusiveListWrapper_0208f0f8 *list, int linkOffset);
extern void IntrusiveListWrapper_InsertLast(
    IntrusiveListWrapper_0208f0f8 *list, void *item);
extern void LoadedModelTexture_SomeFn(void *loadedModelTexture, void *model,
                                      void *texture);

void func_0208f0f8(void *heap)
{
    void *resource;
    u16 groupCount;
    u16 instanceCount;
    AwardTrackGroup_0208f0f8 *groups;
    AwardTrackInstance_0208f0f8 *instances;
    u16 groupIndex;
    u16 instanceIndex;
    LoadedAwardTexture_0208f0f8 *texture;
    u32 scaledWidth;
    u32 clearedWidth;

    resource = FindFileBuffer_MAR_EFT_from_thumb(
        gRaceConfig->mode == 5 ? data_02166514 : data_02166530);

    data_021663e0 = 8;
    data_021663f0 = 0x4d;
    data_021663dc = 3;
    data_021663e4 = 0xc;
    data_021663d8 = 0xe;
    data_021663e8 = 1;
    data_021663ec = func_0208ee40;

    groupCount = 1;
    if (gRaceConfig->raceType == 5) {
        groupCount += 3;
    } else if (gRaceConfig->mode == 5) {
        data_021663e0 = 0xe;
        data_021663dc = 2;
        data_021663f0 = 0;
        data_021663e4 = 0x1e;
        data_021663ec = func_0208ecd8;
        data_021663d8 = 4;
        data_021663e8 = 0;
        groupCount = 6;
    }

    instanceCount =
        (u16)(data_021663f4.dimensions.itemsPerGroup * groupCount);

    if (gRaceConfig->raceType == 4) {
        heap = data_0217aa10->effectHeap;
    }

    data_0217b08c = Mem_AllocateHeap(heap, 0x38);
    groups = Mem_AllocateHeap(heap, groupCount * 0x30);
    instances = Mem_AllocateHeap(heap, instanceCount * 0x1c);

    IntrusiveListWrapper_InitializeEmpty(&data_0217b08c->activeItems, 0);
    IntrusiveListWrapper_InitializeEmpty(&data_0217b08c->groups, 0);
    IntrusiveListWrapper_InitializeEmpty(&data_0217b08c->freeItems, 0);

    for (groupIndex = 0; groupIndex < groupCount; groupIndex++) {
        IntrusiveListWrapper_InitializeEmpty(&groups[groupIndex].members, 0);
        IntrusiveListWrapper_InsertLast(&data_0217b08c->groups,
                                        &groups[groupIndex]);
    }

    for (instanceIndex = 0; instanceIndex < instanceCount; instanceIndex++) {
        IntrusiveListWrapper_InsertLast(&data_0217b08c->freeItems,
                                        &instances[instanceIndex]);
    }

    LoadedModelTexture_SomeFn(&data_0217b08c->loadedModelTexture, resource,
                              resource);

    texture = data_0217b08c->texture;
    scaledWidth = (texture->field_08 & 0xffff) << 3;
    clearedWidth = data_021663f4.dimensions.packedWidth & 0xffff0000;
    data_021663f4.dimensions.packedWidth = clearedWidth;
    data_021663f4.dimensions.packedWidth =
        clearedWidth | ((scaledWidth >> 3) & 0xffff);
    data_021663f4.scaledHeight = (texture->field_2c & 0xffff) << 3;
    data_021663f4.unitScale = 0x10000;
    data_021663f4.halfScale = 0x8000;

    data_0217b08c->field_34 =
        gRaceConfig->courseId == 0x1d ? 0 : 0x8000;
}
