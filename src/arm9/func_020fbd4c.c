// PURPOSE: Updates an object's movement values for the current race configuration.
// The object probably stores a direction vector, its length, and a fixed movement limit.
// It also applies state 0xdd when an object value matches the selected race setting.

typedef signed char s8;
typedef unsigned short u16;
typedef int fx32;

typedef struct VecFx32 {
    fx32 x;
    fx32 y;
    fx32 z;
} VecFx32;

typedef struct Object {
    char padding_000[0x5c];
    VecFx32 vector;
    char padding_068[0x1c0];
    void *field_228;
    char padding_22c[0x44];
    int field_270;
    char padding_274[8];
    int field_27c;
    char padding_280[4];
    int field_284;
} Object;

typedef struct RaceConfig {
    char padding_00[0x62];
    s8 field_62;
} RaceConfig;

extern RaceConfig *gRaceConfig;
extern fx32 VecFx32_Norm(const VecFx32 *v);

void func_020fbd4c(Object *object)
{
    object->field_27c = VecFx32_Norm(&object->vector);
    object->field_284 = 0x1e000;

    if (*(u16 *)((char *)object->field_228 + 0x1f8) == gRaceConfig->field_62) {
        object->field_270 = 0xdd;
    }
}
