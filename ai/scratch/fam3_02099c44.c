extern int data_0216710c;
extern void *data_0217b154;

extern void *CreateMapObjectFromModel_2_from_thumb(void *a0, void *model);
extern void StructMapObject_MaybeSetPolygonId(void *obj, int polygonId);

void LoadDeTree1MapObject(void *a0)
{
    data_0217b154 = CreateMapObjectFromModel_2_from_thumb(a0, &data_0216710c);
    StructMapObject_MaybeSetPolygonId(data_0217b154, 0x3f);
}
