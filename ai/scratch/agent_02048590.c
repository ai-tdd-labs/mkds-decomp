// PURPOSE: Loads a mounted file into a newly allocated buffer.
// The path identifies the file, heap supplies the allocation source, and out receives the buffer.
// It probably reuses the shared mount-manager handle and returns the file size or -1.

typedef struct FSFile {
    unsigned char pad_00[0x0c];
    unsigned int flags;
    unsigned char pad_10[0x14];
    unsigned int start;
    unsigned int end;
} FSFile;

extern void *data_021759c8;
extern int Fs_File_Open(FSFile *file, const char *path);
extern int Fs_File_Read(FSFile *file, void *buffer, unsigned int size);
extern void Fs_File_Close(FSFile *file);
extern void *Mem_AllocateHeap(void *heap, unsigned int size);
extern void Mem_FreeHeap(void *heap, void *block);

int ReadFileFromMountManagerHandle_from_thumb(char *path, void *heap, void **out)
{
    void *volatile localHeap;
    void *volatile block;
    int result;
    int size;
    FSFile *file = (FSFile *)((char *)data_021759c8 + 0x968);
    char *pathLocal;

    localHeap = heap;
    pathLocal = path;

    result = 1;
    if ((file->flags & 1) == 0) {
        result = 0;
    }
    if (result != 0) {
        return 0;
    }

    if ((file->flags & 0x10) != 0) {
        Fs_File_Close(file);
    }

    result = Fs_File_Open(file, pathLocal);
    if (result != 0) {
        size = file->end - file->start;
        block = Mem_AllocateHeap(localHeap, size);
        *out = block;
        if (block == 0) {
            result = 0;
        }
        if (result != 0) {
            if (Fs_File_Read(file, block, size) < 0) {
                result = 0;
                Mem_FreeHeap(localHeap, block);
            }
        }
        Fs_File_Close(file);
    }

    if (result == 0) {
        size = -1;
        *out = 0;
    }
    return size;
}
