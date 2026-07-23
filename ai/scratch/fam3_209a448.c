extern int data_021671b0;
extern void *data_0217b14c;

extern void *CreateMapObjectFromModel_2_from_thumb(void *a0, void *model);
extern void StructMapObject_MaybeSetPolygonId(void *obj, int polygonId);

void LoadOlgPipe1MapObject(void *a0)
{
    data_0217b14c = CreateMapObjectFromModel_2_from_thumb(a0, &data_021671b0);
    StructMapObject_MaybeSetPolygonId(data_0217b14c, 0x3f);
}
