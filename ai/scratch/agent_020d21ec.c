/* PURPOSE: Looks up a map-object file by name inside the "MapObj/" folder.
 *
 * The single argument is a file name string. The function formats
 * "MapObj/<name>" into a 0x100-byte stack buffer with _snprintf and hands
 * the resulting path to FindFileBuffer_CRS_CST_from_thumb, returning that
 * function's result (probably a pointer to the file's data buffer).
 */

typedef unsigned int u32;

extern int _snprintf(char *buffer, u32 size, const char *format, ...);
extern void *FindFileBuffer_CRS_CST_from_thumb(const char *path);

extern char data_0216b25c[]; /* "MapObj/%s" */

void *FormatFindMapObjFileBuffer_from_thumb(const char *name)
{
    char path[0x100];

    _snprintf(path, 0x100, data_0216b25c, name);
    return FindFileBuffer_CRS_CST_from_thumb(path);
}
