// PURPOSE: Initializes the game's temporary record tables.
// It clears sixteen groups of four records and sixteen related records.
// Each record receives state 15 and its attached 0x14-byte buffer is cleared.
// The exact table purpose is probably related to temporary race data.

typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

typedef struct Record {
    u32 unknown_00;
    void *buffer;
    u8 unknown_08;
    u8 state;
    u8 unknown_0a;
    u8 unknown_0b;
} Record;

typedef struct RecordWork {
    u8 padding_000[0x324];
    Record records_a[16];
    Record records_b[16][4];
    u8 record_flags[16][4];
    u16 record_count;
} RecordWork;

extern RecordWork *data_0217aa14;
extern void Mem_CpuFill8(void *destination, int value, u32 size);

void func_0205ad88(void)
{
    int group;
    int group_offset;
    volatile int record_offset;
    int record;
    int record_in_group;
    volatile int first_record;

    group = 0;
    group_offset = group;
    record_offset = group;
    first_record = group;

    do {
        record = first_record;
        record_in_group = record;
        do {
            ((Record *)((u8 *)data_0217aa14 + 0x3e4 + group_offset
                        + record_in_group))->unknown_08 = 0;
            ((Record *)((u8 *)data_0217aa14 + 0x3e4 + group_offset
                        + record_in_group))->unknown_00 = 0;
            ((Record *)((u8 *)data_0217aa14 + 0x3e4 + group_offset
                        + record_in_group))->state = 15;
            ((Record *)((u8 *)data_0217aa14 + 0x3e4 + group_offset
                        + record_in_group))->unknown_0a = 0;
            ((Record *)((u8 *)data_0217aa14 + 0x3e4 + group_offset
                        + record_in_group))->unknown_0b = 0;
            Mem_CpuFill8(((Record *)((u8 *)data_0217aa14 + 0x3e4
                                     + group_offset + record_in_group))->buffer,
                         0, 0x14);
            data_0217aa14->record_flags[group][record] = 0;
            record++;
            record_in_group += 12;
        } while (record < 4);

        ((Record *)((u8 *)data_0217aa14 + 0x324 + record_offset))->unknown_08 = 0;
        ((Record *)((u8 *)data_0217aa14 + 0x324 + record_offset))->unknown_00 = 0;
        ((Record *)((u8 *)data_0217aa14 + 0x324 + record_offset))->state = 15;
        ((Record *)((u8 *)data_0217aa14 + 0x324 + record_offset))->unknown_0a = 0;
        ((Record *)((u8 *)data_0217aa14 + 0x324 + record_offset))->unknown_0b = 0;
        Mem_CpuFill8(((Record *)((u8 *)data_0217aa14 + 0x324
                                 + record_offset))->buffer, 0, 0x14);

        record_offset += 12;
        group_offset += 48;
        group++;
    } while (group < 16);

    data_0217aa14->record_count = 0x30;
}
