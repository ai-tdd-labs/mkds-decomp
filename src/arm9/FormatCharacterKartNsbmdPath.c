/* PURPOSE: Builds the file path to a character's kart 3D model (.nsbmd).
 *
 * Formats "%s%s%skart_%s.%s" into the shared 0x100-byte path buffer and
 * returns that buffer. Arguments to the format: the base path prefix
 * (data_0217af24), a common directory part (data_02165ac8), the character
 * folder ("mario/" for every 3rd character id, otherwise looked up in a
 * per-character folder table indexed by character/3 — probably alternate
 * skins/karts grouped in triples), the kart name from an 8-byte-stride
 * table, and the "nsbmd" extension. */
typedef struct KartNameEntry {
    char *name;   /* kart model name used in "kart_%s" */
    int unk4;
} KartNameEntry;

extern KartNameEntry data_02155d88[];
extern char *data_02165e80[];  /* per-character folder strings, index = character/3 */
extern char *data_02165ac8;
extern char *data_0217af24;
extern char gSharedPathBuffer[];   /* shared path buffer (0x100 bytes) */
extern char data_02165f88[];   /* "mario/" */
extern char data_02165f80[];   /* "nsbmd" */
extern char data_02165f90[];   /* "%s%s%skart_%s.%s" */

extern int _snprintf(char *buf, unsigned int len, const char *fmt, ...);

char *FormatCharacterKartNsbmdPath(int character) {
    char *ext = data_02165f80; /* hoisted so the extension pointer is materialized early (lr) */
    _snprintf(gSharedPathBuffer, 0x100, data_02165f90,
              data_0217af24,
              data_02165ac8,
              /* eq-arm first: mario folder when character is a multiple of 3 */
              (character % 3 == 0) ? data_02165f88 : data_02165e80[character / 3],
              data_02155d88[character].name,
              ext);
    return gSharedPathBuffer;
}
