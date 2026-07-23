// PURPOSE: Prepares a loaded font resource for use by the text renderer.
// The first argument is an NFTR file and the second receives its font data.
// It accepts the current and legacy formats, fixes internal offsets, and
// adapts the legacy encoding layout before returning the detected version.

typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

typedef struct CommonHeader {
    u32 magic;
    u16 byte_order;
    u16 version;
    u32 total_size;
    u16 header_size;
    u16 block_count;
} CommonHeader;

typedef struct NFTR_FNIFBlock {
    u8 font_type;
    u8 height;
    u16 alternate_glyph;
    u8 default_left;
    u8 default_width;
    signed char default_advance;
    u8 encoding;
    void *glyph_block;
    void *width_block;
    void *map_block;
} NFTR_FNIFBlock;

typedef struct G2d_Font {
    NFTR_FNIFBlock *fnif_data;
} G2d_Font;

extern void Os_Terminate(void);
extern void NFTR_MakeAbsoluteOffsets(CommonHeader *header);
extern void *Common_FindBlockByMagic(void *container, u32 magic);

static inline int Common_HasMagic(CommonHeader *header, u32 magic)
{
    if (header != 0 && header->magic == magic)
        return 1;
    return 0;
}

static inline int Common_HasVersion(CommonHeader *header, u16 version)
{
    if (header != 0 && header->version == version)
        return 1;
    return 0;
}

static inline int Common_IsValid(CommonHeader *header, u32 magic, u16 version)
{
    return header != 0 &&
           Common_HasMagic(header, magic) &&
           Common_HasVersion(header, version);
}

int NFTR_Process(CommonHeader *header, G2d_Font *font)
{
    int old_version;
    void *block;

    if (Common_IsValid(header, 0x4e465452, 0x100)) {
        old_version = 0;
    } else if (Common_IsValid(header, 0x4e465452, 1)) {
        old_version = 1;
    } else {
        Os_Terminate();
    }

    NFTR_MakeAbsoluteOffsets(header);
    block = Common_FindBlockByMagic(header, 0x46494e46);
    if (block == 0) {
        font->fnif_data = 0;
        return 0;
    }

    font->fnif_data = (NFTR_FNIFBlock *)((u8 *)block + 8);
    if (old_version != 0) {
        font->fnif_data->encoding = font->fnif_data->default_advance;
        font->fnif_data->default_advance = 0;
    }

    return old_version + 1;
}
