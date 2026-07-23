// PURPOSE: Determines whether the title condition is satisfied by cup records.

extern int CupHasRecord(int cup, int cc);
extern int CupGetResult(int cup, int cc);

int IsTitleTrue(void)
{
    int result;
    int one;
    int cc;
    register int j;
    int i;

    one = 1;

    for (i = 0; i < 8; i++) {
        cc = i;
        j = cc;
        if (cc >= 4)
            continue;

        do {
            result = i;
            if (CupHasRecord(i, j)) {
                if (CupGetResult(i, j) == 0)
                    result = one;
            }

            if (result == 0)
                return 0;

            j++;
        } while (j < 4);
    }

    return 1;
}
