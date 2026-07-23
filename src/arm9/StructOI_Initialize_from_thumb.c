// PURPOSE: Initializes an object-information record to its default state.

typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

typedef struct StructOI {
    u16 field_00;
    u16 field_02;
    u16 field_04;
    u16 field_06;
    u16 field_08;
    u16 field_0a;
    u16 field_0c;
    u8 field_0e[0x14];
    u8 field_22_bit0 : 1;
    u8 field_22_bit1 : 1;
    u8 field_22_bit2 : 1;
    u8 field_22_bit3 : 1;
    u8 field_22_high : 4;
    u8 field_23;
} StructOI;

extern void Mem_CpuFill8(void *destination, int value, u32 size);

void StructOI_Initialize_from_thumb(StructOI *object)
{
    Mem_CpuFill8(object, 0, 0x24);

    object->field_00 = 0;
    object->field_02 = 0;
    object->field_04 = 0;
    object->field_06 = 0;
    object->field_08 = 0;
    object->field_0a = 0;
    object->field_0c &= ~0x7f;
    object->field_0c = (object->field_0c & ~0x780) | 0x80;
    object->field_0c = (object->field_0c & ~0xf800) | 0x0800;

    Mem_CpuFill8(object->field_0e, 0, 0x14);

    object->field_22_bit0 = 0;
    object->field_22_bit1 = 0;
    object->field_22_bit2 = 0;
    object->field_22_bit3 = 0;
}
