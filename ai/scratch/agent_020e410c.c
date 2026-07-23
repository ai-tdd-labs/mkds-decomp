// PURPOSE: Updates distances between consecutive type 0xCB objects in a list.

typedef unsigned short u16;
typedef unsigned char u8;
typedef int fx32;

typedef struct VecFx32 {
    fx32 x;
    fx32 y;
    fx32 z;
} VecFx32;

typedef struct ObjectRecord {
    u16 type;
    u8 _02[2];
    VecFx32 position;
    u8 _10[0x48];
    fx32 f58;
    u8 _5c[0xDC];
    fx32 f138;
    u8 _13c[0x18];
    fx32 f154;
} ObjectRecord;

typedef struct ObjectList {
    ObjectRecord **objects;
    u16 count;
} ObjectList;

extern void VecFx32_Subtract(const VecFx32 *a, const VecFx32 *b, VecFx32 *out);
extern fx32 VecFx32_Norm(const VecFx32 *vector);

void func_020e410c(ObjectList *list)
{
    int i;
    int previous = -1;
    int zero = 0;
    int zero_z = 0;
    VecFx32 difference;
    ObjectRecord **objects = list->objects;

    if (list->count > 0) {
        for (i = 0; i < list->count; i++) {
            ObjectRecord *object = objects[i];

            if (object->type == 0xCB) {
                if (previous < 0) {
                    object->f138 = zero;
                } else {
                    VecFx32_Subtract(&objects[previous]->position,
                        &object->position, &difference);
                    difference.z = zero_z;
                    object->f154 = VecFx32_Norm(&difference);
                    object->f138 = object->f154 - objects[previous]->f58;
                }
                previous = i;
            }
        }
    }
}
