// PURPOSE: Finds a named resource and clears its pending flag.
// The first argument contains a relative resource dictionary pointer.
// The second argument is passed to the Nitro resource lookup routine.
// Returns one only when the resource was found with its low status bit set.

typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

extern void *NNS_G3dGetResDataByName(void *dictionary, const char *name);

int func_020101e8(void *resource, const char *name)
{
    u8 *dictionary;
    u8 *result;

    dictionary = (u8 *)resource + *(u32 *)((u8 *)resource + 8);
    dictionary += *(u16 *)(dictionary + 2);
    result = NNS_G3dGetResDataByName(dictionary, name);
    if (result != 0) {
        if (result[3] & 1) {
            result[3] &= ~1;
            return 1;
        }
    }
    return 0;
}
