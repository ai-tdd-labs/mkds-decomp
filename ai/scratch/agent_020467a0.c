// PURPOSE: Creates the global race state and enables its setup flag.
/*
 * This routine initializes the global LU data, then marks a halfword in the
 * probably shared race configuration as ready.
 */

typedef unsigned short u16;

typedef struct RaceConfig {
    unsigned char _pad[0x248];
    u16 setupFlag;
} RaceConfig;

extern void CreateGlobalLU(void);
extern RaceConfig *gRaceConfig;

void func_020467a0(void)
{
    CreateGlobalLU();
    gRaceConfig->setupFlag = 1;
}
