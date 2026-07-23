// PURPOSE: Loads a group of models and their named animations.
// The heap supplies storage for every model and animation object.
// The descriptor contains four resource counts followed by their base names.
// Multiple texture animations for one model share one animation object.

typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

typedef struct ModelBlock {
    u32 words[0x1b];
} ModelBlock;

typedef struct Animation {
    u32 words[0x0e];
} Animation;

typedef struct ModelBundle {
    ModelBlock *models;
    Animation *jointAnimations;
    Animation *materialAnimations;
    Animation *textureAnimations;
    u16 modelCount;
} ModelBundle;

typedef struct ModelDescriptor {
    u8 modelCount;
    u8 jointAnimationCount;
    u8 materialAnimationCount;
    u8 textureAnimationCount;
    char *names[1];
} ModelDescriptor;

extern void *Mem_AllocateHeap(void *heap, unsigned int size);
extern int _snprintf(char *buffer, unsigned int size, const char *format, ...);
extern void *find_buf_fn_from_thumb(char *path);
extern void Model_CreateFromNsbmdWithoutCullReverse(
    ModelBlock *model, void *resource);
extern void Animation_CreateFrom(
    int type, Animation *animation, ModelBlock *model, int count,
    void *heap, void *modelResource);
extern void Animation_RegisterAll(
    Animation *animation, void *resource, void *heap);
extern void Animation_SetAt(Animation *animation, int slot);
extern void *MaybeLoadBTP0Format(void *resource);
extern void *BTP0_LoadRawData(void *btp0, int index);
extern void Animation_Register(
    Animation *animation, int slot, void *joint, int animationIndex,
    void *heap);

extern char data_02166098[];
extern char data_021660a4[];
extern char data_021660b0[];
extern char data_021660bc[];

void LoadModelBMFromMD(
    void *heap, ModelBundle *bundle, ModelDescriptor *descriptor)
{
    u16 i;
    void *modelResource = 0;
    int usesSharedTextureAnimation = 0;
    char path[0x80];

    bundle->modelCount = descriptor->modelCount;
    bundle->models = 0;
    bundle->textureAnimations = 0;
    bundle->materialAnimations = bundle->textureAnimations;
    bundle->jointAnimations = bundle->materialAnimations;

    if (descriptor->modelCount != 0) {
        bundle->models = Mem_AllocateHeap(
            heap, descriptor->modelCount * sizeof(ModelBlock));
    }
    if (descriptor->jointAnimationCount != 0) {
        bundle->jointAnimations = Mem_AllocateHeap(
            heap, descriptor->jointAnimationCount * sizeof(Animation));
    }
    if (descriptor->materialAnimationCount != 0) {
        bundle->materialAnimations = Mem_AllocateHeap(
            heap, descriptor->materialAnimationCount * sizeof(Animation));
    }

    if (descriptor->modelCount == 1 &&
        descriptor->textureAnimationCount > 1) {
        bundle->textureAnimations =
            Mem_AllocateHeap(heap, sizeof(Animation));
        usesSharedTextureAnimation = 1;
    } else if (descriptor->textureAnimationCount != 0) {
        bundle->textureAnimations = Mem_AllocateHeap(
            heap, descriptor->textureAnimationCount * sizeof(Animation));
    }

    for (i = 0; i < descriptor->modelCount; i++) {
        _snprintf(path, sizeof(path), data_02166098, descriptor->names[i]);
        modelResource = find_buf_fn_from_thumb(path);
        Model_CreateFromNsbmdWithoutCullReverse(
            &bundle->models[i], modelResource);
    }

    for (i = 0; i < descriptor->jointAnimationCount; i++) {
        _snprintf(path, sizeof(path), data_021660a4, descriptor->names[i]);
        Animation_CreateFrom(
            0, &bundle->jointAnimations[i], &bundle->models[i], 1,
            heap, 0);
        Animation_RegisterAll(
            &bundle->jointAnimations[i], find_buf_fn_from_thumb(path), heap);
        Animation_SetAt(&bundle->jointAnimations[i], 0);
    }

    for (i = 0; i < descriptor->materialAnimationCount; i++) {
        _snprintf(path, sizeof(path), data_021660b0, descriptor->names[i]);
        Animation_CreateFrom(
            4, &bundle->materialAnimations[i], &bundle->models[i], 1,
            heap, 0);
        Animation_RegisterAll(
            &bundle->materialAnimations[i], find_buf_fn_from_thumb(path),
            heap);
        Animation_SetAt(&bundle->materialAnimations[i], 0);
    }

    if (usesSharedTextureAnimation == 0) {
        return;
    }

    Animation_CreateFrom(
        2, bundle->textureAnimations, bundle->models,
        descriptor->textureAnimationCount, heap, modelResource);

    for (i = 0; i < descriptor->textureAnimationCount; i++) {
        void *joint;

        _snprintf(path, sizeof(path), data_021660bc, descriptor->names[i]);
        joint = BTP0_LoadRawData(
            MaybeLoadBTP0Format(find_buf_fn_from_thumb(path)), 0);
        Animation_Register(
            bundle->textureAnimations, i, joint, 0, heap);
    }

    Animation_SetAt(bundle->textureAnimations, 0);
}
