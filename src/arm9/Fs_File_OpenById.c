// PURPOSE: Opens a file from a two-word file identifier.

typedef struct FsFileId {
    int word0;
    int word1;
} FsFileId;

extern int Fs_File_SendOperation(void *file, int operation);

int Fs_File_OpenById(void *file, FsFileId fileId)
{
    if (fileId.word0 == 0) {
        return 0;
    }

    *(int *)((char *)file + 8) = fileId.word0;
    /* volatile derefs force a fresh reload of both id words, in order,
       before the two stores (matches ROM load scheduling). */
    {
        int a = *(volatile int *)&fileId.word0;
        int b = *(volatile int *)&fileId.word1;
        *(int *)((char *)file + 0x30) = a;
        *(int *)((char *)file + 0x34) = b;
    }

    if (Fs_File_SendOperation(file, 6) == 0) {
        return 0;
    }

    *(int *)((char *)file + 0xc) |= 0x10;
    *(int *)((char *)file + 0xc) &= ~0x20;
    return 1;
}
