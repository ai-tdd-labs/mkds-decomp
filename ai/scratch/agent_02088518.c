/* PURPOSE: Builds the file path of a kart tire texture (tire/<name>.nsbtx).
 * Behaviour: formats "<base><segment>tire/<tireName>.nsbtx" into the shared
 * 0x100-byte path buffer and returns it. The tire name is passed in by the
 * caller; the kart id argument is unused in this variant. */
extern char *data_02165ac8;     /* path segment pointer */
extern char *data_0217af24;     /* base path prefix */
extern char gSharedPathBuffer[];    /* shared 0x100 path buffer */
extern char data_02165f2c[];    /* "nsbtx" */
extern char data_02165f34[];    /* "%s%stire/%s.%s" */

extern int _snprintf(char *buf, unsigned int len, const char *fmt, ...);

char *FormatKartTireNsbtxPath(int kart, char *tireName) {
    /* PARKED: 4/46 near-miss — mwcc pins the segment/ext temporaries to the
     * opposite of r2/r3 vs ROM; a scheduling floor the source form can't flip. */
    _snprintf(gSharedPathBuffer, 0x100, data_02165f34, data_0217af24,
              data_02165ac8, tireName, data_02165f2c);
    return gSharedPathBuffer;
}
