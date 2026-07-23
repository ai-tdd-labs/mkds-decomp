// PURPOSE: Sends a sound command for a player handle.
// The handle supplies a player identifier at offset 0x3c.
// The remaining arguments are forwarded to the sound command.

typedef struct SoundPlayer {
    unsigned char pad_0x00[0x3c];
    unsigned char player_id;
} SoundPlayer;

extern void func_02020cbc(unsigned int id, int second, int fourth);

void func_0212c4f4(SoundPlayer **handle, int second, int fourth)
{
    if (*handle == 0) {
        return;
    }

    func_02020cbc((*handle)->player_id, second, fourth);
}
