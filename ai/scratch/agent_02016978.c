// PURPOSE: Advances an index and returns its checked value.
// The structure probably supplies the bound or validation context at offset 4.
// The helper returns a 64-bit value; this routine returns its upper half as u16.

typedef struct StructTEQ {
    int unk_0;
    int unk_4;
} StructTEQ;

extern unsigned long long MaybeBoundsCheck(int, int);

unsigned short StructTEQ_IncrementValidateIndex(StructTEQ *teq, int index) {
    return (unsigned short)(MaybeBoundsCheck(index + 1, teq->unk_4) >> 32);
}
