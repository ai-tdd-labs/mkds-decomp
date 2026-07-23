// PURPOSE: Copies a working cup entry into the saved cup records.
// The first two arguments select the entry and cup record bank.
// The last argument is probably the working-memory entry to save.

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

typedef struct SaveDataGrandPrixCupRecords {
    u8 unknown_00[4];
    SaveDataGrandPrixCupRecordEntry entries[4][8];
} SaveDataGrandPrixCupRecords;

typedef struct SaveDataContext {
    u8 unknown_00[8];
    SaveDataGrandPrixCupRecords *cupRecords;
} SaveDataContext;

extern SaveDataContext *data_0217aa08;

extern void StructNKGPCupEntry_CopyTo_from_thumb(
    const SaveDataGrandPrixCupRecordEntry *savedEntry,
    NKGPCupEntry *cupEntry);

int CopyCupEntryTo_from_thumb(int entryIndex, int cupIndex,
                               NKGPCupEntry *cupEntry)
{
    StructNKGPCupEntry_CopyTo_from_thumb(
        &data_0217aa08->cupRecords->entries[cupIndex][entryIndex], cupEntry);
    return 1;
}
