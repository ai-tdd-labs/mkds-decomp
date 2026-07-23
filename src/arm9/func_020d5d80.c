// PURPOSE: Loads a map object's model and companion object.
// The first argument is unused; the other two name the model data to load.
// It probably prepares both global objects and draws the model once.

extern void *data_0217b65c;
extern void *data_0217b658;

extern void *FormatFindMapObjFileBuffer_from_thumb(void *name);
extern void func_020ea588(void **out_model, void *nsbmd, int flag);
extern void func_020ea55c(void **out_object, void *data, int flag);
extern void Model_SetPolygonIdLightFlagsEmi(void *model, int polygon_id,
                                            int light_flags, int emission);
extern void Model_Render(void *model, int mode);

void func_020d5d80(void *unused, void *model_name, void *object_name)
{
    func_020ea588(&data_0217b65c,
                   FormatFindMapObjFileBuffer_from_thumb(model_name), 0);
    func_020ea55c(&data_0217b658,
                   FormatFindMapObjFileBuffer_from_thumb(object_name), 7);
    Model_SetPolygonIdLightFlagsEmi(data_0217b65c, 0x3f, 2, 0x294a);
    Model_Render(data_0217b65c, 7);
}
