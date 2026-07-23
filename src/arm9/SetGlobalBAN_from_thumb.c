// PURPOSE: Stores the first two strings from a BMG message file.
// The BMG argument provides the raw message data.
// This probably updates the global BAN string pointers used elsewhere.

typedef struct GlobalBAN {
    char padding[4];
    void *string0;
    void *string1;
} GlobalBAN;

extern void *Bmg_GetRawStringPointer_from_thumb(void *bmg, int index);
extern GlobalBAN data_0215472c;

void SetGlobalBAN_from_thumb(void *bmg)
{
    void *string0;
    void *string1;

    string0 = Bmg_GetRawStringPointer_from_thumb(bmg, 0);
    string1 = Bmg_GetRawStringPointer_from_thumb(bmg, 1);
    data_0215472c.string0 = string0;
    data_0215472c.string1 = string1;
}
