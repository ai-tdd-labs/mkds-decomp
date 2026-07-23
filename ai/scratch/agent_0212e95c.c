// PURPOSE: Reports whether a sound bank failed to load.
// Passes the bank and load setting to the sound-bank pointer helper.
// Returns one when the helper probably could not load the bank.

extern void *Sound_GetSbnkPointer(void *a0, void *a1, void *a2, int a3, int a4);

int Sound_LoadSbnk(void *a0, void *a1) {
    return Sound_GetSbnkPointer(a0, (void *)0xff, a1, 1, 0) == 0;
}
