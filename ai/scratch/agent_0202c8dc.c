/*
PURPOSE: Fills empty racer name slots with numbered CPU labels.
It loads the localized CPU label from common.bmg, then fills every slot from
the current racer count through slot seven. Each label receives a digit based
on its position relative to the first empty slot.
*/

typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

typedef struct {
    u16 name[11];
    u8 padding[0x16];
} RacerNameSlot;

typedef struct {
    u8 padding_00[0x48];
    int racer_count;
    u8 padding_4c[0x14];
    RacerNameSlot racer_names[8];
} RacerNameWork;

extern void *func_020b47cc(void *name);
extern u16 *Bmg_GetRawStringPointer_from_thumb(void *bmg, int message_id);
extern void Mem_CpuFill16(u16 value, void *destination, u32 size);
extern void CopyMemory16(const void *source, void *destination, u32 size);
extern void SomeStrcat16(u16 *destination, const u16 *source, int flag);

extern char data_02162c58[];
extern RacerNameWork *data_02174e3c;

void func_0202c8dc(void)
{
    volatile u16 fill_value;
    u16 number_suffix[2] = {0, 0};
    u16 *cpu_label;
    int racer_index;

    cpu_label = Bmg_GetRawStringPointer_from_thumb(func_020b47cc(data_02162c58), 0x72);

    for (racer_index = data_02174e3c->racer_count; racer_index < 8; racer_index++) {
        fill_value = 0;
        Mem_CpuFill16(fill_value, data_02174e3c->racer_names[racer_index].name, 0x16);
        CopyMemory16(cpu_label, data_02174e3c->racer_names[racer_index].name, 0x14);

        number_suffix[0] = racer_index + 0x31 - data_02174e3c->racer_count;
        SomeStrcat16(data_02174e3c->racer_names[racer_index].name, number_suffix, 1);
    }
}
