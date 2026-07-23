// PURPOSE: Loads the course models and their animations.
// The heap supplies storage for the main model and an optional variant.
// Missing animation resources disable the corresponding animation slot.
// Certain courses probably receive material-specific rendering adjustments.

typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

typedef struct ModelBlock {
    u8 _00[8];
    u32 dictionaryOffset;
} ModelBlock;

typedef struct Animation {
    u8 _00[0x18];
    u16 jointCount;
    u8 _1a[0x1e];
} Animation;

typedef struct CourseModelState {
    ModelBlock *mainModel;
    ModelBlock *variantModel;
    Animation patternAnimation;
    Animation textureAnimation;
    Animation variantAnimation;
} CourseModelState;

typedef struct RaceConfig {
    int courseId;
} RaceConfig;

extern void *FindFileBuffer_CRS_CST_from_thumb(char *path);
extern void *Mem_AllocateHeap(void *heap, unsigned int size);
extern ModelBlock *Model_CreateFromNsbmdNsbtxMetaCopy(
    void *heap, void *storage, void *nsbmd, void *nsbtx);
extern void Animation_CreateFrom(
    int type, Animation *animation, ModelBlock *model, int enabled,
    void *heap, void *nsbmd);
extern void Animation_RegisterAll(
    Animation *animation, void *resource, void *heap);
extern void Animation_SetLoop(Animation *animation, int index, int loop);
extern void Animation_SetAt(Animation *animation, int index);
extern void Model_Render(ModelBlock *model, int mode);
extern void ModelBlock_SetSomethingToAllMaterials_MaybeTraslucent(
    ModelBlock *model, int enabled);
extern int Dict_SomeFn_0(void *dictionary, char *name);
extern void func_02013468(ModelBlock *model, int material, int value);
extern void ModelBlock_SomeTexPltFn(
    ModelBlock *model, int material, int value);
extern void ModelBlock_SomeTexPltFn_3(
    ModelBlock *model, int material, int value);
extern void Matrix4x3_Identity(void *matrix);
extern void func_0206302c(void);

extern CourseModelState data_0217ab1c;
extern Animation data_0217ab24;
extern Animation data_0217ab5c;
extern Animation data_0217ab94;
extern u8 data_0217abcc[];
extern RaceConfig *gRaceConfig;

extern char data_02165404[];
extern char data_02165418[];
extern char data_0216542c[];
extern char data_02165440[];
extern char data_02165454[];
extern char data_0216546c[];
extern char data_02165484[];
extern char data_02154a00[];
extern char data_02154990[];
extern char data_02154a10[];
extern char data_021549f0[];
extern char data_021549c0[];
extern char data_021549d0[];
extern char data_021549e0[];
extern char data_021549b0[];
extern char data_021549a0[];

void LoadCourseModelsAnimations(void *heap)
{
    void *modelFile;
    void *textureFile;
    ModelBlock *model;
    void *animationFile;
    int shadowMaterials[6];
    int material;
    int i;

    modelFile = FindFileBuffer_CRS_CST_from_thumb(data_02165404);
    textureFile = FindFileBuffer_CRS_CST_from_thumb(data_02165418);

    data_0217ab1c.mainModel = Mem_AllocateHeap(heap, 0x6c);
    model = Model_CreateFromNsbmdNsbtxMetaCopy(
        heap, data_0217ab1c.mainModel, modelFile, textureFile);

    animationFile = FindFileBuffer_CRS_CST_from_thumb(data_0216542c);
    if (animationFile == 0) {
        data_0217ab1c.patternAnimation.jointCount = 0;
    } else {
        Animation_CreateFrom(
            2, &data_0217ab24, data_0217ab1c.mainModel, 1, heap, modelFile);
        Animation_RegisterAll(&data_0217ab24, animationFile, heap);
        Animation_SetLoop(&data_0217ab24, 0, 1);
        Animation_SetAt(&data_0217ab24, 0);
    }

    animationFile = FindFileBuffer_CRS_CST_from_thumb(data_02165440);
    if (animationFile == 0) {
        data_0217ab1c.textureAnimation.jointCount = 0;
    } else {
        Animation_CreateFrom(
            1, &data_0217ab5c, data_0217ab1c.mainModel, 1, heap, modelFile);
        Animation_RegisterAll(&data_0217ab5c, animationFile, heap);
        Animation_SetLoop(&data_0217ab5c, 0, 1);
        Animation_SetAt(&data_0217ab5c, 0);
    }

    Model_Render(data_0217ab1c.mainModel, 8);
    ModelBlock_SetSomethingToAllMaterials_MaybeTraslucent(model, 1);

    switch (gRaceConfig->courseId) {
    case 12:
        material = Dict_SomeFn_0(
            (u8 *)model + model->dictionaryOffset + 4, data_02154a00);
        if (material >= 0) {
            func_02013468(model, material, 0x1e);
            ModelBlock_SomeTexPltFn(model, material, 0);
        }
        break;

    case 22:
        material = Dict_SomeFn_0(
            (u8 *)model + model->dictionaryOffset + 4, data_02154990);
        if (material >= 0) {
            ModelBlock_SomeTexPltFn(model, material, 0);
        }

        material = Dict_SomeFn_0(
            (u8 *)model + model->dictionaryOffset + 4, data_02154a10);
        if (material >= 0) {
            ModelBlock_SomeTexPltFn(model, material, 0);
        }
        break;
    }

    data_0217ab1c.variantModel = 0;
    modelFile = FindFileBuffer_CRS_CST_from_thumb(data_02165454);
    textureFile = FindFileBuffer_CRS_CST_from_thumb(data_0216546c);

    if (modelFile != 0) {
        data_0217ab1c.variantModel = Mem_AllocateHeap(heap, 0x6c);
        Model_CreateFromNsbmdNsbtxMetaCopy(
            heap, data_0217ab1c.variantModel, modelFile, textureFile);
        Model_Render(data_0217ab1c.variantModel, 8);

        animationFile = FindFileBuffer_CRS_CST_from_thumb(data_02165484);
        if (animationFile == 0) {
            data_0217ab1c.variantAnimation.jointCount = 0;
        } else {
            Animation_CreateFrom(
                1, &data_0217ab94, data_0217ab1c.variantModel, 1,
                heap, modelFile);
            Animation_RegisterAll(&data_0217ab94, animationFile, heap);
            Animation_SetLoop(&data_0217ab94, 0, 1);
            Animation_SetAt(&data_0217ab94, 0);
        }
    }

    shadowMaterials[0] = Dict_SomeFn_0(
        (u8 *)model + model->dictionaryOffset + 4, data_021549f0);
    shadowMaterials[1] = Dict_SomeFn_0(
        (u8 *)model + model->dictionaryOffset + 4, data_021549c0);
    shadowMaterials[2] = Dict_SomeFn_0(
        (u8 *)model + model->dictionaryOffset + 4, data_021549d0);
    shadowMaterials[3] = Dict_SomeFn_0(
        (u8 *)model + model->dictionaryOffset + 4, data_021549e0);
    shadowMaterials[4] = Dict_SomeFn_0(
        (u8 *)model + model->dictionaryOffset + 4, data_021549b0);
    shadowMaterials[5] = Dict_SomeFn_0(
        (u8 *)model + model->dictionaryOffset + 4, data_021549a0);

    for (i = 0; i < 6; i++) {
        if (shadowMaterials[i] >= 0) {
            ModelBlock_SomeTexPltFn_3(model, shadowMaterials[i], 7);
        }
    }

    Matrix4x3_Identity(data_0217abcc);
    func_0206302c();
}
