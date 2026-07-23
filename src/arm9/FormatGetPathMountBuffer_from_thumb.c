// PURPOSE: Gets a file buffer using a mounted path.
// Combines the mount name and supplied path into a temporary path string.
// Paths beginning with a slash probably omit the extra separator.

extern void Util_SNPrintF(char *dst, int size, const char *fmt, ...);
extern void *GetFileBuffer(char *path);
extern char data_02165048[];
extern char data_02165050[];

void *FormatGetPathMountBuffer_from_thumb(char *mount, const char *path)
{
    char fullPath[0x80];

    if (*(const unsigned char *)path == '/') {
        Util_SNPrintF(fullPath, 0x80, data_02165048, mount, path);
    } else {
        Util_SNPrintF(fullPath, 0x80, data_02165050, mount, path);
    }
    return GetFileBuffer(fullPath);
}
