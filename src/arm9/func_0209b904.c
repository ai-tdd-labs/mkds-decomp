/*
PURPOSE: Applies a polygon ID to a nested model.

Takes a wrapper, a polygon ID, and a material index.
It does nothing when the wrapper has no nested model reference.
The nested model operation is probably used while configuring model materials.
*/

typedef struct ModelBlock ModelBlock;

typedef struct ModelReference {
    char padding[4];
    ModelBlock *model;
} ModelReference;

typedef struct ModelWrapper {
    char padding[16];
    ModelReference *reference;
} ModelWrapper;

extern void ModelBlock_SomeTexPltFn_3(ModelBlock *model, int index, int polygonId);

void func_0209b904(ModelWrapper *wrapper, int polygonId, int index)
{
    if (wrapper->reference == 0) {
        return;
    }

    ModelBlock_SomeTexPltFn_3(wrapper->reference->model, index, polygonId);
}
