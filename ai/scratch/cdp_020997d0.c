extern int data_021670b0;
extern void *data_0217b120;
extern void *CreateMapObjectFromModel_2_from_thumb(void *a0, void *a1);
extern void StructMapObject_MaybeSetPolygonId(void *obj, int id);
void LoadKinoMount1MapObject(void *a0) {
    void *obj = CreateMapObjectFromModel_2_from_thumb(a0, &data_021670b0);
    data_0217b120 = obj;
    StructMapObject_MaybeSetPolygonId(obj, 0x3f);
}
