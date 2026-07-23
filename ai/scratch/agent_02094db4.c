/* Spawns the Boo map object (teresa): model+animation, polygon-id 0x3f,
 * and sets a ready flag in the argument object (field 0x1c). */
extern int data_021667f4;
extern int data_02166804;
extern void *data_0217b0dc;
extern void *CreateMapObjectFromModelAndAnimation_from_thumb(void *a0, void *a1, void *a2);
extern void StructMapObject_MaybeSetPolygonId(void *obj, int id);

void func_02094db4(int *a0) {
    StructMapObject_MaybeSetPolygonId(data_0217b0dc = CreateMapObjectFromModelAndAnimation_from_thumb(a0, &data_021667f4, &data_02166804), 0x3f);
    a0[7] = 1;
}
