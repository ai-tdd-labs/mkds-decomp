extern int data_02167154;
extern void *data_0217b118;

extern void *CreateMapObjectFromModel_2_from_thumb(void *a0, void *model);
extern void StructMapObject_MaybeSetPolygonId(void *obj, int polygonId);

void LoadGardenTree1MapObject(void *a0)
{
    data_0217b118 = CreateMapObjectFromModel_2_from_thumb(a0, &data_02167154);
    StructMapObject_MaybeSetPolygonId(data_0217b118, 0x3f);
}
