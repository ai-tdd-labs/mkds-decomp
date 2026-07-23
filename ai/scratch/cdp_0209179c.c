extern int data_021665b4;
extern void *data_0217b0b8;
extern void *CreateMapObjectFromModel_2_from_thumb(void *a0, void *a1);
extern void StructMapObject_MaybeSetPolygonId(void *obj, int id);
void LoadSmanTopMapObject(void *a0) {
    void *obj = CreateMapObjectFromModel_2_from_thumb(a0, &data_021665b4);
    data_0217b0b8 = obj;
    StructMapObject_MaybeSetPolygonId(obj, 0x3f);
}
