/* PURPOSE: Builds the file path of a kart's shadow model (sh_*.nsbmd).
 * Behaviour: formats "<base><segment>shadow/sh_<kartName>.nsbmd" into the
 * shared 0x100-byte path buffer and returns it. The kart name comes from an
 * 8-byte-stride table (data_02155d8c) indexed by the kart id. */
typedef struct KartEntry {
    char *name;   /* +0x0: kart file name */
    int unk4;     /* +0x4 */
} KartEntry;

extern KartEntry data_02155d8c[];   /* kart names, 8-byte stride */
extern char *data_02165ac8;     /* path segment pointer */
extern char *data_0217af24;     /* base path prefix */
extern char gSharedPathBuffer[];    /* shared 0x100 path buffer */
extern char data_02165f14[];    /* "%s%sshadow/sh_%s.nsbmd" */

extern int _snprintf(char *buf, unsigned int len, const char *fmt, ...);

char *FormatKartShadowNsbmdPath(int kart) {
    _snprintf(gSharedPathBuffer, 0x100, data_02165f14, data_0217af24,
              data_02165ac8, data_02155d8c[kart].name);
    return gSharedPathBuffer;
}
