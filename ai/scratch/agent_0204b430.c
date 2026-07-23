// PURPOSE: Writes compression state before saving two offsets.
// Saves the second input in a probably global save-work field.
// The remaining inputs are forwarded to the shared compression writer with
// a fixed flag value of one.

typedef struct SaveWork {
    unsigned char _00[0x18];
    int value_18;
} SaveWork;

extern SaveWork *data_021759d4;
extern void SV_MaybeCompressWriteImpl_from_thumb(int, int, int, int, int, int);

void SV_MaybeCompressWriteTwoOffsetsFlagC_from_thumb(int a, int b, int c, int d, int e, int f)
{
    data_021759d4->value_18 = b;
    SV_MaybeCompressWriteImpl_from_thumb(a, c, d, e, 1, f);
}
