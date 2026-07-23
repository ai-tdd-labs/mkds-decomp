// PURPOSE: Loads a model and adjusts its material palette modes.
// The first argument receives model state built from the resource argument.
// The third argument probably enables a scene-specific race setting.
// Matching materials are assigned one of two fixed palette modes.

typedef unsigned char u8;
typedef unsigned int u32;

typedef struct ModelBlock {
    u8 padding_00[0x18];
    u8 numMaterials;
} ModelBlock;

typedef struct ModeResource {
    u8 padding_00[0x18];
    u8 flag_18;
    u8 flag_19;
} ModeResource;

typedef struct Mode {
    u32 unknown_00;
    ModelBlock *model;
    u8 padding_08[0x4c];
    int raceSetting;
    int useSpecialMode;
} Mode;

typedef struct RaceConfig {
    u8 padding_00[0x57];
    signed char setting_57;
} RaceConfig;

extern RaceConfig *gRaceConfig;

extern int GetCurrentSceneId(void);
extern void Mode_CreateFromResource(Mode *mode, void *resource);
extern int ModelBlock_SomeTexPltFn_0(ModelBlock *model, int index);
extern void ModelBlock_SomeTexPltFn_1(ModelBlock *model, int index, int mode);

void StructML_MaybeInnerLoadModel(Mode *mode, ModeResource *resource,
                                  int useRaceSetting)
{
    unsigned int i;
    ModelBlock *model;

    if (useRaceSetting != 0 && GetCurrentSceneId() == 2) {
        mode->raceSetting = gRaceConfig->setting_57;
    } else {
        mode->raceSetting = 0;
    }

    if (resource->flag_18 == 1 && resource->flag_19 == 1) {
        mode->useSpecialMode = 1;
    } else {
        mode->useSpecialMode = 0;
    }

    Mode_CreateFromResource(mode, resource);

    if (mode->raceSetting == 0) {
        return;
    }

    model = mode->model;
    i = 0;
    if (i < model->numMaterials) {
        do {
            if (ModelBlock_SomeTexPltFn_0(model, i) == 1) {
                ModelBlock_SomeTexPltFn_1(model, i, 2);
            } else if (ModelBlock_SomeTexPltFn_0(model, i) == 2) {
                ModelBlock_SomeTexPltFn_1(model, i, 1);
            }
            i++;
        } while (i < model->numMaterials);
    }
}
