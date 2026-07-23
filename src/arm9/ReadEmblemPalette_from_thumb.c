extern void ReadKartModelMenuFile_from_thumb(void *heap, void *name, void *dst);
extern void Gfx_ReadPalette(void *dst, void *palette);
extern char data_02165714[]; // "emblem_s_b.NCLR"
extern char data_0217ad04[];

void ReadEmblemPalette_from_thumb(void *heap)
{
    // PURPOSE: Load the small emblem palette file and upload it to the graphics palette destination.
    void *file;

    ReadKartModelMenuFile_from_thumb(heap, data_02165714, &file);
    Gfx_ReadPalette(data_0217ad04, file);
}
