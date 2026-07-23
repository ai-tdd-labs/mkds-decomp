/* Find a file buffer in the CRS mount, then retry through CST. */

extern void *FormatGetPathMountBuffer_from_thumb(void *mount,
                                                  const char *path);
extern unsigned char data_0216044e[];

void *FindFileBuffer_CRS_CST_from_thumb(const char *path)
{
    void *buffer;

    buffer = FormatGetPathMountBuffer_from_thumb(
        *(void **)(data_0216044e + 0x0c), path);
    if (buffer == 0) {
        buffer = FormatGetPathMountBuffer_from_thumb(
            *(void **)(data_0216044e + 0x34), path);
    }
    return buffer;
}
