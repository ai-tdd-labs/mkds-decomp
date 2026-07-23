typedef unsigned int u32;

#pragma optimize_for_size on

extern u32 GetRacerType(u32 racerId);

// PURPOSE: Returns whether a racer is a player, ghost, or network racer.
u32 IsRacerPlayerOrGhostOrNet(u32 racerId)
{
    if (GetRacerType(racerId) == 0) {
        goto matched;
    }

    if (GetRacerType(racerId) == 2) {
        goto matched;
    }

    if (GetRacerType(racerId) != 3) {
        goto not_matched;
    }

matched:
    return 1;

not_matched:
    return 0;
}
