// PURPOSE: Loads the pendulum model and its shadow.
// This function has no arguments or return value.
// It probably builds the main and shadow model objects in global slots, then
// applies the pendulum model's standard polygon lighting settings.

extern char data_0216c29c[];
extern void *data_0217b838;
extern char data_0216c2ac[];
extern void *data_0217b83c;

extern void *FormatFindMapObjFileBuffer_from_thumb(void *name);
extern void func_020ea588(void **out_model, void *nsbmd, int flag);
extern void func_020ea55c(void **out_object, void *data, unsigned char flag);
extern void Model_SetPolygonIdLightFlagsEmi(void *model, int polygon_id,
                                             int light_flags, int emission);

void func_020e5f68(void)
{
    func_020ea588(&data_0217b838,
                   FormatFindMapObjFileBuffer_from_thumb(data_0216c29c), 0);
    func_020ea55c(&data_0217b83c,
                   FormatFindMapObjFileBuffer_from_thumb(data_0216c2ac), 0x3f);

    Model_SetPolygonIdLightFlagsEmi(data_0217b838, 0x3f, 2, 0x294a);
}
