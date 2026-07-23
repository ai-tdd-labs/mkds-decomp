/* PURPOSE: Advances an object's countdown/position timer and, once it
 * reaches zero or below, resets it and calls func_020d2398 to trigger
 * whatever happens next (probably a state/step transition).
 *
 * r0 is a pointer to some object struct. r1 is stored verbatim into
 * field 0xa4 (probably a callback or state pointer). r2 is negated and
 * added onto field 0xd0 (probably a running counter/position, field
 * 0xd4 used as scratch to hold the negated delta). If the updated
 * counter is still > 0, the function returns early. Otherwise it
 * clears several fields, marks field 0xa4 with -1 (probably "no
 * callback"), sets field 0xf4 to 1 (probably a flag) and clears
 * field 0xf8, then calls func_020d2398(r0).
 */

extern void func_020d2398(void *obj);

#define FIELD(base, off) (*(int *)((unsigned char *)(base) + (off)))

void func_020a2f30(void *r0, void *r1, int r2)
{
    FIELD(r0, 0xa4) = (int)r1;
    FIELD(r0, 0xd4) = -r2;
    FIELD(r0, 0xd0) = FIELD(r0, 0xd0) + FIELD(r0, 0xd4);
    FIELD(r0, 0xfc) = 0;

    if (FIELD(r0, 0xd0) > 0) {
        return;
    }

    FIELD(r0, 0xd8) = 0;
    FIELD(r0, 0xd0) = 0;
    FIELD(r0, 0xa4) = -1;
    FIELD(r0, 0xf4) = 1;
    FIELD(r0, 0xf8) = 0;
    func_020d2398(r0);
}
