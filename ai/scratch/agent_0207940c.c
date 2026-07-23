/* PURPOSE: Loads a kart body palette into its character palette slot.
 *
 * The character number selects a palette slot in dst.  Only every third
 * character uses this body palette; the source is probably an NCLR entry.
 */

#pragma optimize_for_size on

typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

typedef struct KartModel {
    u8 pad_00[4];
    u8 *resource;
} KartModel;

extern char data_02155088[];

extern int _s32_div_f(int numerator, int denominator);
extern void Arm_FlushRange(void *ptr, u32 size);
extern int Dict_SomeFn_0(void *dict, char *name);
extern void func_0214c48c(void);
extern void SomeDmaCopy_0(void *dst, u32 offset, u32 size);
extern void func_0214c3c0(void);

void LoadKartBodyPalette_from_thumb(KartModel *model, int character, u8 *dst)
{
    u8 *resource;
    u8 *dict;
    u8 *entry_base;
    u32 entry_offset;
    u8 *entry;
    u32 entry_size;
    u32 palette_offset;
    int index;

    if (character % 3 != 0)
        return;

    resource = model->resource;
    dst += (character / 3) << 5;
    Arm_FlushRange(dst, 0x10);

    index = Dict_SomeFn_0(resource + *(int *)(resource + 8) + 4,
                          data_02155088);
    dict = resource + *(int *)(resource + 8);
    entry_base = dict + 4;
    entry_offset = *(u16 *)(dict + 0xa);
    entry = entry_base + entry_offset;
    entry_size = *(u16 *)(entry_base + entry_offset);
    palette_offset = (u32)*(u16 *)(dict + *(int *)(entry + entry_size * index + 4) + 0x1c) << 4;

    func_0214c48c();
    SomeDmaCopy_0(dst, palette_offset, 0x10);
    func_0214c3c0();
}
