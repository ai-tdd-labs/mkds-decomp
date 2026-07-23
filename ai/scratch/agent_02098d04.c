/* Loads the Pakkun plant mouth: model + bite animation (nsbca) and a
 * property (0x1f) via StructMapObject_SomeFn_6. */
extern int data_02166a18;
extern int data_02166a2c;
extern void *data_0217b100;
extern void *CreateMapObjectFromModel_from_thumb(void *a0, void *a1);
extern void StructMapObject_AddAnimationNsbca_from_thumb(void *obj, void *a1);
extern void StructMapObject_SomeFn_6(void *obj, int a1);

void func_02098d04(void *a0) {
    void *obj = CreateMapObjectFromModel_from_thumb(a0, &data_02166a18);
    data_0217b100 = obj;
    StructMapObject_AddAnimationNsbca_from_thumb(obj, &data_02166a2c);
    StructMapObject_SomeFn_6(data_0217b100, 0x1f);
}
