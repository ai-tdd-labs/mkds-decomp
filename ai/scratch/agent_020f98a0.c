// PURPOSE: Sets the light data used by an object.
// It copies two three-word values into the object.
// The optional light information is copied when supplied, otherwise it is probably initialized.

typedef unsigned short u16;

typedef struct Vec3i {
    int x;
    int y;
    int z;
} Vec3i;

typedef struct LightInfo {
    u16 value[9];
} LightInfo;

typedef struct ObjectLightData {
    char _00[0x7c];
    LightInfo lightInfo;
    char _8e[0x56];
    Vec3i first;
    Vec3i second;
    char _fc[0x1a];
    u16 mode;
} ObjectLightData;

extern void LightInfo_SomeFn(LightInfo *info, int enabled);

void func_020f98a0(ObjectLightData *object, const Vec3i *first,
                   const Vec3i *second, const LightInfo *lightInfo, int hasMode)
{
    object->first = *first;

    if (lightInfo != 0) {
        object->lightInfo = *lightInfo;
    } else {
        LightInfo_SomeFn(&object->lightInfo, 1);
    }

    object->second = *second;
    object->mode = hasMode != 0 ? 0 : 5;
}
