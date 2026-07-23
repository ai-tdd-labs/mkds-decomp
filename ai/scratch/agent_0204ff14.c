// PURPOSE: Returns a selected context record when it is available.

typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

typedef struct ContextRecord {
    u8 valid;
    u8 padding_01[0xdf];
} ContextRecord;

typedef struct UnkStruct_0217aa00 {
    ContextRecord records[];
} UnkStruct_0217aa00;

extern UnkStruct_0217aa00 *data_0217aa00;
extern void Mem_CpuCopy8(const void *source, void *destination, u32 size);

int func_0204ff14(int slot, void *output)
{
    UnkStruct_0217aa00 *context;
    u8 *record;
    int zero = 0;
    int state;

    context = data_0217aa00;
    state = context == 0 ? zero : *(int *)context;

    if (state != 2) {
        return 0;
    }

    if (*(volatile u16 *)0x027ffc40 == 2) {
        return 0;
    }

    record = (u8 *)&context->records[slot];
    if ((record[0x188] & 1) != 0) {
        if (output != 0) {
            Mem_CpuCopy8(record + 0x188, output, 0x14);
        }
        return 1;
    }

    return 0;
}
