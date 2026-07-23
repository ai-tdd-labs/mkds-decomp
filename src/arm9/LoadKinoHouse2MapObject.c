extern int data_021670c4;
extern void *data_0217b128;
extern void *CreateMapObjectFromModel_2_from_thumb(void *a0, void *a1);
extern void StructMapObject_MaybeSetPolygonId(void *obj, int id);
void LoadKinoHouse2MapObject(void *a0) {
    void *obj = CreateMapObjectFromModel_2_from_thumb(a0, &data_021670c4);
    data_0217b128 = obj;
    StructMapObject_MaybeSetPolygonId(obj, 0x3f);
}
