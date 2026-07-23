// PURPOSE: Releases an archive after its data has been unloaded.
// The archive pointer is passed to both archive-management routines.
// It returns zero if unloading fails, otherwise unregisters the archive.
// The precise archive structure is probably internal to the file system.

extern int Fs_Archive_UnloadFatFnt(void *archive);
extern void Fs_UnregisterArchive(void *archive);

int Fs_Archive_Dispose(void *archive) {
    if (Fs_Archive_UnloadFatFnt(archive) == 0)
        return 0;

    Fs_UnregisterArchive(archive);
    return 1;
}
