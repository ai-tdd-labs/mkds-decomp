/*
// PURPOSE: Loads an NFTR font and selects its character reader.
The output font receives the processed version and width-entry size.
The reader is selected from the loaded font header, probably by encoding.
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
extern int (*data_021530e8[])(StructFON *);

void NFTR_LoadImpl(G2d_Font *out_font, CommonHeader *nftr_ptr)
{
    int ver = NFTR_Process(nftr_ptr, out_font) - 1;
    unsigned char encoding = ((unsigned char *)out_font->fnif_data)[7];
    out_font->ver_is_old = ver;
    out_font->char_width_entry_size = out_font->ver_is_old != 0 ? 2 : 3;
    out_font->next_char_fn_ptr = data_021530e8[encoding];
}
