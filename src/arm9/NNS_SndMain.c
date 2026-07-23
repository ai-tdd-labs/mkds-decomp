/*
PURPOSE: Processes pending sound commands and updates the sound system.
 * This function has no arguments.
 * It probably drains queued sound commands before running the sound managers.
 */
#pragma optimize_for_size on

extern int Sound_CommandReceiveAndReply(int a0);
extern void NNSi_SndPlayerMain(void);
extern void NNSi_SndCaptureMain(void);
extern void NNSi_SndArcStrmMain(void);
extern void Sound_FlushCommand(int a0);

void NNS_SndMain(void) {
    int zero = 0;

    while (Sound_CommandReceiveAndReply(zero) != 0) {
    }
    NNSi_SndPlayerMain();
    NNSi_SndCaptureMain();
    NNSi_SndArcStrmMain();
    Sound_FlushCommand(0);
}
