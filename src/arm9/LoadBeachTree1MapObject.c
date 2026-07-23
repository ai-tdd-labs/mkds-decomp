extern int data_021671e0;
extern void *data_0217b150;
extern void *CreateMapObjectFromModel_2_from_thumb(void *a0, void *a1);
extern void StructMapObject_MaybeSetPolygonId(void *obj, int id);
void LoadBeachTree1MapObject(void *a0) {
    void *obj = CreateMapObjectFromModel_2_from_thumb(a0, &data_021671e0);
    data_0217b150 = obj;
    StructMapObject_MaybeSetPolygonId(obj, 0x3f);
}
