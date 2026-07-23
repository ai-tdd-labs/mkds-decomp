/* PURPOSE: Copies a saved Grand Prix cup record into working memory.
 * The first argument holds a compact cup result and player nickname.
 * The second argument receives the expanded fields used by the game.
 * If the saved entry is invalid, only the destination validity flag is cleared.
 */

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

void StructNKGPCupEntry_CopyTo_from_thumb(
    const SaveDataGrandPrixCupRecordEntry *savedEntry,
    NKGPCupEntry *cupEntry)
{
    if (savedEntry->isValid) {
        Mem_CpuCopy8(savedEntry->nickname, cupEntry->nickname, 0x14);
        cupEntry->characterId = savedEntry->characterId;
        cupEntry->kartId = savedEntry->kartId;
        cupEntry->minutes = savedEntry->minutes;
        cupEntry->seconds = savedEntry->seconds;
        cupEntry->milliseconds = savedEntry->milliseconds;
        cupEntry->rank = savedEntry->rank;
        cupEntry->points = savedEntry->points;
        cupEntry->cupResult = savedEntry->cupResult;
        cupEntry->isValid = 1;
        return;
    }

    cupEntry->isValid = 0;
}
