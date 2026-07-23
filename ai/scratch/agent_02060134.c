// PURPOSE: Copies a valid time trial record header to the output.
// The first two arguments probably select a time trial record.
// The helper writes a temporary 32-byte record and returns whether it was found.
// The output receives its first four bytes only when the record is valid.

typedef unsigned char u8;
typedef unsigned short u16;

extern int TimeTrialRecord_CopyFrom_from_thumb(int recordType, int recordId, u8 *record);

int func_02060134(int recordType, int recordId, void *output)
{
    u8 record[0x20];

    if (TimeTrialRecord_CopyFrom_from_thumb(recordType, recordId, record) && record[0x18]) {
        ((u8 *)output)[2] = record[2];
        ((u8 *)output)[3] = record[3];
        *(u16 *)output = *(u16 *)record;
        return 1;
    }
    return 0;
}
