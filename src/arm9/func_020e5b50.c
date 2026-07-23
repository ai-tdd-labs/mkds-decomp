// PURPOSE: Loads and prepares the Pakkun map object model.
// Finds the model and animation files, probably creates the billboard model
// in its global slot, and applies the standard setup. It takes no arguments
// and returns no value.

extern char data_0216c274[];
extern char data_0216c288[];
extern void *data_0217b830;

extern void *FormatFindMapObjFileBuffer_from_thumb(void *name);
extern void BillboardModel_AllocateFromNsbmdNsbtp_from_thumb(
    void *dst, void *buf, void *a2, void *a3);
extern void BillboardModel_SomeFn(void *model);

void func_020e5b50(void)
{
    /* Look up both files before allocating the shared billboard model. */
    BillboardModel_AllocateFromNsbmdNsbtp_from_thumb(
        &data_0217b830,
        FormatFindMapObjFileBuffer_from_thumb(data_0216c274),
        FormatFindMapObjFileBuffer_from_thumb(data_0216c288),
        0);
    BillboardModel_SomeFn(data_0217b830);
}
