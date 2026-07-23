// PURPOSE: Copies a player's tile palette data into a background canvas.
// The first argument identifies the player data and is prepared by a thumb helper.
// The second argument is probably the destination canvas or palette buffer.
// The prepared data is then copied with the fixed tile and palette settings.

extern void GetSomeBgCanvasTileData_from_thumb(void *playerData);
extern void MaybeSomePlayerTilePaletteCopy(void *playerData, int tileOffset,
                                           void *canvasData, int paletteId,
                                           int tileCount);

void func_020b6dc4(void *playerData, void *canvasData)
{
    GetSomeBgCanvasTileData_from_thumb(playerData);
    MaybeSomePlayerTilePaletteCopy(playerData, 12, canvasData, 27, 8);
}
