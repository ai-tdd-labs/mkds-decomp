// PURPOSE: Loads the cow map object and gives it its polygon ID.
// Arguments: a0 is probably the map-object creation context.
// The model and animation names are supplied by the ROM data symbols.
// The created object is retained globally for later use.

extern int data_021665f8;
extern int data_02166604;
extern void *data_0217b0bc;
extern void *CreateMapObjectFromModelAndAnimation_from_thumb(void *a0, void *a1, void *a2);
extern void StructMapObject_MaybeSetPolygonId(void *obj, int id);

void LoadCowMapObject(void *a0) {
    void *obj = CreateMapObjectFromModelAndAnimation_from_thumb(a0, &data_021665f8, &data_02166604);
    data_0217b0bc = obj; // Preserve the loaded cow object.
    StructMapObject_MaybeSetPolygonId(obj, 0x3f);
}
