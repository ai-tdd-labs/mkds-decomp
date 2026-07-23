// PURPOSE: Sets up the sound player and starts a sequence.
//
// Resets two probably sound-related fields in the global work object.
// It starts sequence five unless the shared mode value is two.

typedef struct SoundWork {
    unsigned char _00[0x34];
    int field_34;
    int field_38;
} SoundWork;

extern SoundWork *data_0217d360;
extern unsigned char data_0217d068[];
extern void NNSi_MaybeSndPlayerStartSeq(void *player, int playerNo, int sequenceId);

#pragma optimize_for_size on

void func_02118184(void)
{
    data_0217d360->field_34 = 4;
    data_0217d360->field_38 = 0;

    if (*(volatile unsigned short *)0x027FFC40 != 2) {
        NNSi_MaybeSndPlayerStartSeq(data_0217d068, 0, 5);
    }
}
