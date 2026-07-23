/* Loads the moving tree (move_tree): model + nsbca animation and
 * polygon-id 0x3f. */
extern int data_021668d4;
extern int data_021668e4;
extern void *data_0217b0e8;
extern void *CreateMapObjectFromModel_from_thumb(void *a0, void *a1);
extern void StructMapObject_AddAnimationNsbca_from_thumb(void *obj, void *a1);
extern void StructMapObject_MaybeSetPolygonId(void *obj, int id);
void LoadMoveTreeMapObject(void *a0) {
    void *obj = CreateMapObjectFromModel_from_thumb(a0, &data_021668d4);
    data_0217b0e8 = obj;
    StructMapObject_AddAnimationNsbca_from_thumb(obj, &data_021668e4);
    StructMapObject_MaybeSetPolygonId(data_0217b0e8, 0x3f);
}
