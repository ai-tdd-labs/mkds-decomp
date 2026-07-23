// PURPOSE: Saves a cup entry into the Grand Prix record table.
// The first two arguments select the entry and cup record.
// The third argument is probably the current in-memory cup result to save.

typedef unsigned char u8;

typedef struct NKGPCupEntry {
    u8 raw[0x20];
} NKGPCupEntry;

typedef struct SaveDataGrandPrixCupRecordEntry {
    u8 raw[0x1c];
} SaveDataGrandPrixCupRecordEntry;

typedef struct GrandPrixCupRecords {
    int unknown_00;
    SaveDataGrandPrixCupRecordEntry entries[][8];
} GrandPrixCupRecords;

typedef struct SaveDataContext {
    u8 unknown_00[8];
    GrandPrixCupRecords *grandPrixCupRecords;
} SaveDataContext;

extern SaveDataContext *data_0217aa08;
extern void StructNKGPCupEntry_CopyFrom_from_thumb(
    SaveDataGrandPrixCupRecordEntry *destination, const NKGPCupEntry *source);

void CopyCupEntryFrom_from_thumb(int entryIndex, int cupIndex,
                                 const NKGPCupEntry *source)
{
    StructNKGPCupEntry_CopyFrom_from_thumb(
        &data_0217aa08->grandPrixCupRecords->entries[cupIndex][entryIndex],
        source);
}
