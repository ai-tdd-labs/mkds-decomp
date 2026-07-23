// PURPOSE: Opens a file using raw data supplied by the caller.
// The file state receives the supplied raw-data arguments before it starts.
// It probably records the request details in fields owned by the file object.
// A successful start updates the file operation flags.

extern int Fs_File_SendOperation(void *file, int operation);

int Fs_File_OpenRaw(void *file, int rawData, int start, int length, int callback)
{
    *(int *)((char *)file + 8) = rawData;
    *(int *)((char *)file + 0x38) = callback;
    *(int *)((char *)file + 0x30) = start;
    *(int *)((char *)file + 0x34) = length;

    if (Fs_File_SendOperation(file, 7) == 0) {
        return 0;
    }

    *(int *)((char *)file + 0xc) |= 0x10;
    *(int *)((char *)file + 0xc) &= ~0x20;
    return 1;
}
