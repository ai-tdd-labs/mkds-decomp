// PURPOSE: Starts this sound sequence only once.
// The argument is probably passed to the sound-sequence starter as context.
// A global flag prevents the sequence from being started again.

extern int data_0217c794;
extern char data_0217d068[];
extern void NNSi_MaybeSndPlayerStartSeq(void *a0, int a1, void *a2);

void MaybePlaySomeSseqFromSarc0(void *a0) {
    if (data_0217c794 != 0) {
        return;
    }

    data_0217c794 = 1;
    NNSi_MaybeSndPlayerStartSeq(data_0217d068, 0, a0);
}
