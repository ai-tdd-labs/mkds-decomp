// PURPOSE: Returns the current racer's finishing result.
// Gets the active racer's ID and checks whether that racer has finished.
// Returns the stored result when finished, or the default value six otherwise.

#pragma optimize_for_size on

extern int GetCurrentPlayerRacerId_0(void);
extern int IsRacerFinishedRace(unsigned short racer_id);
extern int *data_0217561c;

int func_020b2d54(void) {
    if (IsRacerFinishedRace((unsigned short)GetCurrentPlayerRacerId_0())) {
        return data_0217561c[0x138];
    }
    return 6;
}
