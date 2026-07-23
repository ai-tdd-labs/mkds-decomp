// PURPOSE: Copies a selected ghost record into an output buffer.
// The selector chooses a normal course record or one of two extra record stores.
// The destination is cleared first; selectors three and four probably have no record.

typedef unsigned char u8;
typedef signed short s16;
typedef unsigned int u32;

typedef struct RecordEntry {
    u8 bytes[0x30];
} RecordEntry;

typedef struct Effects {
    u8 pad_00[4];
    void *records;
    u8 pad_08[8];
    s16 recordIndex;
} Effects;

typedef struct GlobalPK {
    void *structYE;
    Effects *effects;
    void *ghostHolder;
    int internalCourseId;
    s16 recordIndex;
    u8 reserved_12[2];
} GlobalPK;

extern GlobalPK *data_0217d374;

extern int GetCourseIdFromInternalId(int internalId);
extern int func_020616c0(RecordEntry *entry, void *output);
extern void Mem_CpuFill8(void *destination, u32 value, u32 size);
extern void CopyMemory16(const void *source, void *destination, u32 size);

void func_0211e2f8(int selector, void *output)
{
    u8 record[0x14];
    RecordEntry *records;

    switch (selector) {
    case 0:
        records = (RecordEntry *)data_0217d374->structYE;
        func_020616c0((RecordEntry *)((u8 *)records +
                                      GetCourseIdFromInternalId(data_0217d374->internalCourseId) * 0x30),
                      record);
        break;
    case 1:
        func_020616c0((RecordEntry *)((u8 *)data_0217d374->effects +
                                       (u8)data_0217d374->recordIndex * 0x230),
                       record);
        break;
    case 2:
        records = (RecordEntry *)data_0217d374->ghostHolder;
        func_020616c0((RecordEntry *)((u8 *)records +
                                      GetCourseIdFromInternalId(data_0217d374->internalCourseId) * 0x230),
                      record);
        break;
    case 3:
    case 4:
        break;
    }

    Mem_CpuFill8(output, 0, 0x20);
    CopyMemory16(record, output, 0x14);
}
