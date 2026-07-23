/* PURPOSE: Resets material settings for both racer models.
 * The racer owns a character context at offset 0x590.
 * If that context is inactive, both model containers are updated with zero.
 * The exact meaning of the context state and material settings is uncertain.
 */

typedef struct ModelBlock ModelBlock;

typedef struct RacerModelContainer {
    unsigned char pad_00[4];
    ModelBlock *model;
} RacerModelContainer;

typedef struct RacerCharacterContext {
    unsigned char pad_00[0x10];
    RacerModelContainer *primaryModel;
    RacerModelContainer *secondaryModel;
    unsigned char pad_18[0x4c];
    int state;
} RacerCharacterContext;

typedef struct StructMQRacerEntry {
    unsigned char pad_00[0x590];
    RacerCharacterContext *characterContext;
} StructMQRacerEntry;

extern void ModelBlock_SomeMatFn_4(ModelBlock *model, int setting);
extern void ModelBlock_SomeMatFn(ModelBlock *model, int setting);

void StructMQRacerEntry_SomeFn_2(StructMQRacerEntry *racer)
{
    RacerCharacterContext *context = racer->characterContext;
    ModelBlock *model;

    if (context->state != 0) {
        return;
    }

    model = context->primaryModel->model;
    ModelBlock_SomeMatFn_4(model, 0);
    ModelBlock_SomeMatFn(model, 0);

    model = context->secondaryModel->model;
    ModelBlock_SomeMatFn_4(model, 0);
    ModelBlock_SomeMatFn(model, 0);
}
