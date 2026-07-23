/* Loads the flamethrower/burner effect (mkd_ef_burner): model +
 * nsbta animation, polygon-id 0x3f, and sets a ready flag (field 0x1c). */
extern int data_02166720;
extern int data_02166734;
extern void *data_0217b0c8;
extern void *CreateMapObjectFromModel_from_thumb(void *a0, void *a1);
extern void StructMapObject_AddAnimationNsbta_from_thumb(void *obj, void *a1);
extern void StructMapObject_MaybeSetPolygonId(void *obj, int id);

void func_02093708(int *a0) {
    void *obj = CreateMapObjectFromModel_from_thumb(a0, &data_02166720);
    data_0217b0c8 = obj;
    StructMapObject_AddAnimationNsbta_from_thumb(obj, &data_02166734);
    StructMapObject_MaybeSetPolygonId(data_0217b0c8, 0x3f);
    a0[7] = 1;
}
