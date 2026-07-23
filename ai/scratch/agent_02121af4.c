// PURPOSE: Chooses a course at random from those tied for the most votes.
// It counts the course votes of active racers and records every tied winner.
// It probably advances the race random-number state to break the tie.
// The selected course ID is written to the global race settings.

typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef unsigned long long u64;

typedef struct RandomContext {
    u64 state;
    u64 multiplier;
    u64 increment;
} RandomContext;

typedef struct GlobalCA {
    u8 padding[0xd0];
    u32 selectedCourseId;
} GlobalCA;

extern u8 *data_0217d384;
extern GlobalCA *GetGlobalCA_from_thumb(void);

void MaybeVSSelectRandomCourseId(void)
{
    u8 highestVoteCount = 0;
    u8 tiedCourseCount = 0;
    u32 tiedCourseIds[4] = {0};
    u8 voteCounts[55] = {0};
    u8 racerIndex;
    u8 courseId;
    u8 *raceState = data_0217d384;
    u32 selectedIndex;
    RandomContext *random;

    for (racerIndex = 0;
         (u32)racerIndex < raceState[0x1f53];
         racerIndex++) {
        if (raceState[0x1f55] & (1 << racerIndex)) {
            voteCounts[
                *(u32 *)(raceState + racerIndex * 0x44 + 0x1e48)]++;

            if (highestVoteCount <
                voteCounts[
                    *(u32 *)(raceState + racerIndex * 0x44 + 0x1e48)]) {
                highestVoteCount =
                    voteCounts[
                        *(u32 *)(raceState + racerIndex * 0x44 + 0x1e48)];
            }
        }
    }

    for (courseId = 0; (u32)courseId < 55; courseId++) {
        if (highestVoteCount == voteCounts[courseId]) {
            tiedCourseIds[tiedCourseCount++] = courseId;
        }
    }

    random = (RandomContext *)((u32)raceState + 0x1954);
    if (tiedCourseCount == 0) {
        selectedIndex = 0;
    } else {
        random->state =
            random->multiplier * random->state + random->increment;

        if (tiedCourseCount == 0) {
            selectedIndex = (u32)(random->state >> 32);
        } else {
            selectedIndex = (u32)(((u64)(u32)(random->state >> 32) *
                                   tiedCourseCount) >>
                                  32);
        }
    }

    GetGlobalCA_from_thumb()->selectedCourseId =
        tiedCourseIds[(u16)selectedIndex];
}
