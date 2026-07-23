// PURPOSE: Loads the bound map object and its animation.
// The owner supplies the map-object context.
// This probably stores the object globally for later updates.

typedef struct MapObjectOwner MapObjectOwner;
typedef struct MapModelObject MapModelObject;

extern int data_0216733c;
extern int data_02167348;
extern MapModelObject *data_0217b184;
extern MapModelObject *CreateMapObjectFromModel_from_thumb(
    MapObjectOwner *owner, void *modelName);
extern void StructMapObject_AddAnimationNsbtp_from_thumb(void *obj, void *a1);

void func_0209c878(MapObjectOwner *owner) {
    StructMapObject_AddAnimationNsbtp_from_thumb(
        data_0217b184 = CreateMapObjectFromModel_from_thumb(owner, &data_0216733c),
        &data_02167348);
}
