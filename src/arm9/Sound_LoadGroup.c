// PURPOSE: Reports whether a sound group failed to load.
// Passes the group and its load settings to the internal loader.
// Returns one when the loader probably reports failure.

extern int Sound_LoadGroupImpl(void *a0, void *a1);

int Sound_LoadGroup(void *a0, void *a1) {
    return Sound_LoadGroupImpl(a0, a1) == 0;
}
