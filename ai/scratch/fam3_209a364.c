extern int data_021671a0;
extern void *data_0217b15c;

extern void *CreateMapObjectFromModel_2_from_thumb(void *a0, void *model);
extern void StructMapObject_MaybeSetPolygonId(void *obj, int polygonId);

void LoadOf6Yoshi1MapObject(void *a0)
{
    data_0217b15c = CreateMapObjectFromModel_2_from_thumb(a0, &data_021671a0);
    StructMapObject_MaybeSetPolygonId(data_0217b15c, 0x3f);
}
