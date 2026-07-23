extern int data_02167130;
extern void *data_0217b134;

extern void *CreateMapObjectFromModel_2_from_thumb(void *a0, void *model);
extern void StructMapObject_MaybeSetPolygonId(void *obj, int polygonId);

void LoadMarioTree3MapObject(void *a0)
{
    data_0217b134 = CreateMapObjectFromModel_2_from_thumb(a0, &data_02167130);
    StructMapObject_MaybeSetPolygonId(data_0217b134, 0x3f);
}
