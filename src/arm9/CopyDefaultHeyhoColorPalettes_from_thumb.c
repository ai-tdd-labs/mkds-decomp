/* PURPOSE: Gives every Shy Guy racer its default color palette at race start.
 *
 * No arguments. If the Heyho (Shy Guy) palette manager is loaded, it first
 * copies some shared palette rows, then walks all racers in the race config
 * (byte count at +0x3d0); every racer whose character id is 0xc (Shy Guy)
 * gets the default palette for its racer index applied to its entry.
 * Field meanings are guesses; the math is exact.
 */

typedef unsigned char u8;
typedef unsigned short u16;

/* Manager pointed to by data_0217ad00 (probably the Heyho palette manager). */
typedef struct HeyhoPaletteManager_0207800c {
    u8 *racers;   /* 0x00: array of 0xb4-byte racer entries; first int = character id */
    int unk04;
    int unk08;
    int unk0c;
    int unk10;
    void *unk14;  /* 0x14: guard pointer, 0 = manager not ready */
} HeyhoPaletteManager_0207800c;

/* Race config, only the racer-count byte at +0x3d0 is used here. */
typedef struct RaceConfig_0207800c {
    u8 unk000[0x3d0];
    u8 racerCount; /* 0x3d0: number of racers */
} RaceConfig_0207800c;

extern HeyhoPaletteManager_0207800c *data_0217ad00;
extern RaceConfig_0207800c *gRaceConfig;

extern void CopySomeHeyhoPaletteRows_from_thumb(void);
extern void *GetHeyhoColorPaletteDataForRacer_from_thumb(int racer);
extern void func_02077f9c(int racer, u8 *entry, void *palette);

void CopyDefaultHeyhoColorPalettes_from_thumb(void)
{
    u16 i;   /* u16 counter: ROM wraps it with lsls/lsrs #16 */
    int off; /* i * 0xb4 byte offset into the racer array */
    void *pal;

    if (data_0217ad00->unk14 == 0) {
        return;
    }

    CopySomeHeyhoPaletteRows_from_thumb();

    /* (u32) cast: ROM compares unsigned (bls guard / blo back-edge) */
    for (i = 0; (unsigned int)i < gRaceConfig->racerCount; i++) {
        off = i * 0xb4;
        /* character id 0xc is probably Shy Guy */
        if (*(int *)(data_0217ad00->racers + off) == 0xc) {
            pal = GetHeyhoColorPaletteDataForRacer_from_thumb(i);
            /* reload through the global (no local cache) like the ROM */
            func_02077f9c(i, data_0217ad00->racers + off, pal);
        }
    }
}
