// PURPOSE: Loads the character and kart assets needed by every racer.
// The heap supplies storage for the loaded models and scaled tire positions.
// alternateMode selects the character and kart ID ranges to load.
// In alternate mode, player racers also receive tire and shadow models.

typedef unsigned short u16;
typedef unsigned int u32;
typedef int s32;

typedef struct VecFx32 {
    s32 x;
    s32 y;
    s32 z;
} VecFx32;

typedef struct KartModelData {
    char pad00[0x10];
    s32 scale;
    VecFx32 tirePositions[4];
} KartModelData;

typedef struct RacerEntry {
    s32 characterId;
    s32 kartId;
    char pad08[0x18];
    KartModelData *modelData;
    char pad24[0x30];
    VecFx32 *scaledTirePositions;
    char pad58[0x5c];
} RacerEntry;

typedef struct RacerManager {
    RacerEntry *entries;
    s32 field04;
    u16 entryCount;
} RacerManager;

extern RacerManager *data_0217ad00;
extern int DetermineIsP_from_thumb(int racerIndex);
extern void StructAD00Sub_LoadCharacterEmblem_from_thumb(
    RacerEntry *entry, void *heap, int isPlayer);
extern void StructAD00Sub_LoadKartModel_from_thumb(
    int *entry, int heap, int isPlayer);
extern void *Mem_AllocateHeap(void *heap, unsigned int size);
extern s32 FX_Div(s32 numerator, s32 denominator);
extern void CharacterKart_LoadKartTireModel_from_thumb(
    int *entry, void *heap);
extern void StructAD00Sub_LoadKartShadowModel_from_thumb(
    int *entry, void *heap);

void func_02079678(void *heap, volatile int alternateMode)
{
    int skipKartModel;
    volatile int loadPrimaryKart;
    u16 racerIndex;
    int characterLow;
    int characterHigh;
    int kartLow;
    int kartHigh;
    RacerEntry *entry;
    int isPlayer;
    int isPrimaryKart;

    if (alternateMode != 0) {
        characterLow = 0;
        characterHigh = 7;
        kartLow = characterLow;
        kartHigh = 0x15;
    } else {
        characterLow = 7;
        characterHigh = 0xd;
        kartLow = 0x15;
        kartHigh = 0x25;
    }

    racerIndex = 0;
    if (racerIndex < data_0217ad00->entryCount) {
        if (alternateMode == 0) {
            loadPrimaryKart = 1;
        } else {
            loadPrimaryKart = racerIndex;
        }

        do {
            entry = &data_0217ad00->entries[racerIndex];
            isPlayer = DetermineIsP_from_thumb(racerIndex);
            isPrimaryKart = ((u16)entry->kartId % 3) == 0;

            if (isPrimaryKart != 0 && loadPrimaryKart != 0) {
                skipKartModel = 1;
            } else {
                skipKartModel = 0;
            }

            if (entry->characterId >= characterLow &&
                entry->characterId < characterHigh) {
                StructAD00Sub_LoadCharacterEmblem_from_thumb(
                    entry, heap, isPlayer);
            }

            if (skipKartModel != 0) {
                goto after_kart_model;
            }
            if (isPrimaryKart == 0) {
                goto check_kart_range;
            }
            if (alternateMode != 0) {
                goto load_kart_model;
            }

        check_kart_range:
            if (entry->kartId < kartLow) {
                goto after_kart_model;
            }
            if (entry->kartId >= kartHigh) {
                goto after_kart_model;
            }

        load_kart_model:
            StructAD00Sub_LoadKartModel_from_thumb(
                (int *)entry, (int)heap, isPlayer);

        after_kart_model:
            if (alternateMode != 0) {
                if (isPlayer != 0) {
                    u16 tireIndex = 0;
                    VecFx32 *sourcePositions;

                    entry->scaledTirePositions =
                        (VecFx32 *)Mem_AllocateHeap(heap, 0x30);

                    do {
                        VecFx32 *destinationPositions =
                            entry->scaledTirePositions;
                        VecFx32 *destination =
                            &destinationPositions[tireIndex];

                        sourcePositions = entry->modelData->tirePositions;
                        {
                            VecFx32 *source = &sourcePositions[tireIndex];

                            destination->x = source->x >> 4;
                            destination->y = source->y >> 4;
                            destination->z = source->z >> 4;
                        }
                        tireIndex++;
                    } while (tireIndex < 4);

                    entry->scaledTirePositions[1].x = FX_Div(
                        -(entry->scaledTirePositions[0].x) << 1,
                        entry->modelData->scale);
                    entry->scaledTirePositions[3].x =
                        -(entry->scaledTirePositions[2].x) << 1;
                    CharacterKart_LoadKartTireModel_from_thumb(
                        (int *)entry, heap);
                }
                StructAD00Sub_LoadKartShadowModel_from_thumb(
                    (int *)entry, heap);
            }

            racerIndex++;
        } while (racerIndex < data_0217ad00->entryCount);
    }
}
