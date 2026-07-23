/* PURPOSE: Load the two "picture" map objects (models + nsbca animations) and set their polygon id.
 */
extern int data_021674d4;
extern int data_021674e4;
extern int data_021674f4;
extern int data_02167504;
extern void *data_0217b198;
extern void *data_0217b19c;
extern void *CreateMapObjectFromModel_from_thumb(void *a0, void *a1);
extern void StructMapObject_AddAnimationNsbca_from_thumb(void *obj, void *a1);
extern void StructMapObject_MaybeSetPolygonId(void *obj, int id);

void LoadPictureMapObjects(void *a0) {
    void *obj1 = CreateMapObjectFromModel_from_thumb(a0, &data_021674d4);
    data_0217b198 = obj1;
    StructMapObject_AddAnimationNsbca_from_thumb(obj1, &data_021674e4);
    void *obj2 = CreateMapObjectFromModel_from_thumb(a0, &data_021674f4);
    data_0217b19c = obj2;
    StructMapObject_AddAnimationNsbca_from_thumb(obj2, &data_02167504);
    StructMapObject_MaybeSetPolygonId(data_0217b198, 0x3f);
    StructMapObject_MaybeSetPolygonId(data_0217b19c, 0x3f);
}
