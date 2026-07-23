/*
PURPOSE: Loads a Unicode font from an NFTR resource.
The first argument receives pointers and format details parsed from the resource.
The stored version flag and character-width entry size depend on the NFTR version.
*/

typedef unsigned short u16;

typedef struct CommonHeader CommonHeader;
typedef struct StructFON StructFON;

typedef struct G2d_Font {
    void *fnif_data;
    int (*next_char_fn_ptr)(StructFON *);
    u16 ver_is_old;
    u16 char_width_entry_size;
} G2d_Font;

extern int NFTR_Process(CommonHeader *common_h, G2d_Font *font);
extern int FontEncoding_Unicode_NextCharacter(StructFON *str);

void NFTR_LoadV2(G2d_Font *out_font, CommonHeader *nftr_ptr)
{
    out_font->ver_is_old = NFTR_Process(nftr_ptr, out_font) - 1;
    out_font->char_width_entry_size = out_font->ver_is_old != 0 ? 2 : 3;
    out_font->next_char_fn_ptr = FontEncoding_Unicode_NextCharacter;
}
