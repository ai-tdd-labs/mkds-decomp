/* PURPOSE: Loads a font from its data buffer.
 * The first argument receives the loaded font.
 * The second argument is probably an NFTR file buffer.
 * Empty buffers are ignored.
 */

extern void NFTR_LoadImpl(void *font, void *buffer);

void NFTR_Load(void *font, void *buffer)
{
    if (buffer == 0) {
        return;
    }

    NFTR_LoadImpl(font, buffer);
}
