extern int data_02167144;
extern void *data_0217b124;
extern void *CreateMapObjectFromModel_2_from_thumb(void *a0, void *a1);
extern void StructMapObject_MaybeSetPolygonId(void *obj, int id);
void LoadTownTree1MapObject(void *a0) {
    void *obj = CreateMapObjectFromModel_2_from_thumb(a0, &data_02167144);
    data_0217b124 = obj;
    StructMapObject_MaybeSetPolygonId(obj, 0x3f);
}
