/* PURPOSE: Initializes a linked-route work record for an object.
 * The source selects a course path and supplies the signed route value.
 * The destination stores the source, two status values, and cleared pointers.
 * Paths with at least four points also initialize both embedded work areas.
 */

typedef unsigned char u8;
typedef unsigned short u16;
typedef signed short s16;

typedef struct NkmPathRecord {
    u16 firstPointIndex;
    u16 pointCount;
} NkmPathRecord;

typedef struct CoursePathState {
    u8 unknown_00[8];
    NkmPathRecord *paths;
} CoursePathState;

typedef struct LinkedRouteSource {
    u8 unknown_00[0x40];
    u16 pathIndex;
    s16 routeValue;
} LinkedRouteSource;

typedef struct LinkedRouteWork {
    LinkedRouteSource *source;
    u8 work_04[0x3c];
    u8 work_40[0x3c];
    s16 routeValue;
    u16 state;
    void *unknown_80;
    void *unknown_84;
} LinkedRouteWork;

extern CoursePathState *data_02175620;
extern void StructVC_SomeFnLinkedRouteRelated(void *work);
extern void func_0207bd6c(void *work, LinkedRouteSource *source);

void func_02077750(LinkedRouteWork *work, LinkedRouteSource *source)
{
    NkmPathRecord *path = &data_02175620->paths[source->pathIndex];

    work->routeValue = source->routeValue;
    work->state = 2;
    work->source = source;
    work->unknown_80 = 0;
    work->unknown_84 = 0;

    if (path->pointCount >= 4) {
        StructVC_SomeFnLinkedRouteRelated(work->work_04);
        func_0207bd6c(work->work_40, source);
    }
}
