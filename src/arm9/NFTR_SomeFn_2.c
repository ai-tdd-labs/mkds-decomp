// PURPOSE: Calculates the position of a font entry in its data table.
// The function takes a font object and an entry index.
// It probably adds the table base offset to the helper's indexed stride.
// The helper result is multiplied by the requested index.

typedef unsigned int u32;

typedef struct {
    void *table;
} NFTRHeader;

typedef struct {
    u32 unused0;
    u32 unused4;
    u32 base;
} NFTRTable;

extern int NFTR_SomeFn_3(NFTRHeader *font);

int NFTR_SomeFn_2(NFTRHeader *font, int index) {
    return ((NFTRTable *)font->table)->base + 8 +
           index * NFTR_SomeFn_3(font);
}
