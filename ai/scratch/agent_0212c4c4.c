// PURPOSE: Sends the player identifier from a valid sound handle.
// The handle points to a sound-player pointer.
// Empty handles are ignored.

typedef struct SoundPlayer {
    unsigned char pad_0x00[0x3c];
    unsigned char player_id;
} SoundPlayer;

extern void func_02020c94(unsigned char player_id);

void func_0212c4c4(SoundPlayer **handle)
{
    if (*handle == 0) {
        return;
    }

    func_02020c94((*handle)->player_id);
}
