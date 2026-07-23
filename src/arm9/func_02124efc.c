// PURPOSE: Initializes each entry in a small array to its default state.
// Arguments: destination entries and their count.
// It probably prepares two transform fields and default status values.

typedef struct Entry {
    int unk_00;
    unsigned short unk_04;
    unsigned short unk_06;
    int unk_08;
    unsigned short unk_0C;
    unsigned short unk_0E;
    int unk_10;
    unsigned char unk_14[0x10];
    unsigned char unk_24[0x10];
    int unk_34;
    int unk_38;
    int unk_3C;
} Entry;

extern void MTX_Identity22_(void *matrix);

void func_02124efc(Entry *entries, int count)
{
    int i;
    int zero;
    int minus_one;
    int zero_2;

    i = 0;
    if (count > 0) {
        zero = 0;
        minus_one = ~i;
        zero_2 = 0;
        do {
            entries->unk_00 = 1;
            entries->unk_04 = zero;
            entries->unk_06 = zero;
            entries->unk_08 = zero;
            entries->unk_0C = zero;
            entries->unk_0E = zero;
            entries->unk_10 = zero;
            MTX_Identity22_(entries->unk_14);
            MTX_Identity22_(entries->unk_24);
            entries->unk_34 = 1;
            entries->unk_38 = minus_one;
            entries->unk_3C = zero_2;
            entries++;
            i++;
        } while (i < count);
    }
}
