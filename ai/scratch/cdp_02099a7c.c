extern int data_021670ec;
extern void *data_0217b12c;
extern void *CreateMapObjectFromModel_2_from_thumb(void *a0, void *a1);
extern void StructMapObject_MaybeSetPolygonId(void *obj, int id);
void LoadOsaTree1cMapObject(void *a0) {
    void *obj = CreateMapObjectFromModel_2_from_thumb(a0, &data_021670ec);
    data_0217b12c = obj;
    StructMapObject_MaybeSetPolygonId(obj, 0x3f);
}
