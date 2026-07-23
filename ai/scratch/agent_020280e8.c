// PURPOSE: Checks whether the current object's first value is two.
// Calls the helper that returns the object, then tests its first halfword.
// The returned pointer's exact object type is currently unknown.

extern unsigned short *func_02028110(void);

int func_020280e8(void) {
    return *func_02028110() == 2;
}
