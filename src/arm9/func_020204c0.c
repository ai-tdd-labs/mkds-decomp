// PURPOSE: Checks whether an object contains a valid small header.
// The object probably holds a pending eight-byte header at offset 0x50.
// It is accepted only when the object has no linked entry and its values match.

typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

typedef struct HeaderObject {
    u8 _00[0x3C];
    u16 field_3C;
    u8 _3E[6];
    void *field_44;
    u8 _48[8];
    u8 header[8];
} HeaderObject;

extern void Mem_CpuCopy8(const void *source, void *destination, u32 size);
extern void DC_SomeClean(void *address, u32 size);

int func_020204c0(HeaderObject *object)
{
    volatile u16 header[4];

    if (object == 0)
        return 0;
    if (object->field_3C == 0)
        return 0;

    Mem_CpuCopy8(object->header, header, 8);
    DC_SomeClean(header, 8);

    if (object->field_44 == 0) {
        if (header[0] == 0x2348 || header[0] == 0xBD8A) {
            if (header[3] == 4)
                return 1;
        }
    }
    return 0;
}
