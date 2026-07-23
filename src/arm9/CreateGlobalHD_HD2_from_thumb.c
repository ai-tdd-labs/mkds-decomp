/* PURPOSE: Creates the main route-following state used during a race.
It allocates and initializes one global state object from the active heap.
The object probably receives the current course route and prepares its route helper.
If no route exists, it marks the shared race state instead.
*/

typedef struct CourseRoute {
    unsigned char padding_00[0x40];
    short pathIndex;
} CourseRoute;

typedef struct CoursePathState {
    unsigned char padding_00[0xc4];
    CourseRoute *route;
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

void CreateGlobalHD_HD2_from_thumb(void)
{
    data_0217acb8 = Mem_AllocateHeap(
        ExecutionContext_GetHeapHandle(GetActiveExecutionContext()),
        sizeof(GlobalHD));
    data_0217aca4 = 0;
    StructHD_SomeFn(data_0217acb8);

    data_0217acb8->route = data_02175620->route;
    data_0217acb8->field_250 = 2;
    data_0217acb8->field_24c = 0;

    if (data_0217acb8->route == 0) {
        data_0217561c->missingRoute = 1;
    } else if (data_0217acb8->route->pathIndex != -1) {
        StructVC_SomeFnLinkedRouteRelated(
            data_0217acb8->routeHelper,
            data_0217acb8->route);
    }
}
