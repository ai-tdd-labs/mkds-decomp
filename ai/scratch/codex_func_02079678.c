/* Loads the character and kart assets for every configured racer.
 * The second argument selects one of two character/kart ID ranges; in the
 * alternate mode it also builds scaled tire attachment vectors.
 * Some field meanings are inferred from the neighboring loader calls. */

typedef unsigned short u16;
typedef unsigned int u32;
typedef int s32;
typedef struct VecFx32 { s32 x, y, z; } VecFx32;
typedef struct KartModelData {
    char pad00[0x10];
    s32 scale;
    VecFx32 tirePositions[4];
} KartModelData;
typedef struct CharacterKart {
    s32 characterId;
    s32 kartId;
    char pad08[0x18];
    KartModelData *modelData;
    char pad24[0x30];
    VecFx32 *scaledTirePositions;
    char pad58[0x5c];
} CharacterKart;
typedef struct KartLoadContext {
    CharacterKart *entries;
    s32 field04;
    u16 entryCount;
} KartLoadContext;

extern KartLoadContext *data_0217ad00;
extern int DetermineIsP_from_thumb(u16 index);
extern void StructAD00Sub_LoadCharacterEmblem_from_thumb(CharacterKart *, void *, int);
extern void StructAD00Sub_LoadKartModel_from_thumb(CharacterKart *, void *, int);
extern void *Mem_AllocateHeap(void *, u32);
extern s32 FX_Div(s32, s32);
extern void CharacterKart_LoadKartTireModel_from_thumb(CharacterKart *, void *);
extern void StructAD00Sub_LoadKartShadowModel_from_thumb(CharacterKart *, void *);

void func_02079678(void *heap, int alternateMode) {
    int skipKart;
    int loadPrimarySet;
    u16 index;
    int characterLow;
    int characterHigh;
    int kartLow;
    int kartHigh;
    CharacterKart *entry;
    int isP;
    int isFirstOfThree;

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

    index = 0;
    if (index < data_0217ad00->entryCount) {
        loadPrimarySet = alternateMode == 0 ? 1 : 0;
        do {
            entry = &data_0217ad00->entries[index];
            isP = DetermineIsP_from_thumb(index);
            isFirstOfThree = ((u16)entry->kartId % 3) == 0;
            if (isFirstOfThree && loadPrimarySet)
                skipKart = 1;
            else
                skipKart = 0;

            if (entry->characterId >= characterLow &&
                entry->characterId < characterHigh)
                StructAD00Sub_LoadCharacterEmblem_from_thumb(entry, heap, isP);

            if (!skipKart) {
                if ((!isFirstOfThree || alternateMode == 0) &&
                    (entry->kartId < kartLow || entry->kartId >= kartHigh))
                    goto skip_kart_model;
                StructAD00Sub_LoadKartModel_from_thumb(entry, heap, isP);
            }

        skip_kart_model:
            if (alternateMode != 0) {
                if (isP != 0) {
                    u16 tire = 0;
                    VecFx32 *source;
                    entry->scaledTirePositions =
                        (VecFx32 *)Mem_AllocateHeap(heap, sizeof(VecFx32) * 4);
                    do {
                        VecFx32 *destination = entry->scaledTirePositions;
                        VecFx32 *destinationAt = &destination[tire];
                        source = entry->modelData->tirePositions;
                        {
                            VecFx32 *sourceAt = &source[tire];
                            destinationAt->x = sourceAt->x >> 4;
                            destinationAt->y = sourceAt->y >> 4;
                            destinationAt->z = sourceAt->z >> 4;
                        }
                        tire++;
                    } while (tire < 4);
                    entry->scaledTirePositions[1].x =
                        FX_Div(-(entry->scaledTirePositions[0].x) << 1,
                               entry->modelData->scale);
                    entry->scaledTirePositions[3].x =
                        -(entry->scaledTirePositions[2].x) << 1;
                    CharacterKart_LoadKartTireModel_from_thumb(entry, heap);
                }
                StructAD00Sub_LoadKartShadowModel_from_thumb(entry, heap);
            }
            index++;
        } while (index < data_0217ad00->entryCount);
    }
}
