// PURPOSE: Copies a valid time trial record to the output buffer.
// The first two arguments probably identify the requested record.
// The helper fills a temporary record and returns whether it was found.
// On success, this copies the record payload to the caller and returns one.

typedef unsigned char u8;

extern int TimeTrialRecord_CopyFrom_from_thumb(int arg0, int arg1, void *record);
extern void Mem_CpuCopy8(const void *source, void *destination, unsigned int size);

int func_020600d0(int arg0, int arg1, void *output)
{
    u8 record[0x20];

    if (TimeTrialRecord_CopyFrom_from_thumb(arg0, arg1, record) == 0 || record[0x18] == 0)
        return 0;

    Mem_CpuCopy8(record + 4, output, 0x14);
    return 1;
}
