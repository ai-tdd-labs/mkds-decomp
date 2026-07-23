// PURPOSE: Disposes a sound file and performs its final sound cleanup.
// The first argument is probably the allocated sound-file data.
// The second argument is the file's byte offset; the remaining arguments identify
// the archive data and file to dispose.

typedef unsigned int u32;

extern void Sound_DisposeFile(void *rawFile, void *soundArchive, u32 fileId);
extern void func_020209e8(int value0, int value1);

void Sound_DtorFn_SomeSarcPointer(void *rawFile, u32 offset,
                                  void *soundArchive, u32 fileId)
{
    Sound_DisposeFile(rawFile, soundArchive, fileId);
    func_020209e8((int)rawFile, (int)((char *)rawFile + offset));
}
