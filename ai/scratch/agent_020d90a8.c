// PURPOSE: Updates a route cursor and caches its neighboring path points.
/*
 * The second argument selects a route position and the third chooses direction.
 * The route descriptor probably controls whether the path wraps at its ends.
 * The object stores the current segment scale and pointers to two POIT entries.
 */

typedef unsigned short u16;

typedef struct RouteEntry {
    unsigned char pad00[0x34];
    int scale;
    unsigned char pad38[0x54 - 0x38];
} RouteEntry;

typedef struct RouteDescriptor {
    RouteEntry *entries;
    int count;
    int wraps;
} RouteDescriptor;

typedef struct RouteCursor {
    RouteDescriptor *route;
    int baseScale;
    u16 pathId;
    u16 pad0a;
    int entryIndex;
    int segmentScale;
    int directionOffset;
    int direction;
    void *point;
    void *nextPoint;
} RouteCursor;

extern void *GetLoadedNkmPathEntryPOIT(u16 pathId, int index);

void func_020d90a8(RouteCursor *cursor, int position, int direction)
{
    RouteDescriptor *route = cursor->route;
    int pointIndex;
    int entryScale;
    u16 nextIndex;

    if (route->wraps != 0) {
        if (position == 0 && direction == 0) {
            position = (u16)route->count;
        }
    } else {
        if (position == 0 && direction == 0) {
            direction = 1;
        } else if (position == route->count && direction != 0) {
            direction = 0;
        }
    }

    cursor->entryIndex = direction != 0 ? position : position - 1;

    entryScale = route->entries[cursor->entryIndex].scale;
    cursor->segmentScale = entryScale != 0
        ? (int)(((long long)cursor->baseScale * entryScale) >> 12)
        : 0x1000000;
    cursor->directionOffset = direction != 0 ? 0 : 0x1000000;
    cursor->direction = direction;

    pointIndex = position;
    if (cursor->direction == 0) {
        if (route->wraps != 0 && position == route->count) {
            pointIndex = 0;
        }
    }
    cursor->point = GetLoadedNkmPathEntryPOIT(cursor->pathId, pointIndex);

    nextIndex = cursor->direction != 0 ? position + 1 : position - 1;
    if (cursor->direction != 0) {
        if (route->wraps != 0 && nextIndex == route->count) {
            nextIndex = 0;
        }
    }
    cursor->nextPoint = GetLoadedNkmPathEntryPOIT(cursor->pathId, nextIndex);
}
