// PURPOSE: Creates and prepares a model for rendering.
// The input probably points to paired model and texture data.
// It creates the model, renders the input in mode three, and updates its materials.

extern void *Model_CreateFromNsbmdNsbtx(void *self);
extern void Model_Render(void *model, int mode);
extern void ModelBlock_SomeMatFn(void *model, int flag);

void func_02079014(void *self)
{
    void *model = Model_CreateFromNsbmdNsbtx(self);

    Model_Render(self, 3);
    ModelBlock_SomeMatFn(model, 1);
}
