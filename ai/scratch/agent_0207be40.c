// PURPOSE: Copies the first four route entries for an object's path.
typedef unsigned short u16;

typedef struct {
    int x;
    int y;
    int z;
} NkmPathEntry;

typedef struct {
    NkmPathEntry entries[4];
    int field30;
    int field34;
    int field38;
} RouteOutput;

typedef struct {
    char pad00[8];
    void *pathTable;
} CoursePathState;

typedef struct {
    char pad00[0x40];
    u16 pathId;
} RouteObject;

extern CoursePathState *data_02175620;
extern NkmPathEntry *GetLoadedNkmPathEntryPOIT(u16 pathId, int index);

void StructVC_SomeFnLinkedRouteRelated(RouteOutput *output, RouteObject *object)
{
    unsigned short i;
    CoursePathState *state = data_02175620;
    void *pathTable = state->pathTable;
    u16 pathId = object->pathId;

    output->field30 = 0;
    output->field34 = 0;
    output->field38 = 0;

    if (*(u16 *)((char *)pathTable + ((int)pathId << 2) + 2) < 4) {
        return;
    }

    for (i = 0; i < 4; i++) {
        output->entries[i] = *GetLoadedNkmPathEntryPOIT(object->pathId, i);
        output->field34 = i;
    }
}
