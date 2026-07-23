extern int data_02167168;
extern void *data_0217b144;

extern void *CreateMapObjectFromModel_2_from_thumb(void *a0, void *model);
extern void StructMapObject_MaybeSetPolygonId(void *obj, int polygonId);

void LoadBankTree1MapObject(void *a0)
{
    data_0217b144 = CreateMapObjectFromModel_2_from_thumb(a0, &data_02167168);
    StructMapObject_MaybeSetPolygonId(data_0217b144, 0x3f);
}
