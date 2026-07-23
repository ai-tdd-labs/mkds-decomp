// PURPOSE: Applies a collision response when the racer's state allows it.
// The first argument is the racer entry and the second describes the collision plane.
// It rejects disabled racer states, orients the plane normal, and starts the response.

typedef int fx32;

typedef struct VecFx32 {
    fx32 x;
    fx32 y;
    fx32 z;
} VecFx32;

typedef struct StructMQRacerEntry {
    char pad_00[0x48];
    unsigned int field_48;
    unsigned int field_4c;
    char pad_50[0x7c - 0x50];
    unsigned int field_7c;
    VecFx32 field_80;
    char pad_8c[0x180 - 0x8c];
    int field_180;
} StructMQRacerEntry;

typedef struct CollisionPlane {
    char pad_00[4];
    VecFx32 field_04;
    char pad_10[0x28 - 0x10];
    VecFx32 field_28;
    VecFx32 field_34;
    VecFx32 field_40;
} CollisionPlane;

extern void VecFx32_Subtract(const VecFx32 *a, const VecFx32 *b,
                             VecFx32 *out);
extern void VecFx32_CrossProduct(const VecFx32 *a, const VecFx32 *b,
                                 VecFx32 *out);
extern fx32 Vector3_DotProduct(const VecFx32 *a, const VecFx32 *b);
extern void StructMQRacerEntry_SomeFn_59(StructMQRacerEntry *entry,
                                          const VecFx32 *normal, int mode);

int func_0206b020(StructMQRacerEntry *entry, CollisionPlane *plane)
{
    int result;
    VecFx32 normal;
    VecFx32 difference;
    VecFx32 cross;

    if ((entry->field_4c & 0x400000) != 0) {
        result = 0;
        goto result_ready;
    }
    if ((entry->field_7c & 0x200) == 0) {
        goto inactive;
    }
    if (entry->field_180 != 0) {
        goto active_fail;
    }
    if ((entry->field_48 & 0x1800) != 0) {
        goto active_fail;
    }
    if ((entry->field_4c & 0x10000040) == 0) {
        result = 1;
        goto result_ready;
    }

active_fail:
    result = 0;
    goto result_ready;

inactive:
    {
        int allowed = 1;

        if ((entry->field_4c & 0x10000040) == 0) {
            if ((entry->field_48 & 0x1800) == 0) {
                int state = entry->field_180;
                int other = 0;

                if (state != 0) {
                    if (state != 1) {
                        if (state != 2) {
                            other = allowed;
                        }
                    }
                }
                if (other == 0) {
                    allowed = 0;
                }
            }
        }
        if (allowed == 0) {
            result = 1;
        } else {
            result = 0;
        }
    }

result_ready:
    if (result == 0) {
        return 0;
    }

    normal = plane->field_28;
    VecFx32_Subtract(&entry->field_80, &plane->field_04, &difference);
    VecFx32_CrossProduct(&plane->field_40, &difference, &cross);
    if (Vector3_DotProduct(&cross, &plane->field_34) < 0) {
        normal.x = -normal.x;
        normal.y = -normal.y;
        normal.z = -normal.z;
    }
    StructMQRacerEntry_SomeFn_59(entry, &normal, 0);
    return 1;
}
