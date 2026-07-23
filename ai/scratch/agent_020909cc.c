// PURPOSE: Computes the cup-record unlock tier for the current save state.
// Every cup and engine class must have a first-place record for tier two.
// Tier one probably depends on the paired special cup and the saved progress rank.

#pragma optimize_for_size on

typedef struct CupProgressState {
    char padding_00[0x7c];
    int progressRank;
    char padding_80[4];
    int selectedCup;
    int engineClass;
    int forceClassThree;
} CupProgressState;

extern CupProgressState *data_0217b488;
extern int CupHasRecord(int cup, int engineClass);
extern int CupGetResult(int cup, int engineClass);

int func_020909cc(void)
{
    int allRecords;
    int cup;
    int engine;
    int one;
    int unlockLevel = 0;
    int selectedCup;
    int selectedEngine;
    int qualified = 0;

    selectedEngine = data_0217b488->engineClass;
    if (data_0217b488->forceClassThree != 0) {
        selectedEngine = 3;
    }
    selectedCup = data_0217b488->selectedCup;

    for (cup = qualified; cup < 8; cup++) {
        one = 1;
        for (engine = qualified; engine < 4; engine++) {
            int hasFirstPlace = qualified;

            if (CupHasRecord(cup, engine) != 0) {
                if (CupGetResult(cup, engine) == 0) {
                    hasFirstPlace = one;
                }
            }

            if (hasFirstPlace == 0) {
                allRecords = 0;
                goto records_checked;
            }
        }
    }
    allRecords = 1;

records_checked:
    if (allRecords != 0) {
        if (selectedCup != 3) {
            if (selectedCup != 7) {
                goto first_check_done;
            }
        }

        if (data_0217b488->progressRank == 0) {
            qualified = 1;
        }
    }

first_check_done:
    if (qualified != 0) {
        unlockLevel = 2;
    } else {
        qualified = 0;

        if (selectedCup != 3) {
            if (selectedCup != 7) {
                goto paired_check_done;
            }
        }

        selectedCup = selectedCup == 7 ? 3 : 7;
        allRecords = 0;

        if (CupHasRecord(selectedCup, selectedEngine) != 0) {
            if (CupGetResult(selectedCup, selectedEngine) <= 2) {
                allRecords = 1;
            }
        }

        if (allRecords != 0) {
            if (data_0217b488->progressRank <= 2) {
                qualified = 1;
            }
        }

paired_check_done:
        if (qualified != 0) {
            unlockLevel = 1;
        }
    }

    return unlockLevel;
}
