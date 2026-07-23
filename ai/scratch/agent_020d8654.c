// PURPOSE: Builds sideways directions for every point along an object's route.
/*
 * The object supplies a route index at offset 0x26.
 * The function allocates one direction vector for every point on that route.
 * A final direction is produced only when the route loops back to its start.
 */

typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef int fx32;

typedef struct VecFx32 {
    fx32 x;
    fx32 y;
    fx32 z;
} VecFx32;

typedef struct NkmPathRecord {
    u8 firstPoint;
    u8 loops;
    u16 pointCount;
} NkmPathRecord;

typedef struct CoursePathState {
    u8 pad00[8];
    NkmPathRecord *paths;
} CoursePathState;

typedef struct RouteObject {
    u8 pad00[0x26];
    u16 routeId;
} RouteObject;

extern CoursePathState *data_02175620;

extern void *GetActiveExecutionContext(void);
extern void *ExecutionContext_GetHeapHandle(void *context);
extern void *Mem_AllocateHeap(void *heap, unsigned int size);
extern VecFx32 *GetLoadedNkmPathEntryPOIT(u16 routeId, int pointIndex);
extern void VecFx32_Subtract(const VecFx32 *a, const VecFx32 *b,
                             VecFx32 *out);
extern void Vector3_MaybeNormalize(const VecFx32 *in, VecFx32 *out);

VecFx32 *func_020d8654(RouteObject *object)
{
    u16 routeId = object->routeId;
    u16 pointCount = data_02175620->paths[routeId].pointCount;
    VecFx32 *directions = Mem_AllocateHeap(
        ExecutionContext_GetHeapHandle(GetActiveExecutionContext()),
        pointCount * sizeof(VecFx32));
    u16 pointIndex = 0;

    if (pointIndex < pointCount) {
        volatile int routeOffset = routeId << 2;
        int lastIndex = pointCount - 1;
        volatile int firstIndex = 0;
        fx32 zero = 0;
        volatile int finalIndex = (u16)lastIndex;
        VecFx32 direction;

        do {
            if (pointIndex == lastIndex) {
                if (*((u8 *)data_02175620->paths + routeOffset + 1) == 0)
                    goto advance;

                VecFx32_Subtract(
                    GetLoadedNkmPathEntryPOIT(routeId, firstIndex),
                    GetLoadedNkmPathEntryPOIT(routeId, finalIndex),
                    &direction);
            } else {
                VecFx32_Subtract(
                    GetLoadedNkmPathEntryPOIT(routeId,
                                               (u16)(pointIndex + 1)),
                    GetLoadedNkmPathEntryPOIT(routeId, pointIndex),
                    &direction);
            }

            {
                fx32 x = direction.x;
                fx32 z = direction.z;

                direction.z = -x;
                direction.y = zero;
                direction.x = z;
                direction.y = zero;
            }

            Vector3_MaybeNormalize(&direction, &directions[pointIndex]);

        advance:
            pointIndex++;
        } while (pointIndex < pointCount);
    }

    return directions;
}
