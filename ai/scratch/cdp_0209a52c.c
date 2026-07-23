extern int data_021671c0;
extern void *data_0217b16c;
extern void *CreateMapObjectFromModel_2_from_thumb(void *a0, void *a1);
extern void StructMapObject_MaybeSetPolygonId(void *obj, int id);
void LoadOlgMush1MapObject(void *a0) {
    void *obj = CreateMapObjectFromModel_2_from_thumb(a0, &data_021671c0);
    data_0217b16c = obj;
    StructMapObject_MaybeSetPolygonId(obj, 0x3f);
}
