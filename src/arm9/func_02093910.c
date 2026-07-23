/* PURPOSE: Moves a falling/bouncing object each frame and removes it when its time runs out.
 *
 * Args: arg0 is a bit index/mask selector passed to func_0207a780 (probably the
 *   current camera/player mask); obj is the object being updated.
 * Behaviour: first sets or clears a visibility flag (bit 1 of obj->flags) based on
 *   whether obj->visMask overlaps the mask from func_0207a780; the set path ORs in
 *   a global u16 flag word (data_021564a8). Then, depending on obj->state:
 *   state 0: counts down obj->timer; while it lasts, picks a surface/collision code
 *     (either from obj->touchFlags or computed from the position) and reports it via
 *     func_0210b7ec, then advances the position by the velocity; when the timer drops
 *     below 0x24e it triggers effect 0x17d (probably a splash/despawn effect).
 *   state 1: counts down the same timer, applies gravity (vel.y -= 0x400) and moves.
 *   In both states a timer that already reached zero kills the object (func_020d2398).
 */

typedef unsigned short u16;
typedef unsigned int u32;
typedef struct { int x, y, z; } VecFx32;

typedef struct {
    u16 f0;
    u16 flags;              /* +0x02: bit1 = hidden/culled */
    VecFx32 pos;            /* +0x04 */
    VecFx32 vel;            /* +0x10 */
    char pad1c[0x74 - 0x1c];
    u32 visMask;            /* +0x74: visibility mask compared against func_0207a780 */
    u32 touchFlags;         /* +0x78: surface/collision flags, bit3 = valid */
    char pad7c[0xa0 - 0x7c];
    int timer;              /* +0xa0: remaining lifetime in frames */
    int state;              /* +0xa4: 0 = sliding on surface, 1 = falling */
    int soundHandle;        /* +0xa8: handle passed to func_0210b7ec */
} Obj;

extern volatile u16 data_021564a8;

extern int func_0207a780(int mask);
extern int func_020d4ef4(VecFx32 *pos);
extern void func_0210b7ec(int handle, u32 code);
extern void VecFx32_Add(VecFx32 *dst, VecFx32 *a, VecFx32 *b);
extern void func_020d275c(Obj *obj, int effect);
extern void func_020d2398(Obj *obj);

void func_02093910(int mask, Obj *obj)
{
    /* arm order matters: with the big OR arm as the THEN arm, mwcc predicates
       only the small else-arm (eq) and branches (beq) over the then-arm, exactly
       like the ROM; the opposite order predicates both arms */
    if ((obj->visMask & func_0207a780(mask)) != 0)
        obj->flags |= data_021564a8;    /* visible: OR in global flag bits */
    else
        obj->flags &= ~2;               /* not visible for this view */

    switch (obj->state) {
    case 0:
        if (obj->timer-- > 0) {
            if (!(obj->flags & 2) && (obj->touchFlags & 8)) {
                /* use the stored surface flags, stripped of control bits */
                func_0210b7ec(obj->soundHandle, obj->touchFlags & ~0xc000001f);
            } else {
                /* recompute the surface code from the current position */
                func_0210b7ec(obj->soundHandle, func_020d4ef4(&obj->pos));
            }
            VecFx32_Add(&obj->pos, &obj->vel, &obj->pos);
            if (obj->timer >= 0x24e)
                return;
            func_020d275c(obj, 0x17d);  /* near the end: trigger effect */
            return;
        }
        func_020d2398(obj);             /* lifetime over: destroy */
        return;
    case 1:
        if (obj->timer-- > 0) {
            obj->vel.y -= 0x400;        /* gravity */
            VecFx32_Add(&obj->pos, &obj->vel, &obj->pos);
            return;
        }
        func_020d2398(obj);
        return;
    }
}
