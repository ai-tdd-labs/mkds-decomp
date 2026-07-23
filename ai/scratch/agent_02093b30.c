/* PURPOSE: Load the NsKiller2 map-object model and its shadow variant, then tag the shadow with polygon id 0x3f.
 */
extern int data_02166748;
extern int data_02166758;
extern void *data_0217b0cc;
extern void *data_0217b0d0;
extern void *CreateMapObjectFromModel_from_thumb(void *a0, void *a1);
extern void *func_0209bd90(void *a0, void *a1);
extern void StructMapObject_MaybeSetPolygonId(void *obj, int id);

void LoadNsKiller2MapObject(void *a0) {
    data_0217b0cc = CreateMapObjectFromModel_from_thumb(a0, &data_02166748);
    data_0217b0d0 = func_0209bd90(a0, &data_02166758);
    StructMapObject_MaybeSetPolygonId(data_0217b0d0, 0x3f);
}
