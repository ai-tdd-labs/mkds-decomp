// PURPOSE: Loads and configures the bridge map object's model and animation resources.
extern void *FormatFindMapObjFileBuffer_from_thumb(void *name);
extern void func_020ea588(void *slot, void *buf, int flag);
extern void func_020ea4bc(int a0, void *a1, void *a2, void *a3, void *a4);
extern int Animation_GetCurrentLength(void *animation);
extern void Model_SetPolygonIdLightFlagsEmi(void *model, int polygonId, int flags, void *emi);
extern void func_020e1dc0(void *model, void *animation);

extern int data_0216c148;
extern int data_0216c158;
extern void *data_0217b7c4;
extern void *data_0217b7cc;
extern void *data_0217b7d0;

void func_020e3a7c(void)
{
    void *nsbmdBuf;
    void *nsbcaBuf;

    nsbmdBuf = FormatFindMapObjFileBuffer_from_thumb(&data_0216c148);
    func_020ea588(&data_0217b7d0, nsbmdBuf, 0);
    nsbcaBuf = FormatFindMapObjFileBuffer_from_thumb(&data_0216c158);
    func_020ea4bc(0, data_0217b7d0, &data_0217b7cc, nsbmdBuf, nsbcaBuf);
    ((int *)data_0217b7c4)[0xb] = Animation_GetCurrentLength(data_0217b7cc);
    Model_SetPolygonIdLightFlagsEmi(data_0217b7d0, 0x3f, 2, (void *)0x294a);
    func_020e1dc0(data_0217b7c4, data_0217b7d0);
}
