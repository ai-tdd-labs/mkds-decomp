// PURPOSE: Loads and configures the second-hand map object model.
// This function has no arguments and no return value.
// It probably creates the model in a shared global slot, then applies its
// standard polygon, light, and emission settings.

extern char data_0216c260[];
extern void *data_0217b820;

extern void *FormatFindMapObjFileBuffer_from_thumb(void *name);
extern void func_020ea588(void *slot, void *buf, int flag);
extern void Model_SetPolygonIdLightFlagsEmi(void *model, int polygonId,
                                             int lightFlags, int emission);

void func_020e576c(void)
{
    func_020ea588(&data_0217b820,
                   FormatFindMapObjFileBuffer_from_thumb(data_0216c260), 0);
    Model_SetPolygonIdLightFlagsEmi(data_0217b820, 0x3f, 2, 0x294a);
}
