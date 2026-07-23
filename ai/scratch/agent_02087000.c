// PURPOSE: Loads each racer's emblem texture and palette pointers.

typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

#pragma optimize_for_size on

typedef struct {
    u8 raw[0x30];
} RacerSlotB;

typedef struct {
    char pad_00[0x58];
    signed char f58;
    char pad_59[0x68 - 0x59];
    u32 f68;
    char pad_6c[0x74 - 0x6c];
    u32 f74;
    char pad_78[0x8c - 0x78];
    void *f8c;
    char pad_90[0x94 - 0x90];
    u8 f94;
    char pad_95[0x3d0 - 0x95];
    u8 f3d0;
} RacerRecord;

typedef struct {
    u32 fmt;
    u32 bExtendedPlt;
    u32 szByte;
    void *pRawData;
} PaletteData;

typedef struct {
    char pad_00[0x144];
    u32 tex[8];
    u32 pal[8];
} EmblemArray;

extern RacerSlotB *gRaceConfig;
extern EmblemArray *data_0217aed0;
extern char data_02165a7c[];

extern char *FormatTeamEmblemNsbtx(int team);
extern char *FormatEmblemNsbtx(int character);
extern u8 *FindFileBufferGeneric_KME_KM1_KM2_KSB_from_thumb(char *name);
extern void *Nsbtx_GetTEX0Block(void *nsbtx);
extern void Gfx_ReadPalette(void *out, void *buf);

void LoadEmblemDataInAED0_from_thumb(void)
{
    int slot;
    u16 i;
    volatile int zero;

    i = 0;

    if ((u32)i < ((RacerRecord *)gRaceConfig)->f3d0) {
        zero = 0;
        do {
            RacerRecord *racer;
            u8 *fileBuf;
            u8 *tex0;

            slot = i;
            data_0217aed0->tex[i] = slot;
            data_0217aed0->pal[i] = slot;

            racer = (RacerRecord *)&gRaceConfig[i];

            if (racer->f94 != 0) {
                if (((RacerRecord *)gRaceConfig)->f58 == 0) {
                    goto custom_emblem;
                }
            }

            if (((RacerRecord *)gRaceConfig)->f58 != 0) {
                fileBuf = FindFileBufferGeneric_KME_KM1_KM2_KSB_from_thumb(
                    FormatTeamEmblemNsbtx(racer->f74 == 1 ? 1 : zero));
            } else {
                fileBuf = FindFileBufferGeneric_KME_KM1_KM2_KSB_from_thumb(
                    FormatEmblemNsbtx((u16)racer->f68));
            }

            tex0 = (u8 *)Nsbtx_GetTEX0Block(fileBuf);
            data_0217aed0->tex[i] = (u32)(tex0 + *(int *)(tex0 + 0x14));
            data_0217aed0->pal[i] = (u32)(tex0 + *(int *)(tex0 + 0x38));
            goto emblem_done;

custom_emblem:
            {
                PaletteData *palette;
                void *customTex = racer->f8c;

                fileBuf = FindFileBufferGeneric_KME_KM1_KM2_KSB_from_thumb(data_02165a7c);
                Gfx_ReadPalette(&palette, fileBuf);

                data_0217aed0->tex[i] = (u32)customTex;
                data_0217aed0->pal[i] = (u32)palette->pRawData;
            }

emblem_done:
            i++;
        } while ((u32)i < ((RacerRecord *)gRaceConfig)->f3d0);
    }
}
