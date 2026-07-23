/* PURPOSE: Spawns the "bakubaku" (Chain Chomp) map object plus its shadow
 * model and registers both with the map's polygon-id system.
 *
 * a0 is probably the map-object spawn/placement info passed straight
 * through to both model-creation calls. The two created objects are
 * stored into fixed global slots (data_0217b0e4 = main model,
 * data_0217b0e0 = shadow model) and each gets its polygon id set to
 * the same constant (0x3f).
 */

extern char data_0216687c[];  /* string "bakubaku.nsbmd" */
extern char data_0216688c[];  /* string "baku_shadow.nsbmd" */
extern void *data_0217b0e4;   /* stored main object pointer */
extern void *data_0217b0e0;   /* stored shadow object pointer */

extern void *CreateMapObjectFromModel_from_thumb(void *a0, char *modelName);
extern void *func_0209bd90(void *a0, char *modelName);
extern void StructMapObject_MaybeSetPolygonId(void *obj, int id);

void LoadBakubakuMapObject(void *a0) {
    /* ROM reloads through the globals rather than through locals for the
       polygon-id calls below, so write every step through data_X. */
    data_0217b0e4 = CreateMapObjectFromModel_from_thumb(a0, data_0216687c);
    data_0217b0e0 = func_0209bd90(a0, data_0216688c);
    StructMapObject_MaybeSetPolygonId(data_0217b0e4, 0x3f);
    StructMapObject_MaybeSetPolygonId(data_0217b0e0, 0x3f);
}
