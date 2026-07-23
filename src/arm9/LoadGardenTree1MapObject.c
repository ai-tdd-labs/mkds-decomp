extern int data_02167154;
extern void *data_0217b118;
extern void *CreateMapObjectFromModel_2_from_thumb(void *a0, void *a1);
extern void StructMapObject_MaybeSetPolygonId(void *obj, int id);
void LoadGardenTree1MapObject(void *a0) {
    void *obj = CreateMapObjectFromModel_2_from_thumb(a0, &data_02167154);
    data_0217b118 = obj;
    StructMapObject_MaybeSetPolygonId(obj, 0x3f);
}
