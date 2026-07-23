// PURPOSE: Updates the active player count for the current mode.
// The selected mode normally sets the count to one.
// Mode five probably derives the count from a network-player bitmask.

typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

typedef struct {
    char _00[0x2c];
    u32 mode;
    char _30[0x7c];
    u16 player_count;
} ModeState;

typedef struct {
    char _00[4];
    int state;
    char _08[0x15ee];
    u8 player_mask;
} NetworkState;

extern ModeState *data_0217d368;
extern NetworkState *data_0217aa00;
extern u32 Math_CountPopulation(u32 value);

#pragma optimize_for_size on
void func_0211bd10(void)
{
    switch (data_0217d368->mode) {
    case 0:
    case 1:
    case 2:
    case 3:
    case 4:
        data_0217d368->player_count = 1;
        break;
    case 5:
        {
            int enabled = 1;

            if (data_0217aa00->state != 8) {
                if (data_0217aa00->state != 9) {
                    enabled = 0;
                }
            }
            if (enabled != 0) {
                data_0217d368->player_count =
                    (u8)Math_CountPopulation(data_0217aa00->player_mask);
            } else {
                data_0217d368->player_count = 0;
            }
        }
        break;
    }
}
