// PURPOSE: Copies a usable time-trial record into saved-record format.
// The first argument receives the compact save-data form.
// The second argument supplies the expanded record used by the game.
// Invalid records probably clear the complete saved destination.

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

void TimeTrialRecordCopyTo_from_thumb(
    SaveTimeTrialRecord *savedRecord, const TimeTrialRecord *record)
{
    if (record->isValid) {
        Mem_CpuCopy8(record->nickname, savedRecord->nickname, 0x14);
        savedRecord->isValid = 1;
        savedRecord->characterId = record->characterId;
        savedRecord->kartId = record->kartId;
        savedRecord->minutes = record->minutes;
        savedRecord->seconds = record->seconds;
        savedRecord->milliseconds = record->milliseconds;
        return;
    }

    Mem_CpuFill8(savedRecord, 0, 0x1c);
}
