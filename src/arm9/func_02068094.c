// PURPOSE: Marks a racer after a successful collision response.
// The first argument is probably a racer entry.
// The second argument is unused, and the third describes the collision plane.
// An enabled racer flag also increments a probably global counter.

typedef struct StructMQRacerEntry {
    char pad_00[0x48];
    unsigned int field_48;
    char pad_4c[0x7c - 0x4c];
    unsigned int field_7c;
} StructMQRacerEntry;

typedef struct CollisionPlane CollisionPlane;

typedef struct GlobalRK {
    char pad_00[0x14];
    int field_14;
} GlobalRK;

extern int func_0206b020(StructMQRacerEntry *entry, CollisionPlane *plane);
extern GlobalRK *GetGlobalRK(void);

void func_02068094(StructMQRacerEntry *entry, int unused,
                   CollisionPlane *plane)
{
    if (func_0206b020(entry, plane) == 0) {
        return;
    }

    if ((entry->field_7c & 1) != 0) {
        GetGlobalRK()->field_14++;
    }
    entry->field_48 |= 0x20000;
}
