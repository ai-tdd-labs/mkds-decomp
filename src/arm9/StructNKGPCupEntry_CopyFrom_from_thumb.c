// PURPOSE: Copies a Grand Prix cup entry into saved data.
// The first argument receives the compact save record and the second provides
// the working cup entry.  An invalid working entry leaves the saved record
// unchanged.

typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

typedef struct SaveDataGrandPrixCupRecordEntry {
    u32 isValid : 1;
    u32 characterId : 7;
    u32 kartId : 8;
    u32 points : 8;
    u32 rank : 8;
    u32 cupResult : 8;
    u32 minutes : 7;
    u32 seconds : 7;
    u32 milliseconds : 10;
    u16 nickname[10];
} SaveDataGrandPrixCupRecordEntry;

typedef struct NKGPCupEntry {
    u16 milliseconds;
    u8 minutes;
    u8 seconds;
    u16 nickname[10];
    u8 isValid;
    u8 characterId;
    u8 kartId;
    u8 unknown1B;
    u8 cupResult;
    u8 points;
    u8 rank;
    u8 unknown1F;
} NKGPCupEntry;

extern void Mem_CpuCopy8(const void *source, void *destination, u32 size);

void StructNKGPCupEntry_CopyFrom_from_thumb(
    SaveDataGrandPrixCupRecordEntry *savedEntry,
    const NKGPCupEntry *cupEntry)
{
    if (cupEntry->isValid) {
        Mem_CpuCopy8(cupEntry->nickname, savedEntry->nickname, 0x14);
        savedEntry->isValid = 1;
        savedEntry->characterId = cupEntry->characterId;
        savedEntry->kartId = cupEntry->kartId;
        savedEntry->minutes = cupEntry->minutes;
        savedEntry->seconds = cupEntry->seconds;
        savedEntry->milliseconds = cupEntry->milliseconds;
        savedEntry->rank = cupEntry->rank;
        savedEntry->points = cupEntry->points;
        savedEntry->cupResult = cupEntry->cupResult;
    }
}
