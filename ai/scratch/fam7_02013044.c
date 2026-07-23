typedef struct ModelBlock {
    unsigned char pad[0x18];
    unsigned char numMaterials;
} ModelBlock;

extern void func_02013424(ModelBlock *model, int i, int arg1);

void Maybe_helper_013044(ModelBlock *model, int arg1)
{
    unsigned int i;

    for (i = 0; i < model->numMaterials; i++) {
        func_02013424(model, i, arg1);
    }
}
