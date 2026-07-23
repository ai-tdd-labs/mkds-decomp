// PURPOSE: Checks whether a racer should be treated as a P character.
//
// The argument is probably a racer identifier.  It checks two configured
// racer IDs, the race mode, and two probably special-event states.

typedef struct RaceConfig {
    int field_00;
    char pad_04[0x4];
    int field_08;
    char pad_0c[0x56];
    signed char field_62;
    unsigned char field_63;
} RaceConfig;

extern RaceConfig *gRaceConfig;
extern int IsAwardOrStaffRoll_0(void);

int DetermineIsP_from_thumb(int racerId)
{
    int a = 1;
    int b = 1;
    int c = 1;
    int d = 1;

    if (racerId != gRaceConfig->field_62) {
        if (racerId != gRaceConfig->field_63) {
            d = 0;
        }
    }

    if (d == 0) {
        if (gRaceConfig->field_08 != 4) {
            c = 0;
        }
    }

    if (c == 0) {
        if (IsAwardOrStaffRoll_0() == 0) {
            b = 0;
        }
    }

    if (b == 0) {
        if (gRaceConfig->field_08 != 1) {
            a = 0;
        }
    }

    if (a != 0) {
        return 1;
    }
    return 0;
}
