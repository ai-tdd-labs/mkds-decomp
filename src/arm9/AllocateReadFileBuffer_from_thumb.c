// PURPOSE: Allocates a buffer and fills it with a file's contents.
// It probably takes a file path and the requested buffer alignment.
// The file size determines the allocation size, and a read failure frees it.

typedef unsigned int u32;

typedef struct FSFile {
    int field_00;
    int field_04;
    int field_08;
    int field_0c;
    int field_10;
    int field_14;
    int field_18;
    int field_1c;
    int field_20;
    int field_24;
    int field_28;
    int field_2c;
    int field_30;
    int field_34;
    int field_38;
    int field_3c;
    int field_40;
    int field_44;
} FSFile;

extern int Fs_IsInitialized(void);
extern void Fs_File_Initialize(FSFile *f);
extern int Fs_File_Open(FSFile *f, const char *path);
extern int Fs_File_Read(FSFile *f, void *buffer, unsigned int size);
extern void Fs_File_Close(FSFile *f);
extern void *GetActiveExecutionContext(void);
extern void *ExecutionContext_GetHeapHandle(void *context);
extern void *Mem_AllocateHeapAligned(void *heap, u32 size, u32 alignment);
extern void DC_SomeClean(void *buffer, int size);
extern void Mem_FreeHeap(void *heap, void *block);

void *AllocateReadFileBuffer_from_thumb(const char *path, u32 alignment)
{
    // PURPOSE: Allocates a buffer and fills it with a file's contents.
    FSFile file;
    int opened;
    void *buffer = 0;
    int size;

    if (Fs_IsInitialized() == 0) {
        return buffer;
    }

    Fs_File_Initialize(&file);
    opened = Fs_File_Open(&file, path);
    if (opened != 0) {
        size = file.field_28 - file.field_24;
        buffer = Mem_AllocateHeapAligned(
            ExecutionContext_GetHeapHandle(GetActiveExecutionContext()), size,
            alignment);
        DC_SomeClean(buffer, size);
        if (buffer == 0) {
            opened = 0;
        } else {
            if (Fs_File_Read(&file, buffer, size) < 0) {
                Mem_FreeHeap(
                    ExecutionContext_GetHeapHandle(GetActiveExecutionContext()),
                    buffer);
                opened = 0;
            }
            Fs_File_Close(&file);
        }
    }

    if (opened == 0) {
        buffer = 0;
    }

    return buffer;
}
