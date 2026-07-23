// PURPOSE: Loads a kart model menu file into the requested destination.
// The heap, file name, and destination are supplied by the caller.
// It probably builds the file path in a temporary buffer before loading it.

typedef unsigned int u32;

extern int _snprintf(char *buffer, u32 size, const char *format, ...);
extern void ReadFileFromMountManagerHandle_from_thumb(char *path, void *heap,
                                                      void *dst);
extern char data_02165798[];

void ReadKartModelMenuFile_from_thumb(void *heap, void *name, void *dst)
{
    // PURPOSE: Loads a kart model menu file into the requested destination.
    char path[0x100];

    _snprintf(path, 0x100, data_02165798, name);
    ReadFileFromMountManagerHandle_from_thumb(path, heap, dst);
}
