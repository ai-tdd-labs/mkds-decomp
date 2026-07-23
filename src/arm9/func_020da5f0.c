// PURPOSE: Loads and prepares the Kuribo billboard model.
// Finds the model and texture files, probably places the resulting model in
// the global slot, and applies its standard setup. It takes no arguments.

extern char data_0216be98[];
extern char data_0216bea8[];
extern void *data_0217b688;

extern void *FormatFindMapObjFileBuffer_from_thumb(void *name);
extern void BillboardModel_AllocateFromNsbmdNsbtp_from_thumb(
    void *dst, void *buf, void *a2, void *a3);
extern void BillboardModel_SomeFn(void *model);

void func_020da5f0(void)
{
    void *model = FormatFindMapObjFileBuffer_from_thumb(data_0216be98);
    void *texture = FormatFindMapObjFileBuffer_from_thumb(data_0216bea8);

    BillboardModel_AllocateFromNsbmdNsbtp_from_thumb(
        &data_0217b688, model, texture, 0);
    BillboardModel_SomeFn(data_0217b688);
}
