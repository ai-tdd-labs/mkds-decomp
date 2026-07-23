/*
PURPOSE: Loads a related set of sound resources.
This routine takes no arguments and stops if the wave archive or sound bank fails to load.
It loads wave archive 1, bank 0 with flag 2, and then archive 0 from the shared sound heap.
The final archive load result is ignored, so this routine probably prepares optional audio data.
*/

extern void *data_0217d130;

extern int Sound_LoadSwar(int waveArchiveId, void *heap);
extern int Sound_LoadSbnkWithFlags(int bankId, int flags, void *heap);
extern int Sound_LoadSarc(int archiveId, void *heap);

void LoadCertainSwarSbnkSarc(void)
{
    if (!Sound_LoadSwar(1, data_0217d130)) {
        return;
    }

    if (!Sound_LoadSbnkWithFlags(0, 2, data_0217d130)) {
        return;
    }

    Sound_LoadSarc(0, data_0217d130);
}
