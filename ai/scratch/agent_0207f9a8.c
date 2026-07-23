// PURPOSE: Initializes an object's tracker and reaction state.
// The first argument owns the tracker area at offset 8 and is also initialized.
// The second argument is probably the object whose direction is recorded.
// A mode value of one is then used for the object's reaction setup.

typedef struct Obj Obj;
typedef struct DirectionTracker DirectionTracker;
typedef struct TrackedObject TrackedObject;

extern void func_02080cd0(DirectionTracker *tracker, TrackedObject *object);
extern void func_0207f9cc(Obj *obj, int mode);

void func_0207f9a8(Obj *obj, TrackedObject *object)
{
    func_02080cd0((DirectionTracker *)((char *)obj + 8), object);
    func_0207f9cc(obj, 1);
}
