// PURPOSE: Loads the Pakkun Z head map object.
// The input is probably the map object's loading context.
// It creates the model from the PakkunZHead resource, stores the shared object,
// and applies the object's property value.
extern int data_02166a04;
extern void *data_0217b104;
extern void *CreateMapObjectFromModel_2_from_thumb(void *a0, void *a1);
extern void StructMapObject_SomeFn_6(void *obj, int id);

void LoadPakkunZHeadMapObject(void *a0)
{
    void *obj = CreateMapObjectFromModel_2_from_thumb(a0, &data_02166a04);

    data_0217b104 = obj;
    StructMapObject_SomeFn_6(obj, 0x1e);
}
