extern int data_02167680;
extern void *data_0217b1f8;
extern void *CreateMapObjectFromModel_from_thumb(void *a0, void *a1);
extern void StructMapObject_MaybeSetPolygonId(void *obj, int id);
void LoadAirshipMapObject(void *a0) {
    void *obj = CreateMapObjectFromModel_from_thumb(a0, &data_02167680);
    data_0217b1f8 = obj;
    StructMapObject_MaybeSetPolygonId(obj, 0x3f);
}
