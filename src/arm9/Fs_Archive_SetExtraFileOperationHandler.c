typedef struct FSArchive {
    char pad[0x54];
    void *readFn;   /* 0x54 */
    void *writeFn;  /* 0x58 */
} FSArchive;
void Fs_Archive_SetExtraFileOperationHandler(FSArchive *arc, void *readFn, void *writeFn) {
    if (writeFn == 0) {
        readFn = 0;
    } else if (readFn == 0) {
        writeFn = 0;
    }
    arc->readFn = readFn;
    arc->writeFn = writeFn;
}
