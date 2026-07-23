/* PURPOSE: Detaches or releases the objects tied to a racer entry.
 *
 * Argument: a racer-control object whose flags are at +0x4c and whose
 *   racer index is the u16 at +0x74.
 * If bit 0x8000 of flags is set: look up the racer's effect/model id in
 *   data_0217ae8c and release/activate that effect slot via func_02083a24.
 * Otherwise: for each of the two object pointers stored at +0x20 and +0x24
 *   in the racer entry, mark the pointed-to object at +0x99 and clear the
 *   pointer from the entry.
 */

typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

typedef struct RacerCtrl {
    char pad00[0x4c];
    u32 flags;   /* 0x4c */
    char pad50[0x74 - 0x50];
    u16 idx;     /* 0x74 */
} RacerCtrl;

typedef struct RacerEntry {
    char pad00[0x20];
    u8 *p20;     /* 0x20 */
    u8 *p24;     /* 0x24 */
    char pad28[0x58 - 0x28];
} RacerEntry;

extern u16 *data_0217ae8c;
extern void *data_02155968;      /* effect-slot array, stride 0xc */
extern RacerEntry *data_0217ae84;
extern void func_02083a24(void *slot, int mode);

void func_02083ec4(RacerCtrl *obj)
{
    RacerCtrl *c = obj;
    u32 flags = c->flags;

    if (flags & 0x8000) {
        u16 id = data_0217ae8c[c->idx];
        void *slot = (u8 *)data_02155968 + id * 0xc;
        func_02083a24(slot, 1);
    } else {
        RacerEntry *e = &data_0217ae84[c->idx];
        u8 *p;

        p = e->p20;
        if (p) {
            p[0x99] = 1;
            e->p20 = 0;
        }

        p = e->p24;
        if (p) {
            p[0x99] = 1;
            e->p24 = 0;
        }
    }
}
