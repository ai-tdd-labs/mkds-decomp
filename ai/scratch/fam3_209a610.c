extern int data_021671d0;
extern void *data_0217b140;

extern void *CreateMapObjectFromModel_2_from_thumb(void *a0, void *model);
extern void StructMapObject_MaybeSetPolygonId(void *obj, int polygonId);

void LoadOpaTree1MapObject(void *a0)
{
    data_0217b140 = CreateMapObjectFromModel_2_from_thumb(a0, &data_021671d0);
    StructMapObject_MaybeSetPolygonId(data_0217b140, 0x3f);
}
