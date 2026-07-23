// PURPOSE: Sets up each racer's emblem texture and palette.

typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

typedef struct RaceConfig {
    u8 pad_000[0x3d0];
    u8 racerCount;
} RaceConfig;

typedef struct EmblemArray {
    u8 pad_000[0x144];
    void *tex[8];
    void *pal[8];
} EmblemArray;

extern RaceConfig *gRaceConfig;
extern EmblemArray *data_0217aed0;
extern void DriverContext_SetupEmblem_from_thumb(u16 racer, void *tex, void *pal);

void SetupDriverEmblems_from_thumb(void)
{
    u16 racer;

    racer = 0;
    if ((u32)racer < gRaceConfig->racerCount) {
        do {
            DriverContext_SetupEmblem_from_thumb(
                racer, data_0217aed0->tex[racer], data_0217aed0->pal[racer]);
            racer++;
        } while ((u32)racer < gRaceConfig->racerCount);
    }
}
