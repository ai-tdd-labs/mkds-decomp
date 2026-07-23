// PURPOSE: Releases a sound file and performs its final sound cleanup.
/*
 * rawFile is probably the sound-file address, and offset is its byte offset.
 * soundArchive and fileId identify the file passed to the disposal routine.
 * The function then sends the file range to the sound system and cleans it up.
 */

typedef unsigned int u32;

extern void Sound_DisposeFile(void *rawFile, void *soundArchive, u32 fileId);
extern void func_020209bc(u32 parameter1, u32 parameter2);
extern void func_02021c34(void *sound);

void SomeSoundDtorFn(u32 rawFile, u32 offset, void *soundArchive, u32 fileId)
{
    Sound_DisposeFile((void *)rawFile, soundArchive, fileId);
    func_020209bc(rawFile, rawFile + offset); // Notify the sound system of the file range.
    func_02021c34((void *)rawFile);
}
