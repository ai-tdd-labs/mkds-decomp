extern int data_0216711c;
extern void *data_0217b168;

extern void *CreateMapObjectFromModel_2_from_thumb(void *a0, void *model);
extern void StructMapObject_MaybeSetPolygonId(void *obj, int polygonId);

void LoadSnowTree1MapObject(void *a0)
{
    data_0217b168 = CreateMapObjectFromModel_2_from_thumb(a0, &data_0216711c);
    StructMapObject_MaybeSetPolygonId(data_0217b168, 0x3f);
}
