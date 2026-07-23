/* PURPOSE: Finds the font tile used to draw a character.
 * The font owns a linked list of character maps, each covering an inclusive
 * character range. A matching map converts the character to a tile index;
 * characters absent from every map return 0xffff.
 */

typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

typedef struct NFTR_CharacterMap {
    u16 first_character;
    u16 last_character;
    u32 map_type;
    struct NFTR_CharacterMap *next;
    u16 first_tile_index;
    u16 reserved;
} NFTR_CharacterMap;

typedef struct NFTR_FontInfo {
    u8 header[0x10];
    NFTR_CharacterMap *character_maps;
} NFTR_FontInfo;

typedef struct NFTR_Font {
    NFTR_FontInfo *info;
} NFTR_Font;

extern int NFTR_CharacterMap_GetTileIndexForCharacter(
    NFTR_CharacterMap *map, u32 character);

int NFTR_GetTileIndexForCharacter(NFTR_Font *font, u32 character)
{
    NFTR_CharacterMap *map = font->info->character_maps;

    if (map == 0) {
        goto not_found;
    }

    do {
        if (map->first_character <= character &&
            character <= map->last_character) {
            return NFTR_CharacterMap_GetTileIndexForCharacter(map, character);
        }

        map = map->next;
    } while (map != 0);

not_found:
    return 0xffff;
}
