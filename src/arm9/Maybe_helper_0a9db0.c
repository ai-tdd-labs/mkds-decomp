extern int data_021679e8;
extern void *data_0217b230;
extern void *CreateMapObjectFromModel_2_from_thumb(void *a0, void *a1);
extern void StructMapObject_MaybeSetPolygonId(void *obj, int id);
void Maybe_helper_0a9db0(void *a0) {
    void *obj = CreateMapObjectFromModel_2_from_thumb(a0, &data_021679e8);
    data_0217b230 = obj;
    StructMapObject_MaybeSetPolygonId(obj, 0x3f);
}
