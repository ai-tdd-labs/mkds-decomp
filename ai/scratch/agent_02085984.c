// PURPOSE: Chooses a race entry for a player and removes a fallback entry from the pool.
// The player number can select one of two configured entries.
// Some player states instead consume the supplied countdown.
// If neither configured entry matches, a probably random list entry is removed.

typedef unsigned short u16;
typedef unsigned int u32;
typedef unsigned long long u64;

typedef struct RandomState {
    u64 state;
    u64 multiplier;
    u64 increment;
} RandomState;

typedef struct IntrusiveListWrapper {
    void *first;
    void *last;
    u16 count;
    u16 linkOffset;
} IntrusiveListWrapper;

extern u64 Multiply64(u64 left, u64 right);
extern void *IntrusiveListWrapper_GetAtIndex(IntrusiveListWrapper *list,
                                             int index);
extern void IntrusiveListWrapper_RemoveItem(IntrusiveListWrapper *list,
                                            void *item);

extern char *data_0217aebc;
extern char *gRaceConfig;

int func_02085984(int playerId, int *countdown)
{
    int result = -1;
    int matched = 0;
    volatile int modeIsTwo;
    volatile int slotOffset;
    volatile int stateBit;
    char *context;
    char *raceConfig;
    int useCountdown = 0;
    int mode;
    u32 slotState;

    context = data_0217aebc;
    mode = *(int *)(context + 0x110);
    modeIsTwo = mode == 2;
    raceConfig = gRaceConfig;

    /* Preserve the compiler's three visible stages of the slot calculation. */
    slotOffset = playerId;
    slotOffset = playerId * 0x30;
    slotState = *(u32 *)(raceConfig + playerId * 0x30 + 0x70);
    if (slotState <= 3) {
        stateBit = 1;
        stateBit = 1 << slotState;
        stateBit = (1 << slotState) & 0xd;
        if (((1 << slotState) & 0xd) != 0) {
            useCountdown = 1;
        }
    }

    if (useCountdown != 0) {
        result = *countdown;
        *countdown = result - 1;
    } else {
        if (mode == 0) {
            int firstIndex;
            int secondIndex;

            firstIndex = (*(int *)(context + 0x11c) != 0) ? 1 : 0;
            secondIndex = (firstIndex == 0) ? 1 : 0;

            if (playerId == *(signed char *)(raceConfig + firstIndex + 0x3d5)) {
                result = 1;
                matched = result;
            } else if (playerId ==
                       (u16)*(signed char *)(raceConfig + secondIndex + 0x3d5)) {
                result = 2;
                matched = 1;
            }
        } else {
            u16 i = 0;

            do {
                if (*(signed char *)(raceConfig + i + 0x3d5) == playerId) {
                    if (i == 0) {
                        result = 1;
                    } else {
                        result = 2;
                        if (modeIsTwo != 0) {
                            result = 1;
                        }
                    }
                    matched = 1;
                    break;
                }
                i = (u16)(i + 1);
            } while (i < 2);
        }

        if (matched == 0) {
            char *shared;
            IntrusiveListWrapper *list;
            u16 listCount;
            RandomState *random;
            u16 range;
            u32 index;
            void *item;

            shared = data_0217aebc;
            list = (IntrusiveListWrapper *)(shared + 0x12c);
            listCount = list->count;
            random = *(RandomState **)(shared + 0x128);
            range = (u16)(listCount - 1);

            if (range == 0) {
                index = 0;
            } else {
                random->state =
                    Multiply64(random->multiplier, random->state) +
                    random->increment;

                if ((u16)(listCount - 1) == 0) {
                    index = (u32)(random->state >> 32);
                } else {
                    index = (u32)(Multiply64(
                                      (u32)(random->state >> 32), range) >>
                                  32);
                }
            }

            item = IntrusiveListWrapper_GetAtIndex(list, (u16)index);
            result = *(int *)item;
            IntrusiveListWrapper_RemoveItem(list, item);
        }
    }

    return result;
}
