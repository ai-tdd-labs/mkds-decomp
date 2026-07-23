// PURPOSE: Finds a map-object file buffer by its name.
// Formats the supplied name under the MapObj directory into a local path.
// The returned pointer is probably the file's data buffer.

typedef unsigned int u32;

extern int _snprintf(char *buffer, u32 size, const char *format, ...);
extern void *FindFileBuffer_MAR_EFT_from_thumb(const char *path);

extern char data_0216b268[];

void *FormatFindMapObjFileBuffer_0_from_thumb(const char *name)
{
    char path[0x100];

    _snprintf(path, 0x100, data_0216b268, name);
    return FindFileBuffer_MAR_EFT_from_thumb(path);
}
