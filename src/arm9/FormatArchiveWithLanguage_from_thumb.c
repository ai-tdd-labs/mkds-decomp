// PURPOSE: Builds an archive filename with the current language code.
// The first argument is probably an archive name and the second receives the result.
// It writes a name-language .carc filename into the 0x80-byte destination buffer.

extern char *GetLanguageIdentifierString_from_thumb(void);
extern void Util_SNPrintF(char *dst, int size, const char *fmt, ...);
extern char data_02165074[];

void FormatArchiveWithLanguage_from_thumb(const char *archive_name, char *dst)
{
    Util_SNPrintF(dst, 0x80, data_02165074, archive_name,
                  GetLanguageIdentifierString_from_thumb());
}
