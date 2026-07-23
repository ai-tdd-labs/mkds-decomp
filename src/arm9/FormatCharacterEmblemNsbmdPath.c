/* PURPOSE: Builds the file path of a character's emblem 3D model (.nsbmd).
 * Arguments: character index, and a flag selecting which emblem-name table
 * to use (probably normal vs. alternate/second emblem set).
 * Behaviour: first formats "%s%s%s" (base path + emblem subdir + character
 * folder) into the shared 0x100-byte path buffer gSharedPathBuffer, then appends
 * the emblem file name with "%s%s.%s" (buffer + name + "nsbmd") by formatting
 * the buffer into itself. Returns the shared buffer. */
typedef struct EmblemNameEntry {
    char *name;   /* +0x0: emblem model file name */
    int unk4;     /* +0x4 */
    int unk8;     /* +0x8 */
} EmblemNameEntry; /* stride 0xc */

extern EmblemNameEntry data_02155cec[]; /* table used when flag != 0 */
extern EmblemNameEntry data_02155cf0[]; /* table used when flag == 0 */
extern char *data_02165e80[];   /* per-character folder names */
extern char *data_02165ac4;     /* path segment (probably emblem subdir) */
extern char *data_0217af24;     /* base path prefix */
extern char gSharedPathBuffer[];    /* shared 0x100 path buffer */
extern char data_02165fbc[];    /* "nsbmd" */
extern char data_02165fc4[];    /* "%s%s%s" */
extern char data_02165fcc[];    /* "%s%s.%s" */

extern int _snprintf(char *buf, unsigned int len, const char *fmt, ...);

char *FormatCharacterEmblemNsbmdPath(int character, int alt) {
    char *name;                     /* r5: survives both snprintf calls */
    char *ext = data_02165fbc;      /* r4: "nsbmd", loaded once up front */

    /* both arms are fully predicated in the ROM (movne/mulne vs moveq/muleq) */
    if (alt != 0) {
        name = data_02155cec[character].name;
    } else {
        name = data_02155cf0[character].name;
    }
    _snprintf(gSharedPathBuffer, 0x100, data_02165fc4, data_0217af24,
              data_02165ac4, data_02165e80[character]);
    /* second pass appends to the buffer by formatting it into itself */
    _snprintf(gSharedPathBuffer, 0x100, data_02165fcc, gSharedPathBuffer,
              name, ext);
    return gSharedPathBuffer;
}
