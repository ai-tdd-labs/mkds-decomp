// PURPOSE: Loads and prepares the Pukupuku map object model.
// Finds the Pukupuku model file, probably creates its billboard model in the
// global slot, and then applies the model's standard setup. No arguments or
// return value.

extern char data_0216c20c[];
extern void *data_0217b7f0;

extern void *FormatFindMapObjFileBuffer_from_thumb(void *name);
extern void BillboardModel_AllocateFromNsbmdNsbtp_from_thumb(
    void *dst, void *buf, void *a2, void *a3);
extern void BillboardModel_SomeFn(void *model);

void func_020e48b4(void)
{
    /* The nested lookup leaves its result directly in the second argument. */
    BillboardModel_AllocateFromNsbmdNsbtp_from_thumb(
        &data_0217b7f0,
        FormatFindMapObjFileBuffer_from_thumb(data_0216c20c),
        0,
        0);
    BillboardModel_SomeFn(data_0217b7f0);
}
