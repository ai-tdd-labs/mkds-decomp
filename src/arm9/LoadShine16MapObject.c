// PURPOSE: Loads the Shine 16 map object and its animation.
// The argument is probably the map object's owner or placement data.
// It creates the model with its texture animation, stores the result globally,
// and assigns the standard polygon ID.

extern char data_021678cc[];
extern char data_021678dc[];
extern void *data_0217b224;
extern void *CreateMapObjectFromModelAndAnimation_from_thumb(void *a0, void *a1, void *a2);
extern void StructMapObject_MaybeSetPolygonId(void *obj, int id);

void LoadShine16MapObject(void *a0) {
    void *obj = CreateMapObjectFromModelAndAnimation_from_thumb(a0, data_021678cc, data_021678dc);
    data_0217b224 = obj;
    StructMapObject_MaybeSetPolygonId(obj, 0x3f);
}
