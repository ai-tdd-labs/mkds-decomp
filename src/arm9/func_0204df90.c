// PURPOSE: Starts a shared data request and advances its record handle.
// The global context probably owns a request state and a shared-data record.
// It initializes that record with fixed limits, then moves the record handle forward.

typedef unsigned short u16;

typedef struct SharedDataRecord {
    unsigned char pad_00[0x48];
    u16 handle;
} SharedDataRecord;

typedef struct UnkStruct_0217aa00 {
    unsigned char pad_00[0x0c];
    int request;
    int busy;
    unsigned char pad_14[0x10];
    SharedDataRecord *record;
} UnkStruct_0217aa00;

extern UnkStruct_0217aa00 *data_0217aa00;
extern void func_02007ec4(SharedDataRecord *record, u16 primaryLimit,
                           u16 secondaryLimit, int enableOption4,
                           int enableOption8);

void func_0204df90(void)
{
    data_0217aa00->request = 0x1a;
    data_0217aa00->busy = 1;
    func_02007ec4(data_0217aa00->record, 0x1bc, 0x36, 0, 0);
    data_0217aa00->record->handle =
        (u16)((data_0217aa00->record->handle + 7) & 0x7fff);
    data_0217aa00->busy = 0;
}
