// PURPOSE: Returns the color used for a versus racer indicator.
//
// The racer index selects a palette entry based on the current race mode.
// A special character probably uses its own palette color.

typedef unsigned char u8;
typedef unsigned short u16;

typedef struct RaceConfig {
    u8 pad_00[8];
    int raceMode;
    u8 pad_0c[0x4c];
    signed char useKartColor;
} RaceConfig;

extern RaceConfig *gRaceConfig;
extern u16 data_02155a2c[];
extern u16 data_02155a28[];
extern u16 data_02155a64[];

extern int *GetCharacterKart(int racer);
extern void *GetHeyhoColorPaletteDataForRacer_from_thumb(int racer);

u16 GetVsRacerIndicatorColor_from_thumb(int racer)
{
    if (gRaceConfig->raceMode == 5) {
        return data_02155a2c[((u8 *)gRaceConfig)[racer * 0x30 + 0x95]];
    }

    if (gRaceConfig->useKartColor != 0) {
        return data_02155a28[*(int *)((u8 *)gRaceConfig + racer * 0x30 + 0x74)];
    }

    if (*GetCharacterKart(racer) == 12) {
        return *(u16 *)((u8 *)GetHeyhoColorPaletteDataForRacer_from_thumb(racer) + 4);
    }

    return data_02155a64[racer];
}
