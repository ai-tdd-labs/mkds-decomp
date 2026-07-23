// PURPOSE: Sends a player's track mute setting to the sound system.
// The handle points to a probably sound-player object pointer.
// Empty handles are ignored; its byte-sized player ID and both settings are sent.

typedef unsigned int u32;

typedef struct SoundPlayer {
    unsigned char pad_0x00[0x3c];
    unsigned char player_id;
} SoundPlayer;

extern void func_02020ce4(int value0, int value1, int value2);

void func_0212c524(SoundPlayer **handle, u32 track_bit_mask, int mute)
{
    if (*handle == 0) {
        return;
    }

    func_02020ce4((*handle)->player_id, track_bit_mask, mute);
}
