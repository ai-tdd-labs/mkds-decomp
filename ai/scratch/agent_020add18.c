// PURPOSE: Stores the two font metrics for a character entry.
// Arguments: output receives two integer values, while font and index select the entry.
// It probably retrieves the character width and a related table value.

typedef struct NFTRHeader NFTRHeader;

extern int NFTR_GetCharacterWidthTileEntry(NFTRHeader *font, int index);
extern int NFTR_SomeFn_2(NFTRHeader *font, int index);

void func_020add18(int *output, NFTRHeader *font, int index)
{
    output[0] = NFTR_GetCharacterWidthTileEntry(font, index);
    output[1] = NFTR_SomeFn_2(font, index);
}
