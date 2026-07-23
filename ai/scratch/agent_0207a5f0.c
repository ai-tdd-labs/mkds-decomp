// PURPOSE: Applies an animation argument to every loaded model.

typedef unsigned char u8;

typedef struct ModelBlock ModelBlock;

typedef struct ModelRef {
    u8 unk_00[4];
    ModelBlock *model;
} ModelRef;

typedef struct ModelGroup {
    u8 unk_00[0x10];
    ModelRef *model_10;
    ModelRef *model_14;
    ModelRef *model_18;
} ModelGroup;

typedef struct ModelEntry {
    u8 unk_00[0x590];
    ModelGroup *group;
    u8 unk_594[0x14];
} ModelEntry;

extern unsigned short data_0217ad14;
extern ModelEntry *data_0217ad18;
extern void Maybe_helper_013044(ModelBlock *model, int arg1);

void func_0207a5f0(int arg0)
{
    int i;
    ModelEntry *entry = data_0217ad18;

    for (i = 0; i < data_0217ad14; i++) {
        ModelGroup *group = entry->group;

        Maybe_helper_013044(group->model_14->model, arg0);
        Maybe_helper_013044(group->model_10->model, arg0);
        if (group->model_18 != 0) {
            Maybe_helper_013044(group->model_18->model, arg0);
        }
        entry++;
    }
}
