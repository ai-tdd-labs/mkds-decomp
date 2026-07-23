/* PURPOSE: Loads the menu palette file for kart A and returns a pointer to its color data.
 *
 * Reads "kart/palette/kart_a.NCLR" through the kart-model menu file loader
 * (arg0 is probably the heap to allocate the file buffer from), parses it
 * as a palette with Gfx_ReadPalette, and returns the pointer stored at
 * offset 0xc of the parsed palette block (probably the raw color entries).
 */

extern char data_02165840[]; /* "kart/palette/kart_a.NCLR" */

extern void ReadKartModelMenuFile_from_thumb(void *heap, void *name, void *dst);
extern void Gfx_ReadPalette(void *dst, void *buf);

void *GetKartModelMenuKartAPalette_from_thumb(void *heap)
{
    void *buf;   /* sp+0: file buffer written by the loader */
    struct {
        char *data;         /* sp+4: parsed palette header pointer */
        unsigned int size;  /* sp+8 */
    } pal;

    ReadKartModelMenuFile_from_thumb(heap, data_02165840, &buf);
    Gfx_ReadPalette(&pal, buf);
    return *(void **)(pal.data + 0xc);
}
