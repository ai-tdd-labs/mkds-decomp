// PURPOSE: Configures the default race settings for every racer.

typedef unsigned char u8;

typedef struct RacerSetup {
    void *unk_00;
    int unk_04;
    int unk_08;
    int unk_0c;
    int unk_10;
    int unk_14;
} RacerSetup;

#pragma optimize_for_size on

extern RacerSetup *GetGlobalCA_from_thumb(void);
extern void func_020ccb48(unsigned char racerIndex);
extern void StructCO_ConfigureRacerDefault(void *racer, int a1, int a2,
                                           int a3, int a4, int a5);

void func_020ccab0(void)
{
    volatile RacerSetup * volatile first;
    volatile RacerSetup * volatile second;
    volatile RacerSetup * volatile third;
    register int minusOne = -1;
    int selected;
    u8 racerIndex;

    for (racerIndex = 0; racerIndex < 8; racerIndex++) {
        if (*(void **)((u8 *)GetGlobalCA_from_thumb() + 0xc0) == 0 &&
            GetGlobalCA_from_thumb()[racerIndex].unk_08 == 1) {
            func_020ccb48(racerIndex);
        } else {
            if (*(void **)((u8 *)GetGlobalCA_from_thumb() + 0xdc) != 0) {
                selected = GetGlobalCA_from_thumb()[racerIndex].unk_0c;
            } else {
                selected = minusOne;
            }
            first = GetGlobalCA_from_thumb();
            second = GetGlobalCA_from_thumb();
            third = GetGlobalCA_from_thumb();
            StructCO_ConfigureRacerDefault(
                (void *)(unsigned int)racerIndex,
                (int)first[racerIndex].unk_00,
                second[racerIndex].unk_04,
                third[racerIndex].unk_08,
                selected,
                GetGlobalCA_from_thumb()[racerIndex].unk_10);
        }
    }
}
