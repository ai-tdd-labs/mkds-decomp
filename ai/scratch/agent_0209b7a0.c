// PURPOSE: Mirrors a map object's model on the requested axes.
// The second and third arguments select horizontal and vertical mirroring.
// Optional render data receives matching orientation and culling settings.
// The race direction probably reverses the required culling mode.

typedef struct StructMapObject_Sub {
    char pad_0x00[0x14];
    unsigned int flags;
} StructMapObject_Sub;

typedef struct StructMapObject {
    int scale_x;
    int scale_y;
    int field_0x08;
    StructMapObject_Sub *sub;
    void *model;
} StructMapObject;

typedef struct RaceConfig {
    char pad_0x00[0x57];
    signed char mirrored;
} RaceConfig;

extern RaceConfig *gRaceConfig;
extern void Model_SetCullMode(void *model, int mode);

void StructMapObject_SomeFn_8(StructMapObject *object, int mirror_x,
                              int mirror_y)
{
    if (object->sub != 0) {
        if (((mirror_x != 0 || mirror_y != 0) ^
             gRaceConfig->mirrored) != 0) {
            object->sub->flags &= ~0x80;
            object->sub->flags |= 0x40;
        } else {
            object->sub->flags |= 0x80;
            object->sub->flags &= ~0x40;
        }
    }

    if (object->model != 0) {
        if (((mirror_x != 0 || mirror_y != 0) ^
             gRaceConfig->mirrored) != 0) {
            Model_SetCullMode(object->model, 1);
        } else {
            Model_SetCullMode(object->model, 2);
        }
    }

    object->scale_x = mirror_x != 0 ? -0x1000 : 0x1000;
    object->scale_y = mirror_y != 0 ? -0x1000 : 0x1000;
}
