// PURPOSE: Initializes an object's direction state and reaction state.
// The first argument is probably the object being initialized, and the second
// argument is probably its related tracked object. It initializes the embedded
// tracker at offset 8, then applies reaction mode 1 twice.

typedef struct DirectionTracker DirectionTracker;
typedef struct TrackedObject TrackedObject;
typedef struct Obj Obj;

extern void func_02080cd0(DirectionTracker *tracker, TrackedObject *object);
extern void func_0207f9cc(Obj *obj, int mode);

void func_0207e564(Obj *obj, TrackedObject *object)
{
    // The direction tracker is embedded eight bytes into the object.
    func_02080cd0((DirectionTracker *)((char *)obj + 8), object);
    func_0207f9cc(obj, 1);
    func_0207f9cc(obj, 1);
}
