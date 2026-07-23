// PURPOSE: Loads and configures the wooden box model.
// Finds the model file and creates it in the shared map-object slot.
// It then applies the standard polygon, light, and emission settings.
// Arguments and return value: none.

extern char data_0216c404[];
extern void *data_0217bbf8;

extern void *FormatFindMapObjFileBuffer_from_thumb(void *name);
extern void func_020ea588(void *slot, void *buf, int flag);
extern void Model_SetPolygonIdLightFlagsEmi(void *model, int polygonId,
                                            int lightFlags, int emission);

void func_020eb72c(void)
{
    /* Preserve the lookup result directly in the second call argument. */
    func_020ea588(&data_0217bbf8,
                   FormatFindMapObjFileBuffer_from_thumb(data_0216c404), 0);
    Model_SetPolygonIdLightFlagsEmi(data_0217bbf8, 0x3f, 2, 0x294a);
}
