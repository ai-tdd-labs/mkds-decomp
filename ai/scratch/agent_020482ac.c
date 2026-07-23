/* Builds a race .carc path WITH language code: "/data/Scene/%s_%s_%s%s" ->
 * name + table[idx] + language string + ".carc" into dst (max 0x80). Does
 * nothing if name is empty. */
extern char *GetLanguageIdentifierString_from_thumb(void);
extern void Util_SNPrintF(char *dst, int size, const char *fmt, ...);
extern char *data_02164d28[];
extern char data_02165080[]; /* "/data/Scene/%s_%s_%s%s" */
extern char data_02165098[]; /* ".carc" */

void FormatRaceCarcWithLanguage_from_thumb(char *dst, const char *name, int idx) {
    if (*(const unsigned char *)name != 0) {
        Util_SNPrintF(dst, 0x80, data_02165080, name, data_02164d28[idx],
                      GetLanguageIdentifierString_from_thumb(), data_02165098);
    }
}
