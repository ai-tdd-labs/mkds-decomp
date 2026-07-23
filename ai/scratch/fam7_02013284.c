typedef struct ModelBlock {
    unsigned char pad[0x18];
    unsigned char numMaterials;
} ModelBlock;

extern void ModelBlock_SomeTexPltFn_5(ModelBlock *model, int i, int arg1);

void ModelBlock_SomeMatFn_1(ModelBlock *model, int arg1)
{
    unsigned int i;

    for (i = 0; i < model->numMaterials; i++) {
        ModelBlock_SomeTexPltFn_5(model, i, arg1);
    }
}
