/* PURPOSE: Creates two route-following states for the current course.
 * It allocates and initializes both global state objects from the active heap.
 * Each object probably receives one of the course's two route variants.
 * Missing routes are reported through the shared race state.
 */

typedef struct CourseRoute {
    unsigned char padding_00[0x40];
    short pathIndex;
} CourseRoute;

typedef struct CoursePathState {
    unsigned char padding_00[0xc4];
    CourseRoute *route;
    CourseRoute *route2;
} CoursePathState;

typedef struct GlobalHD {
    unsigned char padding_000[0x194];
    unsigned char routeHelper[0x84];
    CourseRoute *route;
    unsigned char padding_21c[0x30];
    int field_24c;
    int field_250;
    unsigned char padding_254[0x1c];
} GlobalHD;

typedef struct RaceState {
    unsigned char padding_000[0x4d0];
    int missingRoute;
} RaceState;

extern GlobalHD *data_0217acb8;
extern GlobalHD *data_0217aca4;
extern CoursePathState *data_02175620;
extern RaceState *data_0217561c;

extern void *GetActiveExecutionContext(void);
extern void *ExecutionContext_GetHeapHandle(void *context);
extern void *Mem_AllocateHeap(void *heap, unsigned int size);
extern void StructHD_SomeFn(GlobalHD *state);
extern void StructVC_SomeFnLinkedRouteRelated(void *helper, CourseRoute *route);

void CreateGlobalHD_HD2_V2_from_thumb(void)
{
    void *heap;

    heap = ExecutionContext_GetHeapHandle(GetActiveExecutionContext());
    data_0217acb8 = Mem_AllocateHeap(heap, sizeof(GlobalHD));
    data_0217aca4 = Mem_AllocateHeap(heap, sizeof(GlobalHD));

    StructHD_SomeFn(data_0217acb8);
    StructHD_SomeFn(data_0217aca4);

    data_0217acb8->route = data_02175620->route;
    data_0217aca4->route = data_02175620->route2;
    data_0217acb8->field_250 = 2;
    data_0217aca4->field_250 = 2;

    if (data_0217acb8->route == 0) {
        data_0217561c->missingRoute = 1;
    } else {
        if (data_0217acb8->route->pathIndex != -1) {
            StructVC_SomeFnLinkedRouteRelated(
                data_0217acb8->routeHelper,
                data_0217acb8->route);
        }
        if (data_0217aca4->route->pathIndex != -1) {
            StructVC_SomeFnLinkedRouteRelated(
                data_0217aca4->routeHelper,
                data_0217aca4->route);
        }
    }
}
