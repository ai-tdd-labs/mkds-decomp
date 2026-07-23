// PURPOSE: Sets up the default racers for a race.
// Arguments: none.
// It probably supplies two global racer lists to the default configuration.

typedef struct GlobalCA {
    void *unk_00;
    void *unk_04;
} GlobalCA;

extern GlobalCA *GetGlobalCA_from_thumb(void);
extern void StructCO_ConfigureRacerDefault(void *racer, int a1, int a2,
                                           int a3, int a4, int a5);
extern void func_020ccb48(unsigned char racerIndex);

void func_020ccb78(void)
{
    GlobalCA *first;
    GlobalCA *second;
    unsigned char racerIndex;

    first = GetGlobalCA_from_thumb();
    second = GetGlobalCA_from_thumb();
    StructCO_ConfigureRacerDefault(0, (int)first->unk_00,
                                   (int)second->unk_04, 0, -1, 3);

    for (racerIndex = 1; racerIndex < 8; racerIndex++) {
        func_020ccb48(racerIndex);
    }
}
