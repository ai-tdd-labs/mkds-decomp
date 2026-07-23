// PURPOSE: Loads and prepares the Choropu map object model.
// Finds the model and texture files, probably creates their billboard model,
// then applies its standard setup. This function has no arguments or result.

extern char data_0216c128[];
extern char data_0216c138[];
extern void *data_0217b7b8;

extern void *FormatFindMapObjFileBuffer_from_thumb(void *name);
extern void BillboardModel_AllocateFromNsbmdNsbtp_from_thumb(
    void *dst, void *buf, void *a2, void *a3);
extern void BillboardModel_SomeFn(void *model);

void func_020e2fac(void)
{
    void *model_buffer;

    model_buffer = FormatFindMapObjFileBuffer_from_thumb(data_0216c128);
    BillboardModel_AllocateFromNsbmdNsbtp_from_thumb(
        &data_0217b7b8,
        model_buffer,
        FormatFindMapObjFileBuffer_from_thumb(data_0216c138),
        0);
    BillboardModel_SomeFn(data_0217b7b8);
}
