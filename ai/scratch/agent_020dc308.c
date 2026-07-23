// PURPOSE: Loads the Wanwan model and its rock shadow.
// This setup function finds two map-object model files and creates their
// corresponding global model instances. It then applies the shared polygon
// lighting settings to the shadow model.

extern char data_0216bf2c[];
extern void *data_0217b6cc;
extern char data_0216bf3c[];
extern void *data_0217b6d0;

extern void *FormatFindMapObjFileBuffer_from_thumb(void *name);
extern void func_020ea588(void *out_model, void *nsbmd, int flags);
extern void func_020ea55c(void *out_model, void *nsbmd, int polygon_id);
extern void Model_SetPolygonIdLightFlagsEmi(void *model, int polygon_id,
                                            int light_flags, int emission);

void func_020dc308(void)
{
    func_020ea588(&data_0217b6cc,
                   FormatFindMapObjFileBuffer_from_thumb(data_0216bf2c), 0);
    func_020ea55c(&data_0217b6d0,
                   FormatFindMapObjFileBuffer_from_thumb(data_0216bf3c), 0x3F);
    Model_SetPolygonIdLightFlagsEmi(data_0217b6cc, 0x3F, 2, 0x294A);
}
