// PURPOSE: Builds a language-specific scene archive path.
// Writes a scene name, the current language code, and the archive extension into dst.
// Empty names are ignored; this probably prepares a scene archive lookup.

extern char *GetLanguageIdentifierString_from_thumb(void);
extern void Util_SNPrintF(char *dst, int size, const char *fmt, ...);
extern char data_02165148[];
extern char data_0216515c[];

void FormatCarcWithLanguage2_from_thumb(char *dst, const char *name)
{
    if (*(const unsigned char *)name != 0) {
        Util_SNPrintF(dst, 0x80, data_02165148, name,
                      GetLanguageIdentifierString_from_thumb(), data_0216515c);
    }
}
