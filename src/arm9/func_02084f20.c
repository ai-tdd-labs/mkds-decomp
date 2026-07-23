// PURPOSE: Applies texture palette settings to every material in a model.
// The input probably wraps a model pointer at offset four.
// Each material is processed with the fixed palette mode two.

typedef struct ModelBlock {
    unsigned char pad[0x18];
    unsigned char numMaterials;
} ModelBlock;

typedef struct ModelBlockWrapper {
    unsigned char pad[4];
    ModelBlock *model;
} ModelBlockWrapper;

extern void ModelBlock_SomeTexPltFn_1(ModelBlock *model, int i, int arg1);

void func_02084f20(ModelBlockWrapper *wrapper)
{
    unsigned int i = 0;
    ModelBlock *model = wrapper->model;
    int arg1 = 2;

    if (i < model->numMaterials) {
        do {
            ModelBlock_SomeTexPltFn_1(model, i, arg1);
            i++;
        } while (i < model->numMaterials);
    }
}
