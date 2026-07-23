/* Loads the Pakkun plant (piranha) body: model, polygon-id 0x3f and a
 * second property (0x1f) via StructMapObject_SomeFn_6. */
extern void *data_0217b10c;
extern char data_021669f0[];
extern void *CreateMapObjectFromModel_2_from_thumb(void *a0, void *a1);
extern void StructMapObject_MaybeSetPolygonId(void *obj, int id);
extern void StructMapObject_SomeFn_6(void *obj, int id);

void LoadPakkunBodyMapObject(void *a0) {
    void *obj = CreateMapObjectFromModel_2_from_thumb(a0, data_021669f0);
    data_0217b10c = obj;
    StructMapObject_MaybeSetPolygonId(obj, 0x3f);
    StructMapObject_SomeFn_6(data_0217b10c, 0x1f);
}
