extern int data_0216717c;
extern void *data_0217b11c;
extern void *CreateMapObjectFromModel_2_from_thumb(void *a0, void *a1);
extern void StructMapObject_MaybeSetPolygonId(void *obj, int id);
void LoadCrossTree1MapObject(void *a0) {
    void *obj = CreateMapObjectFromModel_2_from_thumb(a0, &data_0216717c);
    data_0217b11c = obj;
    StructMapObject_MaybeSetPolygonId(obj, 0x3f);
}
