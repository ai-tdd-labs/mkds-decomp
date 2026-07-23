// PURPOSE: Copies a saved time-trial record into a usable record.
// The source is a compact save-data record and the destination is its expanded form.
// Invalid source records clear the complete destination record.
// Field meanings are inferred from the saved-record layout.

typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

typedef struct SaveTimeTrialRecord {
    u32 isValid : 1;
    u32 characterId : 7;
    u32 minutes : 7;
    u32 seconds : 7;
    u32 milliseconds : 10;
    u8 kartId;
    u8 padding_05[3];
    u16 nickname[10];
} SaveTimeTrialRecord;

typedef struct TimeTrialRecord {
    u16 milliseconds;
    u8 minutes;
    u8 seconds;
    u16 nickname[10];
    u8 isValid;
    u8 characterId;
    u8 kartId;
    u8 padding_1B[5];
} TimeTrialRecord;

extern void Mem_CpuCopy8(const void *source, void *destination, u32 size);
extern void Mem_CpuFill8(void *destination, u32 value, u32 size);

void TimeTrialRecord_CopyFromImpl_from_thumb(
    const SaveTimeTrialRecord *savedRecord, TimeTrialRecord *record)
{
    if (savedRecord->isValid) {
        Mem_CpuCopy8(savedRecord->nickname, record->nickname, 0x14);
        record->characterId = savedRecord->characterId;
        record->kartId = savedRecord->kartId;
        record->minutes = savedRecord->minutes;
        record->seconds = savedRecord->seconds;
        record->milliseconds = savedRecord->milliseconds;
        record->isValid = 1;
        return;
    }

    Mem_CpuFill8(record, 0, 0x20);
}
