// PURPOSE: Loads the fireball map object and marks its owner ready.
// The argument points to the owning object, whose ready flag is at offset 0x1c.
// It probably creates the fireball model, saves it globally, and assigns polygon ID 0x3f.

extern char data_02167418[];
extern void *data_0217b190;
extern void *CreateMapObjectFromModel_2_from_thumb(void *a0, void *a1);
extern void StructMapObject_MaybeSetPolygonId(void *obj, int id);

void func_0209e950(int *a0) {
    StructMapObject_MaybeSetPolygonId(data_0217b190 = CreateMapObjectFromModel_2_from_thumb(a0, data_02167418), 0x3f);
    a0[7] = 1;
}
