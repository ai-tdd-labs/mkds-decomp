// PURPOSE: Finds the lowest star rank recorded across all cups.

//
// Arguments: none.  It checks the eight cup entries and their four ranks.
// A rank below five or the special rank nine produces zero; ranks five through
// seven are converted to the corresponding result value.

extern int GetCupEntryRank(unsigned char cup, unsigned char entry);

int GetWorstStarRank_from_thumb(void)
{
    int worst = 7;
    unsigned char cup = 0;
    unsigned char start = cup;
    unsigned char entry;

    do {
        entry = start;
        do {
            int rank = GetCupEntryRank(cup, entry);

            if (rank == 9 || rank < worst) {
                worst = rank;
            }
            if (worst == 9 || worst < 5) {
                return 0;
            }
            entry++;
        } while (entry < 4);
        cup++;
    } while (cup < 8);

    switch (worst) {
    case 5:
        return 1;
    case 6:
        return 2;
    case 7:
        return 3;
    }
    return 0;
}
