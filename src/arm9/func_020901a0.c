/*
 * PURPOSE: Skip an object's per-frame update unless a global gate check passes and its state field is below a threshold.
 */

extern int func_0207c078(void);
extern void func_0207c614(void *obj0, void *obj1);

struct Obj70 {
    char pad[0x70];
    int state;
};

void func_020901a0(void *obj0, struct Obj70 *obj1)
{
    if (func_0207c078() == 0) {
        return;
    }

    if (obj1->state >= 0xa000) {
        return;
    }

    func_0207c614(obj0, obj1);
}
