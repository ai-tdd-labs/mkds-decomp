/* PURPOSE: Advances a map object's animation frame counters once per update.
 *
 * Args: a0 = unused (kept only because the ROM prototype has it),
 *       obj = the map object whose counters get advanced.
 * Behaviour: obj->fa0 (a 16-bit frame counter) is incremented; once it
 *   reaches the limit returned by StructMapObject_SomeFn_2() (probably a
 *   per-object animation frame count/speed) it wraps back to 0. Separately,
 *   obj->f7e (probably an angle/phase accumulator) is advanced by a fixed
 *   step of 0x111 every call, with no wraparound.
 */

typedef unsigned short u16;

typedef struct {
    char _0[0x7e];
    u16  f7e;   /* 0x7e: phase/angle accumulator, += 0x111 per call */
    char _80[0xa0 - 0x80];
    u16  fa0;   /* 0xa0: frame counter, wraps to 0 at the animation limit */
} MapObject;

extern unsigned short StructMapObject_SomeFn_2(void *handle);
extern void *data_0217b1a0;   /* shared render handle (pointer global) */

void func_0209f178(void *a0, MapObject *obj)
{
    unsigned short limit = StructMapObject_SomeFn_2(data_0217b1a0);

    obj->fa0 = obj->fa0 + 1;
    if (obj->fa0 >= limit) {
        obj->fa0 = 0;
    }

    obj->f7e = obj->f7e + 0x111;
}
