// PURPOSE: Loads a kart emblem image and its palette into video memory.
// The character selects a kart model, while the other arguments point to the
// image and palette destinations. The function probably prepares the VRAM
// transfer state before copying both emblem resources.

typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

extern char data_02155a54[];

extern void *GetCharacterKartModel(u16 character);
extern int Dict_SomeFn_0(void *dict, char *name);
extern void Arm_FlushRange(void *buffer, u32 size);
extern void func_0214c6a8(void);
extern void func_0214c544(void *ptr, u32 offset, u32 size);
extern void func_0214c4d4(void);
extern void func_0214c48c(void);
extern void SomeDmaCopy_0(void *dst, u32 offset, u32 size);
extern void func_0214c3c0(void);

void DriverContext_SetupEmblem_from_thumb(u16 character, void *image_dst,
                                           void *palette_dst)
{
    u8 *model;
    u8 *dict;
    u8 *entry_base;
    u32 entry_offset;
    u8 *entry;
    u32 entry_size;
    u8 *item;
    u32 image_offset;
    u32 palette_offset;
    int index;

    model = GetCharacterKartModel(character);
    index = Dict_SomeFn_0(model + *(u32 *)(model + 8) + 4, data_02155a54);
    dict = model + *(u32 *)(model + 8);
    entry_base = dict + 4;
    entry_offset = *(u16 *)(dict + 0xa);
    entry = entry_base + entry_offset;
    entry_size = *(u16 *)(entry_base + entry_offset);
    item = dict + *(u32 *)(entry + entry_size * index + 4);
    image_offset = *(u32 *)(item + 0x14) & 0xffff;
    image_offset <<= 3;
    palette_offset = (u32)*(u16 *)(item + 0x1c) << 4;

    Arm_FlushRange(image_dst, 0x200);
    Arm_FlushRange(palette_dst, 0x20);
    func_0214c6a8();
    func_0214c544(image_dst, image_offset, 0x200);
    func_0214c4d4();
    func_0214c48c();
    SomeDmaCopy_0(palette_dst, palette_offset, 0x20);
    func_0214c3c0();
}
