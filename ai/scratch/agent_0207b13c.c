/* PURPOSE: Sets material options for two racer models.
 * The racer owns a visual context containing two model references.
 * This probably skips models whose visual state is already active.
 * Each available model receives material options 2 and 3 in sequence. */
typedef unsigned char u8;

typedef struct ModelBlock ModelBlock;

typedef struct RacerModelReference {
    u8 padding_00[4];
    ModelBlock *model;
} RacerModelReference;

typedef struct RacerVisualContext {
    u8 padding_00[0x10];
    RacerModelReference *primaryModel;
    RacerModelReference *secondaryModel;
    u8 padding_18[0x4c];
    void *activeState;
} RacerVisualContext;

typedef struct StructMQRacerEntry {
    u8 padding_000[0x590];
    RacerVisualContext *visualContext;
} StructMQRacerEntry;

extern void ModelBlock_SomeMatFn_4(ModelBlock *model, int option);
extern void ModelBlock_SomeMatFn(ModelBlock *model, int option);

void StructMQRacerEntry_SomeFn_36(StructMQRacerEntry *racer)
{
    RacerVisualContext *visualContext = racer->visualContext;
    ModelBlock *model;

    if (visualContext->activeState != 0) {
        return;
    }

    model = visualContext->primaryModel->model;
    ModelBlock_SomeMatFn_4(model, 2);
    ModelBlock_SomeMatFn(model, 3);

    model = visualContext->secondaryModel->model;
    ModelBlock_SomeMatFn_4(model, 2);
    ModelBlock_SomeMatFn(model, 3);
}
