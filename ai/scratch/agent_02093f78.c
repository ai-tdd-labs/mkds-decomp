// PURPOSE: Creates the NsKiller1 map object.
// The owner provides the map-object context.
// This probably stores the loaded model object for later use.

typedef struct MapObjectOwner MapObjectOwner;
typedef struct MapModelObject MapModelObject;

extern int data_021667b0;
extern MapModelObject *data_0217b0d4;
extern MapModelObject *CreateMapObjectFromModel_from_thumb(
    MapObjectOwner *owner, void *modelName);

void func_02093f78(MapObjectOwner *owner) {
    data_0217b0d4 = CreateMapObjectFromModel_from_thumb(owner, &data_021667b0);
}
