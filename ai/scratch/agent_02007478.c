// PURPOSE: Loads raw file data and stops if the load fails.
// The argument probably supplies a raw-data descriptor and an archive reference.
// The descriptor receives status 2 only after a full read succeeds.

typedef struct FSFile {
    int fields[19];
} FSFile;

typedef struct RawFileDescriptor {
    void *data;
    int size;
    void *destination;
    int status;
} RawFileDescriptor;

typedef struct ArchiveReference {
    char pad_00[0x10];
    void *mountName;
    void *archive;
} ArchiveReference;

typedef struct RawFileLoadContext {
    char pad_00[0x10];
    RawFileDescriptor *descriptor;
    ArchiveReference *archiveReference;
} RawFileLoadContext;

extern void Fs_File_Initialize(FSFile *f);
extern void *Fs_FindArchiveByMountName(void *mountName, void *archive);
extern int Fs_File_OpenRaw(FSFile *f, void *archive, void *data, void *end, int callback);
extern int Fs_File_Read(FSFile *f, void *buffer, int size);
extern void Fs_File_Close(FSFile *f);
extern void Os_Terminate(void);

void func_02007478(RawFileLoadContext *context)
{
    RawFileDescriptor *descriptor;
    ArchiveReference *archiveReference;
    FSFile file;
    void *data;

    descriptor = context->descriptor;
    archiveReference = context->archiveReference;
    Fs_File_Initialize(&file);
    data = descriptor->data;
    if (Fs_File_OpenRaw(
            &file,
            Fs_FindArchiveByMountName(
                archiveReference->mountName, archiveReference->archive),
            data, (char *)data + descriptor->size, -1) != 0) {
        if (Fs_File_Read(&file, descriptor->destination, descriptor->size) == descriptor->size) {
            descriptor->status = 2;
        }
        Fs_File_Close(&file);
    }
    if (descriptor->status != 2) {
        Os_Terminate();
    }
}
