// PURPOSE: Loads and configures the DRAM map object model.
// This function has no arguments or return value.
// It probably creates the model in its global slot and sets its render flags.

extern char data_0216c770[];
extern void *data_0217c628;

extern void *FormatFindMapObjFileBuffer_from_thumb(void *name);
extern void func_020ea588(void *slot, void *buf, int flag);
extern void Model_SetPolygonIdLightFlagsEmi(void *model, int polygonId,
                                            int lightFlags, int emission);

void func_020ffbd4(void)
{
    func_020ea588(&data_0217c628,
                  FormatFindMapObjFileBuffer_from_thumb(data_0216c770), 0);
    Model_SetPolygonIdLightFlagsEmi(data_0217c628, 0x3f, 2, 0x294a);
}
