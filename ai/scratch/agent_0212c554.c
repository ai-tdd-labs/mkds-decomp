// PURPOSE: Sends a sound command for a player's selected track.
/*
 * The handle supplies the player ID when it is valid.
 * The final argument selects a signed halfword from a command table.
 */

typedef struct SoundPlayer {
    unsigned char pad_00[0x3c];
    unsigned char player_id;
} SoundPlayer;

extern short data_02152ce4[];
extern void func_02020d0c(int player_id, int track_mask, int command_value);

void func_0212c554(SoundPlayer **handle, int track_mask, int command_index)
{
    if (*handle == 0) {
        return;
    }

    func_02020d0c((*handle)->player_id, track_mask, data_02152ce4[command_index]);
}
