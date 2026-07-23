/* PURPOSE: Builds the animation path for a character emblem.
 * The character selects the shared character directory and emblem name.
 * The animation selects a name from a table whose entries are 12 bytes wide.
 * The completed NSBCA path is written to and returned from a shared buffer. */
typedef struct EmblemAnimationEntry {
    char *name;
    char unused[8];
} EmblemAnimationEntry;

extern char *FormatCharacterPath(int character);
extern char *FormatCharacterEmblemName(int character, int emblem);
extern int _snprintf(char *buffer, unsigned int size, const char *format, ...);

extern EmblemAnimationEntry data_021551b0[];
extern char data_0217ad34[];
extern char data_021658e0[];

char *FormatCharacterEmblemNsbcaPath(int character, int animation) {
    char *characterPath = FormatCharacterPath(character);
    char *emblemName = FormatCharacterEmblemName(character, 1);

    _snprintf(data_0217ad34, 0x100, data_021658e0, characterPath, emblemName,
              data_021551b0[animation].name);
    return data_0217ad34;
}
