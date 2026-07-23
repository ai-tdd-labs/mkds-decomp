extern int data_021670fc;
extern void *data_0217b130;
extern void *CreateMapObjectFromModel_2_from_thumb(void *a0, void *a1);
extern void StructMapObject_MaybeSetPolygonId(void *obj, int id);
void LoadOlaTree1cMapObject(void *a0) {
    void *obj = CreateMapObjectFromModel_2_from_thumb(a0, &data_021670fc);
    data_0217b130 = obj;
    StructMapObject_MaybeSetPolygonId(obj, 0x3f);
}
