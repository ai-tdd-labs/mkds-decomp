// PURPOSE: Stores a small record in the first free temporary slot.
// The first two arguments become record bytes, while the last two provide optional data.
// The record buffer is cleared before the optional data is copied into it.
// The global work area and the record purpose are probably related to temporary race data.

typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

typedef struct {
    void *unknown_00;
    void *buffer;
    u8 in_use;
    u8 value_09;
    u8 value_0a;
    u8 data_size;
} Record;

typedef struct {
    u8 padding_000[0x324];
    Record records[16];
    u8 padding_3e4[0x344];
    void *unknown_728;
} RecordWork;

extern RecordWork *data_0217aa14;
extern void Mem_CpuFill8(void *destination, int value, u32 size);
extern void Mem_CpuCopy8(const void *source, void *destination, u32 size);

void func_0205a858(u8 value_09, u8 value_0a, const void *source, u8 data_size)
{
    u16 i;
    Record *record;

    for (i = 0; i < 16; i++) {
        record = &data_0217aa14->records[i];
        if (record->in_use == 0) {
            goto found;
        }
    }
    record = 0;

found:
    record->value_09 = value_09;
    record->value_0a = value_0a;
    record->in_use = 1;
    record->unknown_00 = (u8 *)data_0217aa14->unknown_728 + 0x28;
    Mem_CpuFill8(record->buffer, 0, 0x14);
    if (data_size == 0) {
        record->data_size = 0;
        return;
    }
    Mem_CpuCopy8(source, record->buffer, data_size);
    record->data_size = data_size;
}
