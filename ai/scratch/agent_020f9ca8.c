/* PURPOSE: Caches the collision entry for a race object.
 * Takes the race object whose collision entry may need initialization.
 * If its entry ID is unset, this probably searches near its position and
 * stores the resulting ID for later collision queries.
 */

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

void func_020f9ca8(RaceObject *object)
{
    if (object->collisionEntryId != -1) {
        return;
    }

    object->collisionEntryId = FindComputeSomeCollisionEntryId(
        object->collisionPosition,
        object->collisionHeight + 0xa000,
        0x4000,
        object);
}
