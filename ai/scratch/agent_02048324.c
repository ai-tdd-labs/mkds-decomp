// PURPOSE: Builds the staff roll archive path for the current language.
// Writes a StaffRoll .carc filename into dst, including the language suffix.
// The exact path format is supplied by ROM data.

extern char *GetLanguageIdentifierString_from_thumb(void);
extern void Util_SNPrintF(char *dst, int size, const char *fmt, ...);
extern char data_021650d8[];
extern char data_021650bc[];

void FormatStaffRollCarcWithLanguage_from_thumb(char *dst)
{
    Util_SNPrintF(dst, 0x80, data_021650bc,
                  GetLanguageIdentifierString_from_thumb(), data_021650d8);
}
