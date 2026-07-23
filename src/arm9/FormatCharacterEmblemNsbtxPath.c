/* PURPOSE: Builds the file path of a character's emblem texture (.nsbtx).
 * Arguments: character index, and a flag choosing between two emblem name
 * tables (probably normal vs. alternate/menu emblem set).
 * Behaviour: first formats "<base><segment><characterFolder>" into the shared
 * 0x100-byte path buffer, then appends "<emblemName>.nsbtx" to it in place
 * (buffer is passed to _snprintf as its own first %s), and returns the buffer.
 * The emblem names come from 12-byte-stride tables (data_02155cec when the
 * flag is set, data_02155cf0 otherwise). */
typedef struct EmblemEntry {
    char *name;   /* +0x0: emblem file name */
    int unk4;     /* +0x4 */
    int unk8;     /* +0x8 */
} EmblemEntry;

extern EmblemEntry data_02155cec[];    /* emblem names, flag != 0 */
extern EmblemEntry data_02155cf0[];    /* emblem names, flag == 0 */
extern char *data_02165e80[];   /* per-character folder names */
extern char *data_02165ac4;     /* path segment pointer */
extern char *data_0217af24;     /* base path prefix */
extern char gSharedPathBuffer[];    /* shared 0x100 path buffer */
extern char data_02165fa4[];    /* "nsbtx" */
extern char data_02165fac[];    /* "%s%s%s" */
extern char data_02165fb4[];    /* "%s%s.%s" */

extern int _snprintf(char *buf, unsigned int len, const char *fmt, ...);

char *FormatCharacterEmblemNsbtxPath(int character, int flag) {
    char *name;
    char *ext;

    ext = data_02165fa4;   /* "nsbtx" held in a callee-saved reg across both calls */
    if (flag != 0) {
        name = data_02155cec[character].name;
    } else {
        name = data_02155cf0[character].name;
    }
    _snprintf(gSharedPathBuffer, 0x100, data_02165fac, data_0217af24,
              data_02165ac4, data_02165e80[character]);
    /* appends in place: the buffer itself is the first %s argument */
    _snprintf(gSharedPathBuffer, 0x100, data_02165fb4, gSharedPathBuffer,
              name, ext);
    return gSharedPathBuffer;
}
