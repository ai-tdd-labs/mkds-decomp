// PURPOSE: Finds a buffer for a MAR effect file.
// The input is probably a file name or path fragment.
// It tries the primary mounted archive before a fallback archive.

extern void *data_02164e04;
extern void *FormatGetPathMountBuffer_from_thumb(void *archive, void *path);

void *FindFileBuffer_MAR_EFT_from_thumb(void *path)
{
    void *buffer;

    buffer = FormatGetPathMountBuffer_from_thumb(data_02164e04, path);
    if (buffer == 0) {
        buffer = FormatGetPathMountBuffer_from_thumb(
            ((void **)&data_02164e04)[0x12], path);
    }
    return buffer;
}
