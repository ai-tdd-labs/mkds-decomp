/* Loads the 'cover' map object: three sub-objects (2x model, 1x
 * model+animation), stores them in globals and sets polygon-id 0x3f on
 * the second and third object. */
extern int data_02166928;
extern int data_02166934;
extern int data_02166940;
extern int data_0216694c;
extern void *data_0217b0f0;
extern void *data_0217b0f4;
extern void *data_0217b0ec;
extern void *CreateMapObjectFromModel_2_from_thumb(void *a0, void *a1);
extern void *CreateMapObjectFromModelAndAnimation_from_thumb(void *a0, void *a1, void *a2);
extern void StructMapObject_MaybeSetPolygonId(void *obj, int id);

void func_02096d68(void *a0) {
    data_0217b0f0 = CreateMapObjectFromModel_2_from_thumb(a0, &data_02166928);
    data_0217b0f4 = CreateMapObjectFromModelAndAnimation_from_thumb(a0, &data_02166934, &data_02166940);
    data_0217b0ec = CreateMapObjectFromModel_2_from_thumb(a0, &data_0216694c);
    StructMapObject_MaybeSetPolygonId(data_0217b0f4, 0x3f);
    StructMapObject_MaybeSetPolygonId(data_0217b0ec, 0x3f);
}
