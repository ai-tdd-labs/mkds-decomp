/*
 * PURPOSE: Loads the "kart_tire" model and finds its material block by name.
 *
 * Creates a model from an NSBMD/NSBTX pair pointed to by `self`, forces a
 * render pass and a material-block pass on it, then looks up the dictionary
 * entry named "kart_tire" inside the model's material dictionary (located at
 * model+8's offset, plus 4) and hands the found entry to func_02013468
 * together with the model pointer. Returns whatever func_02013468 returns.
 * Field layouts are unknown, so pointer arithmetic mirrors the disassembly
 * literally instead of naming struct fields.
 */

extern void *Model_CreateFromNsbmdNsbtx(void *self);
extern void Model_Render(void *model, int mode);
extern void ModelBlock_SomeMatFn(void *model, int flag);
extern void *Dict_SomeFn_0(void *dict, const char *name);
extern int func_02013468(void *model, void *entry, int flag);

extern char data_02155098[]; /* "kart_tire" */

int Model_CreateFromNsbmdNsbtx2_from_thumb(void *self)
{
    void *model = Model_CreateFromNsbmdNsbtx(self);

    Model_Render(self, 3);
    ModelBlock_SomeMatFn(model, 1);

    /* dict = model + *(int*)(model + 8) + 4 */
    int dictOff = *(int *)((char *)model + 8);
    void *dict = (char *)model + dictOff + 4;

    void *entry = Dict_SomeFn_0(dict, data_02155098);

    return func_02013468(model, entry, 0);
}
