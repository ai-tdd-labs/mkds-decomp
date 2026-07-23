/* Loads the TownMonte map object (model+animation), first sets a
 * callback pointer at offset 0x14 of the argument object, and gives the
 * object polygon-id 0x3f. */
extern int data_021675f8;
extern int data_02167608;
extern void *data_0217b1a8;
extern void func_0209fc2c(void);
extern void *CreateMapObjectFromModelAndAnimation_from_thumb(void *a0, void *a1, void *a2);
extern void StructMapObject_MaybeSetPolygonId(void *obj, int id);

void LoadTownMonteMapObject(void *a0) {
    *(void **)((char *)a0 + 0x14) = (void *)func_0209fc2c;
    data_0217b1a8 = CreateMapObjectFromModelAndAnimation_from_thumb(a0, &data_021675f8, &data_02167608);
    StructMapObject_MaybeSetPolygonId(data_0217b1a8, 0x3f);
}
