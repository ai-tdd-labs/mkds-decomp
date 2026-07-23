// PURPOSE: Sets the mute state for a player's tracks.
/*
 * The handle points to a sound-player object pointer.
 * Empty handles are ignored.
 * The player identifier, track mask, and mute flag are sent to the sound command.
 */

typedef unsigned int u32;

typedef struct SoundPlayer {
    unsigned char pad_0x00[0x3c];
    unsigned char player_id;
} SoundPlayer;

extern void func_02020af8(int value1, int value2, int value3);

void NNS_SndPlayerSetTrackMute(SoundPlayer **handle, u32 track_bit_mask, int mute)
{
    if (*handle == 0) {
        return;
    }

    func_02020af8((*handle)->player_id, track_bit_mask, mute);
}
