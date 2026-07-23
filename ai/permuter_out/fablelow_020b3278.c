/* PURPOSE: Selects a race setting for the current menu state.
 * This reads the active race mode and the current race-menu selection.
 * It passes a probably related setting index to an unknown race subsystem.
 * The exact meaning of the setting index is uncertain.
 */

typedef struct RaceMenuState {
    unsigned char unknown_00[0x28];
    int selection;
} RaceMenuState;

extern RaceMenuState *data_0217b354;

extern int GetRaceMode(void);
extern void func_02105b64(int settingIndex);

#pragma optimize_for_size on
void func_020b3278(void)
{
    if (GetRaceMode() == 5) {
        func_02105b64(4);
    } else switch (data_0217b354->selection) {
    case 0:
    case 8:
        func_02105b64(0);
        break;
    case 1:
    case 3:
        func_02105b64(1);
        break;
    case 2:
    case 7:
    case 10:
        func_02105b64(5);
        break;
    case 4:
    case 5:
    case 6:
        func_02105b64(2);
        break;
    case 9:
        func_02105b64(3);
        break;
    }
}
