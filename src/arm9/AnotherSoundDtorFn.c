// PURPOSE: Releases a sound file and performs its final sound cleanup.
// The first argument is probably the raw sound-file address.
// The second argument is the file size or end offset; the other arguments
// identify the sound archive and file metadata passed to the disposal call.

typedef unsigned int u32;

extern void Sound_DisposeFile(void *rawFile, void *soundArchive, u32 fileId);
extern void func_02020990(u32 parameter1, u32 parameter2);
extern void SND_func_0042(void *rawFile);

void AnotherSoundDtorFn(u32 rawFile, u32 offset, void *soundArchive, u32 fileId)
{
    Sound_DisposeFile((void *)rawFile, soundArchive, fileId);
    func_02020990(rawFile, rawFile + offset);
    SND_func_0042((void *)rawFile);
}
