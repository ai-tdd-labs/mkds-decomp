/* Builds the .carc scene path for the results screen WITH language code:
 * "/data/Scene/%s%s_%s%s" -> name + (variant depending on mode field f78)
 * + language string + ".carc" into dst (max 0x80). */
extern char *GetLanguageIdentifierString_from_thumb(void);
extern void Util_SNPrintF(char *dst, unsigned int size, const char *fmt, ...);

struct S0217b488 { char pad[0x78]; int f78; };
extern struct S0217b488 *data_0217b488;

struct S021541a8 { char pad[0x50]; char *f50; };
extern struct S021541a8 data_021541a8;

extern char data_021650e0[];
extern char data_021650e4[];
extern char data_02165100[]; /* ".carc" */
extern char data_021650e8[]; /* "/data/Scene/%s%s_%s%s" */

void FormatResultCarcWithLanguage_from_thumb(char *dst)
{
    Util_SNPrintF(dst, 0x80, data_021650e8, data_021541a8.f50,
                  data_0217b488->f78 == 1 ? data_021650e0 : data_021650e4,
                  GetLanguageIdentifierString_from_thumb(), data_02165100);
}
