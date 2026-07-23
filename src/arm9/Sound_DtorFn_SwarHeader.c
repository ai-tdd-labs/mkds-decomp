// PURPOSE: Releases a sound archive header and performs its final cleanup.
// Arguments: rawFile is the archive file; soundArchive is probably the archive
// context; fileId selects the file to dispose.
// Behaviour: releases the file, then clears its sound bookkeeping.

typedef unsigned int u32;

extern void Sound_DisposeFile(void *rawFile, void *soundArchive, u32 fileId);
extern void SND_func_0042(void *rawFile);

void Sound_DtorFn_SwarHeader(void *rawFile, void *unused, void *soundArchive, u32 fileId)
{
    Sound_DisposeFile(rawFile, soundArchive, fileId);
    SND_func_0042(rawFile);
}
