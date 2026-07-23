// PURPOSE: Checks whether a player's lap count needs updating.
// The player index selects a probably race-state record.
// States 1, 2, and 3 do not need an update.
// Other states probably update only when the stored lap matches the current lap.

typedef struct PlayerLapRecord {
    unsigned char padding_00[0x14];
    int state;
    unsigned char padding_18[0x38 - 0x18];
    int lapCount;
    unsigned char padding_3c[0x8c - 0x3c];
} PlayerLapRecord;

extern PlayerLapRecord *data_0217561c;
extern int GetCurrentLapCount(void);

int UpdatePlayerLapCountIfNot123(int playerId)
{
    int is123 = 0;
    int result;

    if (data_0217561c[playerId].state == 1) {
        goto state_is_123;
    }
    if (data_0217561c[playerId].state == 2) {
        goto state_is_123;
    }
    if (data_0217561c[playerId].state != 3) {
        goto state_is_not_123;
    }

state_is_123:
    is123 = 1;

state_is_not_123:

    result = is123 == 0;
    if (result != 0) {
        result = data_0217561c[playerId].lapCount == GetCurrentLapCount();
    }
    return result != 0;
}
