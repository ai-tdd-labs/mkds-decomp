/* Loads the rain star object (RainStar): model + nsbta animation and
 * polygon-id 0x3f. */
extern void *data_0217b1a0;
extern char data_02167548[];
extern char data_02167558[];
extern void *CreateMapObjectFromModel_from_thumb(void *a0, void *a1);
extern void StructMapObject_AddAnimationNsbta_from_thumb(void *obj, void *name);
extern void StructMapObject_MaybeSetPolygonId(void *obj, int id);

void LoadRainStarMapObject(void *a0) {
    void *obj = CreateMapObjectFromModel_from_thumb(a0, data_02167548);
    data_0217b1a0 = obj;
    StructMapObject_AddAnimationNsbta_from_thumb(obj, data_02167558);
    StructMapObject_MaybeSetPolygonId(data_0217b1a0, 0x3f);
}
