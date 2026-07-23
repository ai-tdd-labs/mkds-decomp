// PURPOSE: Stops every active sequence player.
// The argument is passed as the stop-fade value to each active player.
// Sixteen fixed-size player records are checked in sequence.

typedef unsigned char u8;

typedef struct SequencePlayer {
    u8 unused_00[0x2c];
    u8 active;
    u8 unused_2d[0x17];
} SequencePlayer;

extern SequencePlayer data_0217d45c[16];
extern void NNSi_SndPlayerStopSeq(SequencePlayer *player, int fadeFrame);

void func_0212c6ac(int fadeFrame)
{
    int index;
    SequencePlayer *player;

    player = data_0217d45c;
    for (index = 0; index < 16; index++, player++) {
        if (player->active != 0) {
            NNSi_SndPlayerStopSeq(player, fadeFrame);
        }
    }
}
