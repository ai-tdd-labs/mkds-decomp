extern int data_02167144;
extern void *data_0217b124;

extern void *CreateMapObjectFromModel_2_from_thumb(void *a0, void *model);
extern void StructMapObject_MaybeSetPolygonId(void *obj, int polygonId);

void LoadTownTree1MapObject(void *a0)
{
    data_0217b124 = CreateMapObjectFromModel_2_from_thumb(a0, &data_02167144);
    StructMapObject_MaybeSetPolygonId(data_0217b124, 0x3f);
}
