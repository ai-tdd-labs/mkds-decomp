/* Builds the emblem texture path for a character:
 * "%semblem/%s_emblem.nsbtx" with the character name from a 12-byte struct
 * table (data_02155cf4). Writes into the shared path buffer and returns it. */
typedef struct EmblemEntry {
    char *name;
    int unk4;
    int unk8;
} EmblemEntry;

extern EmblemEntry data_02155cf4[];
extern char *data_0217af24;
extern char gSharedPathBuffer[];
extern char data_02165ed4[];

extern int _snprintf(char *buf, unsigned int len, const char *fmt, ...);

char *FormatEmblemNsbtx(int character) {
    _snprintf(gSharedPathBuffer, 0x100, data_02165ed4, data_0217af24, data_02155cf4[character].name);
    return gSharedPathBuffer;
}
