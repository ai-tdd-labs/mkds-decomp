// PURPOSE: Loads and prepares the Koopa Block map object model.
// Finds the model file and registers it in the first global model slot.
// It then applies the model's standard polygon settings and links the two
// global model-related objects. This routine takes no arguments and returns nothing.

extern char data_0216c010[];
extern void *data_0217b77c;
extern void *data_0217b784;

extern void *FormatFindMapObjFileBuffer_from_thumb(void *name);
extern void func_020ea588(void *slot, void *buf, int flag);
extern void Model_SetPolygonIdLightFlagsEmi(void *model, int polygonId,
                                            int flags, int emi);
extern void func_020e1dc0(void *a0, void *a1);

void func_020dff08(void)
{
    func_020ea588(&data_0217b77c,
                   FormatFindMapObjFileBuffer_from_thumb(data_0216c010), 0);
    Model_SetPolygonIdLightFlagsEmi(data_0217b77c, 0x3f, 2, 0x294a);
    func_020e1dc0(data_0217b784, data_0217b77c);
}
