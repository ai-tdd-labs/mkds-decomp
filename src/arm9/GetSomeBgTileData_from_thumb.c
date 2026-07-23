// PURPOSE: Updates the background tile data for the current option menu.
// It probably copies the selected tile-data pointer into the active background.
// The returned pointer is the menu's primary background tile data.

typedef struct BgTileData {
    unsigned char pad_00[0x14];
    void *tileData;
} BgTileData;

typedef struct OptionMenuBgState {
    unsigned char pad_00[0x170];
    BgTileData *field_170;
    BgTileData *field_174;
    BgTileData *field_178;
} OptionMenuBgState;

extern OptionMenuBgState *data_0217b354;
extern int GetCurrentOptionMenuKind_from_thumb(void);

#pragma optimize_for_size on
void *GetSomeBgTileData_from_thumb(void)
{
    if (GetCurrentOptionMenuKind_from_thumb() == 1) {
        data_0217b354->field_170->tileData = data_0217b354->field_174;
    } else if (GetCurrentOptionMenuKind_from_thumb() == 2) {
        data_0217b354->field_170->tileData = data_0217b354->field_178;
    }
    return data_0217b354->field_170;
}
