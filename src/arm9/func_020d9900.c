// PURPOSE: Prepares the materials for two water models.
/*
 * The argument holds two model resources and their created model blocks.
 * The first resource is optional; both models receive material flags and
 * polygon IDs, followed by probably model-specific material indices.
 */

typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

typedef struct ModelBlock {
    u8 pad_00[0x18];
    u8 numMaterials;
} ModelBlock;

typedef struct ModelHolder {
    u32 state;
    ModelBlock *model;
} ModelHolder;

typedef struct WaterModelSetup {
    u8 pad_00[0x58];
    u16 firstMaterialIndex;
    u16 secondMaterialIndex;
    u8 pad_5c[4];
    void *firstResource;
    void *secondResource;
    ModelHolder firstModel;
    u8 pad_70[0x64];
    ModelHolder secondModel;
} WaterModelSetup;

extern void Model_CreateFromNsbmd(ModelHolder *holder, void *resource);
extern void ModelBlock_SomeTexPltFn_7(ModelBlock *model, int index, int materialFlags);
extern void ModelBlock_SomeTexPltFn_3(ModelBlock *model, int index, int polygonId);
extern int Dict_SomeFn_0(void *dictionary, const char *name);
extern void func_02013468(ModelBlock *model, int index, int materialIndex);

extern char data_02158094[];

void func_020d9900(WaterModelSetup *setup)
{
    u32 i;
    ModelBlock *model;
    ModelBlock * secondModel;
    int volatile secondIndex;
    int materialFlags = 0x294a;
    u16 firstMaterialIndex;

    if (setup->firstResource != 0) {
        Model_CreateFromNsbmd(&setup->firstModel, setup->firstResource);

        for (i = 0, model = setup->firstModel.model;
             i < model->numMaterials; i++) {
            ModelBlock_SomeTexPltFn_7(model, i, materialFlags);
        }

        for (i = 0, model = setup->firstModel.model;
             i < model->numMaterials; i++) {
            ModelBlock_SomeTexPltFn_3(model, i, 1);
        }
    }

    Model_CreateFromNsbmd(&setup->secondModel, setup->secondResource);

    for (i = 0, model = setup->secondModel.model;
         i < model->numMaterials; i++) {
        ModelBlock_SomeTexPltFn_7(model, i, materialFlags);
    }

    for (i = 0, model = setup->secondModel.model;
         i < model->numMaterials; i++) {
        ModelBlock_SomeTexPltFn_3(model, i, 2);
    }

    model = setup->secondModel.model;
    secondModel = model;
    secondIndex = Dict_SomeFn_0((u8 *)model + *(int *)((u8 *)model + 8) + 4,
                                data_02158094);

    if (setup->firstResource != 0) {
        firstMaterialIndex = setup->firstMaterialIndex;
        for (i = 0, model = setup->firstModel.model;
             i < model->numMaterials; i++) {
            func_02013468(model, i, firstMaterialIndex);
        }
    }

    func_02013468(secondModel, secondIndex, setup->secondMaterialIndex);
}
