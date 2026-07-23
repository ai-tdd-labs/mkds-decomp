/* PURPOSE: Spawns the sun model plus its low-detail (LOD) twin and gives
 * the sun a spinning animation and a unique polygon id.
 *
 * a0 is probably the map-object spawn context passed through to
 * CreateMapObjectFromModel_from_thumb. The near model uses "sun.nsbmd" and
 * gets an "sun.nsbca" animation attached; the LOD model uses
 * "sun_LOD.nsbmd" and has no animation. The near-model object is stashed
 * in data_0217b18c so its polygon id can be set from a running item
 * counter (GetIncrementSomeItemCounter), matching the pattern used by the
 * other Load*MapObject helpers.
 */
extern int data_02167388;  /* string "sun.nsbmd" */
extern int data_02167394;  /* string "sun.nsbca" */
extern int data_021673a0;  /* string "sun_LOD.nsbmd" */
extern void *data_0217b18c;
extern void *data_0217b188;
extern void *CreateMapObjectFromModel_from_thumb(void *a0, void *a1);
extern void StructMapObject_AddAnimationNsbca_from_thumb(void *obj, void *a1);
extern void StructMapObject_MaybeSetPolygonId(void *obj, int id);
extern int GetIncrementSomeItemCounter(void);

void LoadSunMapObject(void *a0) {
    void *obj = CreateMapObjectFromModel_from_thumb(a0, &data_02167388);
    data_0217b18c = obj;
    StructMapObject_AddAnimationNsbca_from_thumb(obj, &data_02167394);
    data_0217b188 = CreateMapObjectFromModel_from_thumb(a0, &data_021673a0);
    StructMapObject_MaybeSetPolygonId(data_0217b18c, GetIncrementSomeItemCounter());
}
