// PURPOSE: Builds a scene archive path from a scene name.
// The destination buffer receives a path for the supplied scene name.
// Empty names are ignored; this probably prepares a scene archive lookup.

extern void Util_SNPrintF(char *dst, int size, const char *fmt, ...);
extern char data_0216512c[];
extern char data_02165140[];

void FormatSceneArchive_from_thumb(char *dst, const char *name)
{
    if (*(const unsigned char *)name != 0) {
        Util_SNPrintF(dst, 0x80, data_0216512c, name, data_02165140);
    }
}
