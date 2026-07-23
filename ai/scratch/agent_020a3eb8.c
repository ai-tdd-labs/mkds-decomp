/* PURPOSE: Loads the balloon map object (balloon.nsbmd + balloon.nsbtp).
 * Behaviour: creates the map object from its model and animation, stores it in
 * a global, then configures it (polygon-id 0x3f and two further properties
 * 0x1a and 0) and finally marks the caller's struct ready (field 0x1c = 1). */
extern void *data_0217b204;     /* the created balloon map object */
extern char data_02167878[];    /* "balloon.nsbmd" */
extern char data_02167888[];    /* "balloon.nsbtp" */

extern void *CreateMapObjectFromModelAndAnimation_from_thumb(void *a0, void *model, void *anim);
extern void StructMapObject_MaybeSetPolygonId(void *obj, int id);
extern void StructMapObject_SomeFn_6(void *obj, int a);
extern void StructMapObject_SomeFn_7(void *obj, int a);

void LoadBalloonMapObject(int *a0) {
    void *obj = CreateMapObjectFromModelAndAnimation_from_thumb(a0, data_02167878, data_02167888);
    data_0217b204 = obj;
    StructMapObject_MaybeSetPolygonId(obj, 0x3f);
    StructMapObject_SomeFn_6(data_0217b204, 0x1a);
    StructMapObject_SomeFn_7(data_0217b204, 0);
    a0[7] = 1;
}
