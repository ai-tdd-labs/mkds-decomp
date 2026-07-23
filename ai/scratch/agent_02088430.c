/* PURPOSE: Builds a character's asset file path into the shared path buffer.
 * Behaviour: formats "<base><segment><characterFolder>" via "%s%s%s" into the
 * shared 0x100-byte path buffer and returns the buffer. The base prefix and
 * path segment are fixed globals; the folder name comes from a per-character
 * pointer table (data_02165e80). */
extern char *data_02165e80[];   /* per-character folder names */
extern char *data_02165ac4;     /* path segment pointer */
extern char *data_0217af24;     /* base path prefix */
extern char gSharedPathBuffer[];    /* shared 0x100 path buffer */
extern char data_02165f0c[];    /* "%s%s%s" (this callsite's own pool copy) */

extern int _snprintf(char *buf, unsigned int len, const char *fmt, ...);

char *FormatCharacterPath(int character) {
    _snprintf(gSharedPathBuffer, 0x100, data_02165f0c, data_0217af24,
              data_02165ac4, data_02165e80[character]);
    return gSharedPathBuffer;
}
