// PURPOSE: Checks whether a sound bank could be loaded.
// Passes three caller settings and fixed loader flags to the bank lookup.
// Returns one when the lookup probably fails, otherwise zero.

extern void *Sound_GetSbnkPointer(void *a0, void *a1, void *a2, int a3, int a4);

int Sound_LoadSbnkWithFlags(void *a0, void *a1, void *a2) {
    return Sound_GetSbnkPointer(a0, a1, a2, 1, 0) == 0;
}
