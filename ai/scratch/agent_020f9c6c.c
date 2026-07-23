// PURPOSE: Caches a collision entry for a race object.
// The argument is a race object with a position, height, and collision entry ID.
// If the ID is unset, this probably finds and stores the matching collision entry.

typedef struct RaceObject {
    unsigned char pad_000[0x50];
    int collisionPosition[3];
    unsigned char pad_05c[0x7e];
    signed short collisionEntryId;
    unsigned char pad_0dc[4];
    int collisionHeight;
} RaceObject;

extern int FindComputeSomeCollisionEntryId(
    int *position,
    int height,
    int searchRadius,
    void *owner);

void func_020f9c6c(RaceObject *object)
{
    if (object->collisionEntryId != -1) {
        return;
    }

    object->collisionEntryId = FindComputeSomeCollisionEntryId(
        object->collisionPosition,
        object->collisionHeight,
        0x4000,
        object);
}
