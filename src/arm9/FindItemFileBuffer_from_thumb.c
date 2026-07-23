// PURPOSE: Finds the data buffer for an item file.
// The name selects an item resource, probably from the Item folder.
// It formats the path into a temporary buffer and returns the loaded file.

typedef unsigned int u32;

extern int _snprintf(char *buffer, u32 size, const char *format, ...);
extern void *FindFileBuffer_MAR_EFT_from_thumb(const char *path);

extern char data_0216c604[];

void *FindItemFileBuffer_from_thumb(const char *name)
{
    char path[0x100];

    if (name == 0) {
        return 0;
    }

    _snprintf(path, 0x100, data_0216c604, name);
    return FindFileBuffer_MAR_EFT_from_thumb(path);
}
