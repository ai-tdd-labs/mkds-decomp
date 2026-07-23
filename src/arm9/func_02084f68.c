// PURPOSE: Applies the first texture palette action to every material in a model.
// The argument probably wraps a pointer to the model at offset 4.
// Each material receives the fixed action value 1.

typedef struct ModelBlock {
    unsigned char pad[0x18];
    unsigned char numMaterials;
} ModelBlock;

typedef struct ModelBlockHolder {
    unsigned char pad[4];
    ModelBlock *model;
} ModelBlockHolder;

extern void ModelBlock_SomeTexPltFn_1(ModelBlock *model, int i, int arg1);

void func_02084f68(ModelBlockHolder *holder)
{
    unsigned int i;
    ModelBlock *model = holder->model;

    for (i = 0; i < model->numMaterials; i++) {
        ModelBlock_SomeTexPltFn_1(model, i, 1);
    }
}
