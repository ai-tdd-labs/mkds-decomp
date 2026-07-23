extern int data_021671c0;
extern void *data_0217b16c;

extern void *CreateMapObjectFromModel_2_from_thumb(void *a0, void *model);
extern void StructMapObject_MaybeSetPolygonId(void *obj, int polygonId);

void LoadOlgMush1MapObject(void *a0)
{
    data_0217b16c = CreateMapObjectFromModel_2_from_thumb(a0, &data_021671c0);
    StructMapObject_MaybeSetPolygonId(data_0217b16c, 0x3f);
}
