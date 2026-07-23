/* PURPOSE: Loads the crab map object's body and hand models.
 * Creates two model+animation sub-objects (body: crab.nsbmd/crab.nsbtp,
 * hand: crab_hand.nsbmd/crab_hand.nsbtp) under the map-object template
 * given in a0, stores each in its own global, and gives both sub-objects
 * polygon-id 0x3f. */
extern int data_02167228;
extern int data_02167234;
extern void *data_0217b178;
extern int data_02167240;
extern int data_02167250;
extern void *data_0217b174;
extern void *CreateMapObjectFromModelAndAnimation_from_thumb(void *a0, void *a1, void *a2);
extern void StructMapObject_MaybeSetPolygonId(void *obj, int id);

void LoadCrabMapObject(void *a0) {
    data_0217b178 = CreateMapObjectFromModelAndAnimation_from_thumb(a0, &data_02167228, &data_02167234);
    data_0217b174 = CreateMapObjectFromModelAndAnimation_from_thumb(a0, &data_02167240, &data_02167250);
    StructMapObject_MaybeSetPolygonId(data_0217b178, 0x3f);
    StructMapObject_MaybeSetPolygonId(data_0217b174, 0x3f);
}
