// PURPOSE: Loads the portrait graphics files for a player.
// The player value selects the graphics resources to load.
// The output structure receives the four related resource pointers.
// The exact resource formats are probably NCE, palette, NCER, and BNCL data.

typedef struct PlayerGfxData {
    void *nce;
    void *palette;
    void *ncer;
    void *bncl;
} PlayerGfxData;

extern void *GetPortraitNceNcgr_from_thumb(int player);
extern void *GetPortraitNceNcer_from_thumb(int player);
extern void *GetPortraitPalette_from_thumb(int player);
extern void *GetPortraitBNCL_from_thumb(int player);

void LoadPlayerGfxData_from_thumb(int player, PlayerGfxData *data)
{
    data->nce = GetPortraitNceNcgr_from_thumb(player);
    data->ncer = GetPortraitNceNcer_from_thumb(player);
    data->palette = GetPortraitPalette_from_thumb(player);
    data->bncl = GetPortraitBNCL_from_thumb(player);
}
