// PURPOSE: Loads the Kanoke map object and its animation.
// The owner supplies the map-object context.
// This probably retains the object globally for later updates.

typedef struct MapObjectOwner MapObjectOwner;
typedef struct MapModelObject MapModelObject;

extern int data_02166644;
extern int data_02166654;
extern MapModelObject *data_0217b0c0;
extern MapModelObject *CreateMapObjectFromModel_from_thumb(
    MapObjectOwner *owner, void *modelName);
extern void StructMapObject_AddAnimationNsbca_from_thumb(void *obj, void *a1);

void func_02092140(MapObjectOwner *owner) {
    StructMapObject_AddAnimationNsbca_from_thumb(
        data_0217b0c0 = CreateMapObjectFromModel_from_thumb(owner, &data_02166644),
        &data_02166654);
}
