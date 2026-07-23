extern int data_0216717c;
extern void *data_0217b11c;

extern void *CreateMapObjectFromModel_2_from_thumb(void *a0, void *model);
extern void StructMapObject_MaybeSetPolygonId(void *obj, int polygonId);

void LoadCrossTree1MapObject(void *a0)
{
    data_0217b11c = CreateMapObjectFromModel_2_from_thumb(a0, &data_0216717c);
    StructMapObject_MaybeSetPolygonId(data_0217b11c, 0x3f);
}
