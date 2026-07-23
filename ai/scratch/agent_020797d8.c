// PURPOSE: Prepares the shared character and kart data for a race.
/*
 * Uses the supplied heap and racer count for the shared-state allocations.
 * It loads model, palette, animation, and physical-parameter resources, then
 * initializes each racer entry. Some resource field meanings are inferred.
*/

typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

typedef struct RacerEntry {
    int characterId;               /* 0x00 */
    int kartId;                    /* 0x04 */
    u8 unknown_08[0x18];
    void *kartOffsetData;          /* 0x20 */
    u8 unknown_24[0x8c];
    u32 colorVariant;              /* 0xb0 */
} RacerEntry;

typedef struct RacerManager {
    RacerEntry *racers;            /* 0x00 */
    void *kartCrossMaterial;       /* 0x04 */
    u16 racerCount;                /* 0x08 */
    u16 unknown_0a;
    u32 unknown_0c;
    void *kartAPaletteData;        /* 0x10 */
    void *heyhoPaletteData;        /* 0x14 */
    u8 unknown_18[0x10];
    void *faceAnimationData;       /* 0x28 */
} RacerManager;

typedef struct RacerSlot {
    u8 raw[0x30];
} RacerSlot;

typedef struct RacerConfigRecord {
    int kartCrossMaterialIndex;    /* 0x00, probably one-based */
    u8 unknown_04[0x64];
    int characterId;               /* 0x68 */
    int kartId;                    /* 0x6c */
    u8 unknown_70[0x25];
    u8 colorVariant;               /* 0x95 */
} RacerConfigRecord;

typedef struct PaletteData {
    u32 format;
    u32 extended;
    u32 size;
    void *rawData;
} PaletteData;

extern RacerManager *data_0217ad00;
extern void *data_0217ad08;
extern RacerSlot *gRaceConfig;

extern char data_02165878[];
extern char data_0216588c[];
extern char data_0216589c[];

extern void *FindFileBuffer_KME_KM1_KM2_KSB_from_thumb(char *path);
extern void *FindFileBufferGeneric_KME_KM1_KM2_KSB_from_thumb(char *path);
extern void SetCurrentlyInKartModelMenu(int enabled);
extern void *Mem_AllocateHeap(void *heap, u32 size);
extern void *GetKartAPaletteData_from_thumb(void);
extern char *FormatCharacterFaceAnimationNsbtpPath(void);
extern void CreateLoadPhysicalParams(void *heap, int count);
extern void MaybeLoadKartAIData_from_thumb(void);
extern void LoadAD00KillerItemModel_from_thumb(int heapId);
extern void StructAD00Sub_Initialize_from_thumb(RacerEntry *racer);
extern void StructAD00Sub_SomeFn_from_thumb(RacerEntry *racer);
extern void StructAD00Sub_SetKartIndex_from_thumb(RacerEntry *racer, int kartId);
extern void Mem_CpuCopy8(const void *source, void *destination, u32 size);
extern void CopyKartCharPhysicalParam(u16 racerIndex, u16 kartId, u16 characterId);
extern void func_02079678(void *heap, int alternateMode);
extern void Dispose_KM1_Mount_KM2_from_thumb(void);
extern int DetermineIsP_from_thumb(int racerIndex);
extern void CharacterKart_PatchRobPalette_from_thumb(RacerEntry *racer, int isPlayer);
extern void Gfx_ReadPalette(PaletteData **output, void *buffer);

void InitializeGlobalAD00_from_thumb(void *heap, int racerCount)
{
    void *kartOffsetData;
    PaletteData *heyhoPalette;

    kartOffsetData = FindFileBuffer_KME_KM1_KM2_KSB_from_thumb(data_02165878);
    SetCurrentlyInKartModelMenu(0);

    data_0217ad08 = 0;
    data_0217ad00 = (RacerManager *)Mem_AllocateHeap(heap, 0x144);
    data_0217ad00->racers =
        (RacerEntry *)Mem_AllocateHeap(heap, racerCount * 0xb4);

    data_0217ad00->kartCrossMaterial =
        FindFileBufferGeneric_KME_KM1_KM2_KSB_from_thumb(data_0216588c);
    /* The file table is indexed from one, with eight bytes per record. */
    data_0217ad00->kartCrossMaterial =
        (u8 *)data_0217ad00->kartCrossMaterial +
        ((RacerConfigRecord *)gRaceConfig)->kartCrossMaterialIndex * 8 - 8;

    data_0217ad00->kartAPaletteData = GetKartAPaletteData_from_thumb();
    data_0217ad00->heyhoPaletteData = 0;
    data_0217ad00->faceAnimationData =
        FindFileBufferGeneric_KME_KM1_KM2_KSB_from_thumb(
            FormatCharacterFaceAnimationNsbtpPath());
    data_0217ad00->racerCount = racerCount;
    data_0217ad00->unknown_0c = 0;

    CreateLoadPhysicalParams(heap, racerCount);
    MaybeLoadKartAIData_from_thumb();
    LoadAD00KillerItemModel_from_thumb((int)heap);

    {
        register u16 racerIndex = 0;
        RacerManager * volatile *globalAddress =
            (RacerManager * volatile *)&data_0217ad00;

        if (racerIndex < (*globalAddress)->racerCount) {
            register RacerEntry *racers = data_0217ad00->racers;
            do {
                RacerEntry *racer = &racers[racerIndex];

                StructAD00Sub_Initialize_from_thumb(racer);
                racer->colorVariant =
                    ((RacerConfigRecord *)&gRaceConfig[racerIndex])->colorVariant;
                StructAD00Sub_SomeFn_from_thumb(racer);

                racers[racerIndex].characterId =
                    ((RacerConfigRecord *)&gRaceConfig[racerIndex])->characterId;
                racer->kartId =
                    ((RacerConfigRecord *)&gRaceConfig[racerIndex])->kartId;
                StructAD00Sub_SetKartIndex_from_thumb(racer, racer->kartId);

                racer->kartOffsetData = Mem_AllocateHeap(heap, 0xe0);
                Mem_CpuCopy8(
                    (u8 *)kartOffsetData + racer->kartId * 0xe0,
                    racer->kartOffsetData,
                    0xe0);

                CopyKartCharPhysicalParam(
                    racerIndex,
                    racer->kartId,
                    racers[racerIndex].characterId);

                racerIndex++;
            } while (racerIndex < data_0217ad00->racerCount);
        }
    }

    func_02079678(heap, 1);
    Dispose_KM1_Mount_KM2_from_thumb();
    func_02079678(heap, 0);

    {
        void *racer;
        int isPlayer;
        register u16 racerIndex = 0;

        if (racerIndex < data_0217ad00->racerCount) {
            do {
                racer = &data_0217ad00->racers[racerIndex];
                isPlayer = DetermineIsP_from_thumb(racerIndex);

                CharacterKart_PatchRobPalette_from_thumb((RacerEntry *)racer, isPlayer);
                racerIndex++;
            } while (racerIndex < data_0217ad00->racerCount);
        }
    }

    Gfx_ReadPalette(
        &heyhoPalette,
        FindFileBufferGeneric_KME_KM1_KM2_KSB_from_thumb(data_0216589c));
    data_0217ad00->heyhoPaletteData = heyhoPalette->rawData;
}
