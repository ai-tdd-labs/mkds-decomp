extern int data_02167e14;
extern void *data_0217b33c;
extern void *CreateMapObjectFromModel_2_from_thumb(void *a0, void *a1);
extern void StructMapObject_MaybeSetPolygonId(void *obj, int id);
void LoadShineBalloonMapObject(void *a0) {
    void *obj = CreateMapObjectFromModel_2_from_thumb(a0, &data_02167e14);
    data_0217b33c = obj;
    StructMapObject_MaybeSetPolygonId(obj, 0x3f);
}
