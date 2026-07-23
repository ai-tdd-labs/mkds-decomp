/*
PURPOSE: Tells every object in a manager's list to update, skipping ones
that already have a "done" flag set.
Looks up the manager for kind 0x6a, then walks its object array calling
func_020d2398 on each entry whose flags field does not have bit 0x100 set.
The scan stops early either when it hits a NULL slot in the array (returns 0)
or when it finishes the whole count (returns the count). If the manager
itself does not exist yet, returns 0 immediately.
*/

typedef struct Obj020a5848 {
    unsigned char pad0[2];
    unsigned short flags;
} Obj020a5848;

typedef struct Mgr020a5848 {
    Obj020a5848 **arr;
    unsigned short count;
} Mgr020a5848;

extern Mgr020a5848 *func_02100138(int kind);
extern void func_020d2398(Obj020a5848 *obj);

int func_020a5848(void)
{
    Mgr020a5848 *m = func_02100138(0x6a);
    if (m == 0) {
        return 0;
    }

    int i;
    Obj020a5848 *o;

    i = 0;
    while (i < m->count) {
        o = m->arr[i];
        if (o == 0) {
            return 0;
        }
        if (!(o->flags & 0x100)) {
            func_020d2398(o);
        }
        i++;
    }

    return m->count;
}
