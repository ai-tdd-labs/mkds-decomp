/* PURPOSE: Copies a character's main palette from its resource file into a buffer.
 *
 * func_02077f9c(name, holderSlot, dst): resource file lives at
 * *(holderSlot+0x10)+4. Flushes the 0x20-byte dst buffer from cache, looks up
 * "P_main" or "E_main" in the file's palette dictionary depending on
 * DetermineIsP_from_thumb(name), takes the entry's u16 field at +0x1c shifted
 * left by 4 as the palette offset, and copies 0x20 bytes to dst via
 * SomeDmaCopy_0, bracketed by func_0214c48c / func_0214c3c0 (probably VRAM
 * map/unmap).
 */

typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

extern char data_02154ff8[]; /* "P_main" */
extern char data_02155068[]; /* "E_main" */

extern void Arm_FlushRange(void *ptr, u32 size);
extern int DetermineIsP_from_thumb(void *name);
extern int Dict_SomeFn_0(void *dict, char *name);
extern void func_0214c48c(void);
extern void SomeDmaCopy_0(void *dst, u32 offset, u32 size);
extern void func_0214c3c0(void);

void func_02077f9c(void *name, void *holderSlot, void *dst)
{
    u8 *res;
    u8 *dict;
    u8 *entbase;
    u32 eofs;
    u8 *ent;
    u32 esz;
    u32 plttOfs;
    int idx;

    /* resource file lives at holder(+0x10) + 4 */
    res = *(u8 **)((u8 *)*(void **)((u8 *)holderSlot + 0x10) + 4);

    Arm_FlushRange(dst, 0x20);

    if (DetermineIsP_from_thumb(name) != 0) {
        idx = Dict_SomeFn_0(res + *(int *)(res + 8) + 4, data_02154ff8);
    } else {
        idx = Dict_SomeFn_0(res + *(int *)(res + 8) + 4, data_02155068);
    }

    dict = res + *(int *)(res + 8);      /* reload after the call */
    entbase = dict + 4;
    eofs = *(u16 *)(dict + 0xa);         /* offset of the entry block */
    ent = entbase + eofs;
    esz = *(u16 *)(entbase + eofs);      /* per-entry stride */
    plttOfs = (u32)*(u16 *)(dict + *(int *)(ent + esz * idx + 4) + 0x1c) << 4;

    func_0214c48c();
    SomeDmaCopy_0(dst, plttOfs, 0x20);
    func_0214c3c0();
}
