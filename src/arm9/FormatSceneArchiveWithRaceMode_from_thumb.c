// PURPOSE: Builds a scene archive path for the selected race mode.
// The destination buffer receives a formatted Scene archive filename.
// The mode index selects a ROM-provided name fragment.
// Empty scene names are ignored; this probably prepares a scene archive lookup.

extern void Util_SNPrintF(char *dst, int size, const char *fmt, ...);
extern char *data_02164d28[];
extern char data_021650a0[];
extern char data_021650b4[];

void FormatSceneArchiveWithRaceMode_from_thumb(char *dst, const char *name, int idx)
{
    if (*(const unsigned char *)name != 0) {
        Util_SNPrintF(dst, 0x80, data_021650a0, name, data_02164d28[idx], data_021650b4);
    }
}
