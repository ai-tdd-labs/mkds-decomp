extern int data_0216706c;
extern void *data_0217b164;
extern void *CreateMapObjectFromModel_2_from_thumb(void *a0, void *a1);
extern void StructMapObject_MaybeSetPolygonId(void *obj, int id);
void LoadBankEgg1MapObject(void *a0) {
    void *obj = CreateMapObjectFromModel_2_from_thumb(a0, &data_0216706c);
    data_0217b164 = obj;
    StructMapObject_MaybeSetPolygonId(obj, 0x3f);
}
