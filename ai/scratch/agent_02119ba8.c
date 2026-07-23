// PURPOSE: Starts a sound sequence unless the shared mode disables it.
// The global work object probably tracks the current sound state.
// It resets two state fields before requesting sequence five.
// The shared WRAM halfword selects whether that request is skipped.

typedef struct SoundStateWork {
    unsigned char padding_00[0x38];
    int state_38;
    int state_3C;
} SoundStateWork;

extern SoundStateWork *data_0217d364;
extern unsigned char data_0217d068[];
extern void NNSi_MaybeSndPlayerStartSeq(void *player, int playerNo, int sequenceId);

void func_02119ba8(void)
{
    data_0217d364->state_38 = 4;
    data_0217d364->state_3C = 0;
    if (*(volatile unsigned short *)0x027ffc40 != 2) {
        NNSi_MaybeSndPlayerStartSeq(data_0217d068, 0, 5);
    }
}
