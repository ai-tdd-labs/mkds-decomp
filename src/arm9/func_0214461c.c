// PURPOSE: Checks whether a flagged entry can be processed.
// The entry provides two bit masks followed by data for the helper.
// It returns zero unless both masks contain the requested bit.
// The helper performs the actual processing when the inputs are valid.

typedef unsigned short u16;

extern int func_021445e0(void *context, u16 mask, void *data, int bitIndex);

int func_0214461c(void *context, u16 *entry, int bitIndex)
{
    u16 firstMask = entry[0];
    u16 secondMask = entry[1];
    int bit = 1 << bitIndex;

    if (context == 0)
        return 0;
    if (entry == 0)
        return 0;
    if (!(firstMask & bit))
        return 0;
    if (!(secondMask & bit))
        return 0;

    return func_021445e0(context, firstMask, entry + 2, bitIndex);
}
