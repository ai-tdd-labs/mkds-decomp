// PURPOSE: Loads the kart appearance table when the menu needs it.
//
// Takes a heap and a flag. When the flag is set, it loads the table and marks
// the global menu work as not using its alternate table; otherwise it marks
// that alternate mode. It also loads the kart A palette and clears a lock.
// The exact purpose of the alternate-table flag is probably menu state.

typedef unsigned char u8;

typedef struct StructCE {
    u8 pad_000[0x1cc];
    void *kartAPalette;           /* +0x1cc */
    void *kartAppearTable;        /* +0x1d0 */
    u8 pad_1d4[0xc];
    int useAlternateAppearTable;  /* +0x1e0 */
    u8 pad_1e4[0x84];
    int lock;                     /* +0x268 */
} StructCE;

extern StructCE *data_0217ad08;

extern void *LoadKartAppearTablePointer_from_thumb(void *heap);
extern void *GetKartModelMenuKartAPalette_from_thumb(void *heap);

void LoadKartAppearTablePointerCE_from_thumb(void *heap, int loadTable)
{
    if (loadTable != 0) {
        data_0217ad08->useAlternateAppearTable = 0;
        data_0217ad08->kartAppearTable =
            LoadKartAppearTablePointer_from_thumb(heap);
    } else {
        data_0217ad08->useAlternateAppearTable = 1;
    }

    data_0217ad08->kartAPalette =
        GetKartModelMenuKartAPalette_from_thumb(heap);
    data_0217ad08->lock = 0;
}
