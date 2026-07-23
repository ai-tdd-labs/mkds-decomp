/* PURPOSE: Initializes menu state and starts its queued sound.
The argument selects a probable alternate mode.
The exact state-field meanings are uncertain because their config symbols are unnamed.
If a sound sequence is queued, this starts it on player zero.
*/

typedef struct MenuTransitionState {
    unsigned char padding_000[0x810];
    int transitionProgress;
    int transitionActive;
    int alternateMode;
    unsigned char padding_81c[8];
    int soundSequenceId;
} MenuTransitionState;

extern MenuTransitionState *data_0217d3f8;
extern unsigned char data_0217d068[];

extern void NNSi_MaybeSndPlayerStartSeq(
    void *player,
    int playerNumber,
    unsigned short sequenceId);

void func_02128310(int useAlternateMode)
{
    int sequenceId;

    data_0217d3f8->transitionProgress = 0;
    data_0217d3f8->transitionActive = 1;

    if (useAlternateMode != 0) {
        data_0217d3f8->alternateMode = 1;
    } else {
        data_0217d3f8->alternateMode = 0;
    }

    sequenceId = data_0217d3f8->soundSequenceId;
    if (sequenceId != -1) {
        NNSi_MaybeSndPlayerStartSeq(data_0217d068, 0, sequenceId);
    }
}
