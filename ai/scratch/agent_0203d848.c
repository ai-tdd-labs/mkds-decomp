/* PURPOSE: Sets up the global rank and records manager when a race starts.
 *
 * Argument: heap to allocate from (kept across the calls).
 * Allocates the main manager plus a table with one pointer per course entry,
 * loads the rank-point and rank-time files, and probably initializes extra
 * mission-mode area data when the race mode is 4.
 */

typedef struct MVSource {
    char pad_00[0x98];
    unsigned short entryCount; /* 0x98: table gets count + 1 slots */
} MVSource;

typedef struct GlobalMV {
    char pad_000[0x4c8];
    void *ranktimeBuf;   /* 0x4c8: "/ranktimeGP.rtt" file buffer */
    char pad_4cc[0x8];
    void *entryTable;    /* 0x4d4: entryCount + 1 pointer slots */
    char pad_4d8[0x4];
    void *rankpointBuf;  /* 0x4dc: "/rankpoint.rpt" file buffer */
    char pad_4e0[0x44];
} GlobalMV;

typedef struct RaceConfigHeader {
    char pad_00[0x8];
    int mode; /* 0x8: mode 4 gets the extra mission setup */
} RaceConfigHeader;

extern MVSource *data_02175620;
extern GlobalMV *data_0217561c;
extern RaceConfigHeader *gRaceConfig;
extern char data_021647b8[];
extern char data_021647c8[];

extern void *Mem_AllocateHeap(void *heap, unsigned int size);
extern void *FindFileBuffer_MAR_EFT_from_thumb(const char *path);
extern void LoadCurrentCourseRanktime(void *buffer);
extern void SomethingMissionModeType5Areas(void *heap);
extern void CreateGlobalMV(void);

void InitializeGlobalMV(void *heap)
{
    /* Global-based stores reproduce the manager reloads between operations. */
    data_0217561c = (GlobalMV *)Mem_AllocateHeap(heap, sizeof(GlobalMV));
    data_0217561c->entryTable =
        Mem_AllocateHeap(heap, (data_02175620->entryCount + 1) * 4);
    data_0217561c->rankpointBuf =
        FindFileBuffer_MAR_EFT_from_thumb(data_021647b8);
    data_0217561c->ranktimeBuf =
        FindFileBuffer_MAR_EFT_from_thumb(data_021647c8);
    LoadCurrentCourseRanktime(data_0217561c->ranktimeBuf);
    if (gRaceConfig->mode == 4) {
        SomethingMissionModeType5Areas(heap);
    }
    CreateGlobalMV();
}
