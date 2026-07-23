// PURPOSE: Loads the Dossun model and its shadow.
// It finds the two map-object model files and stores their prepared data.
// The loaded main model probably receives its standard polygon and lighting setup.

extern char data_0216beb8[];
extern void *data_0217b68c;
extern char data_0216bec8[];
extern void *data_0217b694;

extern void *FormatFindMapObjFileBuffer_from_thumb(void *name);
extern void func_020ea588(void *dst, void *buf, int arg);
extern void func_020ea55c(void *dst, void *buf, int arg);
extern void Model_SetPolygonIdLightFlagsEmi(void *model, int polygon_id,
                                            int light_flags, int emi);

void func_020db3e4(void)
{
    func_020ea588(&data_0217b68c,
                  FormatFindMapObjFileBuffer_from_thumb(data_0216beb8), 0);
    func_020ea55c(&data_0217b694,
                  FormatFindMapObjFileBuffer_from_thumb(data_0216bec8), 0x3f);
    Model_SetPolygonIdLightFlagsEmi(data_0217b68c, 0x3f, 2, 0x294a);
}
