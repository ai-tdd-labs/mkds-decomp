/*
 * PURPOSE: Loads the palette data for kart A from its palette file.
 *
 * Looks up "/kart/palette/kart_a.NCLR" in the kart file archives, reads
 * it as a palette into a temporary handle on the stack, and returns the
 * pointer at offset 0xc of that handle (probably the raw palette data).
 * No arguments; returns the palette-data pointer.
 */

extern void *FindFileBufferGeneric_KME_KM1_KM2_KSB_from_thumb(void *name);
extern void Gfx_ReadPalette(void *dst, void *buf);

extern char data_0216585c[]; /* "/kart/palette/kart_a.NCLR" */

void *GetKartAPaletteData_from_thumb(void)
{
    void *pal; /* filled in by Gfx_ReadPalette (lives at sp+0) */

    Gfx_ReadPalette(&pal, FindFileBufferGeneric_KME_KM1_KM2_KSB_from_thumb(data_0216585c));

    /* return the data pointer at +0xc of the palette object */
    return *(void **)((char *)pal + 0xc);
}
