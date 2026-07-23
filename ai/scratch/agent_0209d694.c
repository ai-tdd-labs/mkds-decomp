/*
 * PURPOSE: Spawns an effect object at a position and sets up its two sprite parts.
 *
 * Arguments: pos (r0) = pointer to a 3-component fx32 vector (position),
 *            vel (r1) = pointer to a 3-component fx32 vector (probably velocity/direction).
 * Behaviour: plays/queues something with id 0x1ae (probably a sound or effect id),
 * allocates an effect entry; on failure returns. Otherwise stores type 0x1c2,
 * copies pos into two slots, copies vel, packs each vel component through a
 * 64-bit shift ((v<<13)>>12, i.e. v*2 with the high bits folded), creates two
 * sub-objects with ids 0x35 and 0x34, sets their fields, clears some flags and
 * sets a timer/state of 0x1f.
 */

typedef int fx32;
typedef long long fx64;
typedef unsigned short u16;
typedef unsigned char u8;

typedef struct VecFx32 {
    fx32 x, y, z;
} VecFx32;

typedef struct SubObj {
    char pad0[0x70];
    u16 field70;      /* mode/state halfword */
    char pad72[0xe];
    u8 field80;       /* small state byte */
} SubObj;

typedef struct EffectObj {
    char pad0[0x2];
    u16 flags2;         /* +0x02: bit flags, several bits cleared here */
    VecFx32 pos04;      /* +0x04: working position */
    VecFx32 scaled10;   /* +0x10: packed/scaled copy of vel */
    char pad1c[0x24];
    VecFx32 vel40;      /* +0x40: velocity/direction copy */
    char pad4c[0x1a];
    u16 timer66;        /* +0x66: countdown/state, set to 0x1f */
    char pad68[0x38];
    u16 type_a0;        /* +0xa0: type id (0x1c2) */
    char pada2[0x2];
    int field_a4;       /* +0xa4: cleared */
    VecFx32 posA8;      /* +0xa8: original spawn position */
    char padb4[0x4];
    int field_b8;       /* +0xb8: cleared */
    SubObj *part_bc;    /* +0xbc: first sprite part (id 0x35) */
    SubObj *part_c0;    /* +0xc0: second sprite part (id 0x34) */
} EffectObj;

extern void func_02100138(int id);
extern EffectObj *func_0209bbfc(void);
extern SubObj *func_0208b7bc(int id, VecFx32 *pos);

void func_0209d694(VecFx32 *pos, VecFx32 *vel)
{
    EffectObj *obj;

    func_02100138(0x1ae); /* probably an effect/sound id from the literal pool */
    obj = func_0209bbfc();
    if (obj == 0) {
        return;
    }
    obj->type_a0 = 0x1c2;
    obj->posA8 = *pos;
    obj->pos04 = obj->posA8; /* re-read from the struct, matches ROM double ldm */
    obj->vel40 = *vel;
    /* pack each component through a 64-bit shift: (v << 13) >> 12 */
    obj->scaled10.x = (fx32)(((fx64)vel->x << 13) >> 12);
    obj->scaled10.y = (fx32)(((fx64)vel->y << 13) >> 12);
    obj->scaled10.z = (fx32)(((fx64)vel->z << 13) >> 12);
    obj->field_a4 = 0;
    obj->field_b8 = 0;
    obj->part_bc = func_0208b7bc(0x35, &obj->pos04);
    obj->part_c0 = func_0208b7bc(0x34, &obj->pos04);
    obj->part_bc->field70 = 0x15;
    obj->part_c0->field70 = 0x15;
    obj->part_bc->field80 = 3;
    obj->part_c0->field80 = 3;
    obj->flags2 = obj->flags2 & ~1;
    obj->flags2 = obj->flags2 & ~8;
    obj->flags2 = obj->flags2 & ~2;
    obj->flags2 = obj->flags2 & ~8; /* duplicate clear, present in ROM */
    obj->timer66 = 0x1f;
}
