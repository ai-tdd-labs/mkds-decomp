// PURPOSE: Advances the kart-select model loading process.
// The function waits for the save worker and handles one loading stage per call.
// Finished kart models receive their palette, emblem, and animation links.
// Some resource field meanings are probable, but every offset follows the menu work data.

typedef unsigned char u8;
typedef unsigned short u16;
typedef signed short s16;

typedef struct ModelBlock ModelBlock;
typedef struct Animation Animation;

typedef struct KartAnimationState {
    u8 pad_00[0x0c];
    void *f0c;
    u8 pad_10[0x0a];
    u16 f1a;
    void ***f1c;
} KartAnimationState;

typedef struct StructCESub {
    int f00;
    int character;
    Animation *animation;
    u8 pad_0c[4];
    ModelBlock *model;
    ModelBlock *bodyModel;
    void *f18;
    void *f1c;
    u8 pad_20[0x5c];
    void *f7c;
    u8 pad_80[0x34];
    void *emblemData;
} StructCESub;

typedef struct CEElem {
    int f00;
    int heapId;
    void *modelData;
    void *textureData;
    void *textureResource;
    void *animationData;
    void *bodyModelData;
    void *bodyTextureData;
    void *f20;
    void *f24;
    void *f28;
    int lock;
    u16 state;
    u16 pad_32;
} CEElem;

typedef struct StructCE {
    u8 pad_000[0x20];
    StructCESub *current;
    u8 pad_024[0x2c];
    int horizontalOffset;
    u8 pad_054[4];
    StructCESub subs[2];
    u8 pad_1c8[8];
    void *kartAppearanceTable;
    void *textureBlock;
    u8 pad_1d8[0x1c];
    CEElem elems[2];
    u8 pad_25c[8];
    s16 selectedSlot;
    s16 currentElem;
    int f268;
} StructCE;

typedef struct SaveWorkerState {
    u8 pad_00[0xf8];
    int taskPending;
} SaveWorkerState;

extern StructCE *data_0217ad08;
extern SaveWorkerState *data_0217aa0c;

extern void G3X_SetHOffset(int offset);
extern void MaybeLoadWinModelTextureAnimationHelper_from_thumb(
    int heapId, ModelBlock *model, Animation *animation, void *modelData,
    void *textureData, void *animationData);
extern void func_02078f78(void *resource);
extern void StructAD00Sh_SomeFn_1_from_thumb(void *self, void *arg);
extern void func_02079014(void *self, void *modelData, void *textureData);
extern int Model_CreateFromNsbmdNsbtx2_from_thumb(
    void *self, void *modelData, void *textureData);
extern void StructCESub_SomeFn_from_thumb(StructCESub *sub);
extern void LoadKartBodyPalette_from_thumb(
    ModelBlock *model, int character, void *palette);
extern void CharacterKart_PatchRobPalette_from_thumb(
    StructCESub *sub, int isPlayer);

void func_02077c1c(void)
{
    StructCE *work;
    CEElem *elem;
    StructCESub *sub;

    G3X_SetHOffset(data_0217ad08->horizontalOffset);
    if (data_0217aa0c->taskPending != 0) {
        return;
    }

    work = data_0217ad08;
    elem = &work->elems[work->currentElem];
    if (elem->lock == 0) {
        return;
    }
    sub = work->current;

    if (elem->state == 0) {
        MaybeLoadWinModelTextureAnimationHelper_from_thumb(
            elem->heapId, sub->model, sub->animation, elem->modelData,
            elem->textureData, elem->animationData);
        elem->state++;
        return;
    }

    if (elem->state == 1) {
        func_02078f78(elem->textureResource);
        data_0217ad08->current->emblemData = data_0217ad08->textureBlock;
        StructAD00Sh_SomeFn_1_from_thumb(sub->f1c, elem->f28);
        func_02079014(sub->f18, elem->f20, elem->f24);
        elem->state++;
        return;
    }

    Model_CreateFromNsbmdNsbtx2_from_thumb(
        sub->bodyModel, elem->bodyModelData, elem->bodyTextureData);
    StructCESub_SomeFn_from_thumb(data_0217ad08->current);
    LoadKartBodyPalette_from_thumb(
        sub->bodyModel, sub->character, data_0217ad08->kartAppearanceTable);
    CharacterKart_PatchRobPalette_from_thumb(sub, 1);

    elem->lock = 0;
    elem->state = 0;

    work = data_0217ad08;
    if (work->selectedSlot >= 0) {
        StructCESub *selected = &work->subs[work->selectedSlot];

        if (sub->f00 == selected->f00) {
            KartAnimationState *dst = (KartAnimationState *)sub->animation;
            KartAnimationState *src = (KartAnimationState *)selected->animation;

            dst->f0c = src->f0c;
            *dst->f1c[dst->f1a] = dst->f0c;
        }
    }

    data_0217ad08->selectedSlot = data_0217ad08->currentElem;
    data_0217ad08->currentElem = data_0217ad08->currentElem == 0;
    data_0217ad08->current =
        &data_0217ad08->subs[data_0217ad08->currentElem];
}
