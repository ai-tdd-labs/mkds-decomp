// PURPOSE: Loads the models and animations used by map-object effects.
// The heap argument supplies memory for the shared effect-model manager.
// Race and course settings select limits, resources, and an optional wave model.

typedef unsigned short u16;

typedef struct RaceConfig_0208e570 {
    int courseId;
    int field_04;
    int mode;
} RaceConfig_0208e570;

typedef struct RaceContext_0208e570 {
    char pad_000[0xa4];
    void *effectHeap;
} RaceContext_0208e570;

typedef struct IntrusiveListWrapper_0208e570 {
    char data[0xc];
} IntrusiveListWrapper_0208e570;

typedef struct EffectModelManager_0208e570 {
    IntrusiveListWrapper_0208e570 models;
    IntrusiveListWrapper_0208e570 modelsByKind[5];
    char pad_048[0x14];
    u16 maximumModels;
    u16 pad_05e;
} EffectModelManager_0208e570;

extern RaceConfig_0208e570 *gRaceConfig;
extern RaceContext_0208e570 *data_0217aa10;
extern EffectModelManager_0208e570 *data_0217b080;

extern u16 data_0216618c;
extern u16 data_021661b8;
extern int data_021661e4;
extern int data_0216623c;

extern char data_02166298[];
extern char data_021662b8[];
extern char data_021662d8[];
extern char data_021662f8[];
extern char data_02166318[];
extern char data_0216633c[];
extern char data_02166360[];
extern char data_02166384[];
extern char data_021663a8[];
extern char data_021663c0[];

extern void *Mem_AllocateHeap(void *heap, unsigned int size);
extern void IntrusiveListWrapper_InitializeEmpty(void *list, int itemSize);
extern void MaybeLoadExplosionManager(void *resource, u16 kind);
extern void MaybeCheckMapObjBkWaveNsbcaNsbma(void);
extern void CreateExplosionInstances(void *heap);
extern void *FindFileBuffer_MAR_EFT_from_thumb(const char *path);
extern void *FindFileBuffer_CRS_CST_from_thumb(const char *path);
extern void MaybeLoadSomeExplosion(void *heap, int kind, void *model,
                                   void *jointAnimation,
                                   void *materialAnimation,
                                   void *textureAnimation);
extern void *GetExplosionSplashWaveNsbmd_from_thumb(void);
extern void *GetExplosionSplashWaveNsbca_from_thumb(void);
extern void *GetExplosionSplashWaveNsbma_from_thumb(void);

void LoadEffectMapObjModels(void *heap)
{
    u16 kind;
    void *model;
    void *jointAnimation;
    void *materialAnimation;

    if (gRaceConfig->mode == 4) {
        heap = data_0217aa10->effectHeap;
    }

    data_0217b080 = Mem_AllocateHeap(heap, 0x60);
    IntrusiveListWrapper_InitializeEmpty(&data_0217b080->models, 0);

    for (kind = 0; kind < 5; kind++) {
        IntrusiveListWrapper_InitializeEmpty(
            &data_0217b080->modelsByKind[kind], 0);
    }

    if (gRaceConfig->mode == 5) {
        data_0216618c = 6;
        data_021661b8 = 4;
    } else {
        data_0216618c = 3;
        data_021661b8 = 1;
    }

    if (gRaceConfig->mode == 4) {
        data_0216618c = 0x14;
    }

    MaybeLoadExplosionManager(&data_021661e4, 1);
    MaybeLoadExplosionManager(&data_0216623c, 2);
    MaybeCheckMapObjBkWaveNsbcaNsbma();
    CreateExplosionInstances(heap);

    model = FindFileBuffer_MAR_EFT_from_thumb(data_02166298);
    jointAnimation = FindFileBuffer_MAR_EFT_from_thumb(data_021662b8);
    materialAnimation = FindFileBuffer_MAR_EFT_from_thumb(data_021662d8);
    MaybeLoadSomeExplosion(
        heap, 0, model, jointAnimation, materialAnimation,
        FindFileBuffer_MAR_EFT_from_thumb(data_021662f8));

    model = FindFileBuffer_MAR_EFT_from_thumb(data_02166318);
    jointAnimation = FindFileBuffer_MAR_EFT_from_thumb(data_0216633c);
    materialAnimation = FindFileBuffer_MAR_EFT_from_thumb(data_02166360);
    MaybeLoadSomeExplosion(
        heap, 1, model, jointAnimation, materialAnimation,
        FindFileBuffer_MAR_EFT_from_thumb(data_02166384));

    model = GetExplosionSplashWaveNsbmd_from_thumb();
    jointAnimation = GetExplosionSplashWaveNsbca_from_thumb();
    MaybeLoadSomeExplosion(heap, 2, model, jointAnimation,
                           GetExplosionSplashWaveNsbma_from_thumb(), 0);

    model = GetExplosionSplashWaveNsbmd_from_thumb();
    jointAnimation = GetExplosionSplashWaveNsbca_from_thumb();
    MaybeLoadSomeExplosion(heap, 4, model, jointAnimation,
                           GetExplosionSplashWaveNsbma_from_thumb(), 0);

    if (gRaceConfig->courseId == 0x17) {
        model = GetExplosionSplashWaveNsbmd_from_thumb();
        jointAnimation = FindFileBuffer_CRS_CST_from_thumb(data_021663a8);
        MaybeLoadSomeExplosion(
            heap, 3, model, jointAnimation,
            FindFileBuffer_CRS_CST_from_thumb(data_021663c0), 0);
    }

    data_0217b080->maximumModels = 0xa;
}
