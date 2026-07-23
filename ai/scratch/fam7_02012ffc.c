typedef struct ModelBlock {
    unsigned char pad[0x18];
    unsigned char numMaterials;
} ModelBlock;

extern void ModelBlock_SomeTexPltFn(ModelBlock *model, int i, int arg1);

void ModelBlock_SetSomethingToAllMaterials_MaybeTraslucent(ModelBlock *model, int arg1)
{
    unsigned int i;

    for (i = 0; i < model->numMaterials; i++) {
        ModelBlock_SomeTexPltFn(model, i, arg1);
    }
}
