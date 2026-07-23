extern int data_02167190;
extern void *data_0217b170;

extern void *CreateMapObjectFromModel_2_from_thumb(void *a0, void *model);
extern void StructMapObject_MaybeSetPolygonId(void *obj, int polygonId);

void LoadNsCannon1MapObject(void *a0)
{
    data_0217b170 = CreateMapObjectFromModel_2_from_thumb(a0, &data_02167190);
    StructMapObject_MaybeSetPolygonId(data_0217b170, 0x3f);
}
