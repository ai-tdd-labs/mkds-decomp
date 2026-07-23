/* PURPOSE: Flush a buffer, look up the P/E-main texture entry for a model, then DMA its data out. */

typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

typedef struct StructF9C {
    u8 pad_00[0x10];
    void *f10; /* holder; resource file pointer at +4 */
} StructF9C;

extern char data_02154ff8[]; /* "P_main" */
extern char data_02155068[]; /* "E_main" */

extern void Arm_FlushRange(void *addr, u32 size);
extern int DetermineIsP_from_thumb(void *a);
extern int Dict_SomeFn_0(void *dict, char *name);
extern void func_0214c48c(u32 entryval);
extern void SomeDmaCopy_0(void *ptr, u32 offset, u32 size);
extern void func_0214c3c0(void);

void func_02077f9c(void *a, StructF9C *holder, void *dst)
{
    u8 *res = *(u8 **)((u8 *)holder->f10 + 4);
    u8 *dict;
    u8 *entbase;
    u32 eofs;
    u8 *ent;
    u32 esz;
    u8 *item;
    u32 size;
    u32 entryval;
    int idx;

    Arm_FlushRange(dst, 0x20);

    if (DetermineIsP_from_thumb(a)) {
        idx = Dict_SomeFn_0(res + *(int *)(res + 8) + 4, data_02154ff8);
    } else {
        idx = Dict_SomeFn_0(res + *(int *)(res + 8) + 4, data_02155068);
    }

    dict = res + *(int *)(res + 8);
    entbase = dict + 4;
    eofs = *(u16 *)(dict + 0xa);
    ent = entbase + eofs;
    esz = *(u16 *)ent;
    item = dict + *(int *)(ent + esz * idx + 4);
    entryval = *(u16 *)(item + 0x1c);

    size = entryval << 4;
    func_0214c48c(entryval);
    SomeDmaCopy_0(dst, size, 0x20);
    func_0214c3c0();
}
