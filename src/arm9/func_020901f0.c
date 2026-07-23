/*
 * PURPOSE: Fires a kart-object event unless the object is still cloaked and its timer has not elapsed yet.
 *
 * a0 (r5) is forwarded verbatim to the event callee.
 * a1 (r4) points at a struct with a boolean-ish flag at +0xb0 and a
 * signed counter/state field at +0x70.
 * If func_0207c078() reports "not active" (0) AND the flag at +0xb0 is
 * also 0, the function bails out early.
 * Otherwise, if the counter at +0x70 has not yet reached 0xa000, the
 * event callee func_0207c614(a0, a1) is invoked.
 */

extern int func_0207c078(void);
extern void func_0207c614(void *a0, void *a1);

typedef struct {
    char pad_0x00[0x70];
    int field_0x70;
    char pad_0x74[0xb0 - 0x74];
    int field_0xb0;
} Obj0209;

void func_020901f0(void *a0, Obj0209 *a1)
{
    if (func_0207c078() == 0) {
        if (a1->field_0xb0 == 0) {
            return;
        }
    }

    if (a1->field_0x70 >= 0xa000) {
        return;
    }

    func_0207c614(a0, a1);
}
