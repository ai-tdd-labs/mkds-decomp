typedef struct ModelBlock {
    unsigned char pad[0x18];
    unsigned char numMaterials;
} ModelBlock;

extern void ModelBlock_SomeTexPltFn_3(ModelBlock *model, int i, int arg1);

void ModelBlock_SetPolygonId(ModelBlock *model, int arg1)
{
    unsigned int i;

    for (i = 0; i < model->numMaterials; i++) {
        ModelBlock_SomeTexPltFn_3(model, i, arg1);
    }
}
