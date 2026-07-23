// PURPOSE: Returns the sound identifier for a selected course.
// The argument selects one of twenty course slots.
// Most slots map directly to a fixed sound identifier.
// Slot five probably also depends on the current racer's variant.

#pragma optimize_for_size on

typedef unsigned char u8;
typedef unsigned short u16;

typedef struct RacerRecord {
    u8 padding_00[0x30];
    int type;
    int unknown_34;
    int variant;
} RacerRecord;

typedef struct TypeRecord {
    u8 padding_00[8];
    int type;
    u8 padding_0c[0x1c - 0x0c];
} TypeRecord;

extern int GetCurrentPlayerRacerId(void);
extern TypeRecord *data_0217bc48;

int func_020b846c(int selection)
{
    int result = 0xb;

    switch (selection) {
    case 0:
        result = 0x12;
        break;
    case 1:
        result = 0x10;
        break;
    case 2:
        result = 0x17;
        break;
    case 3:
        result = 0x14;
        break;
    case 4:
        result = 0xd;
        break;
    case 5: {
        RacerRecord *racer =
            (RacerRecord *)(*(u8 * volatile *)0x027e00c8 +
                            GetCurrentPlayerRacerId() * 0x210);
        int variant = data_0217bc48[racer->type].type == 3
                          ? (u16)racer->variant
                          : 0;

        switch (variant) {
        case 1:
            result = 0xd;
            break;
        case 2:
            result = 0xe;
            break;
        case 0:
        case 3:
            result = 0xf;
            break;
        }
        break;
    }
    case 6:
        result = 0x16;
        break;
    case 7:
        result = 0x1b;
        break;
    case 8:
        result = 0x19;
        break;
    case 9:
        result = 0x13;
        break;
    case 10:
        result = 0x18;
        break;
    case 11:
        result = 0x11;
        break;
    case 12:
        result = 0x1a;
        break;
    case 13:
        result = 0x1e;
        break;
    case 14:
        result = 0x1c;
        break;
    case 15:
        result = 0x1d;
        break;
    case 16:
        result = 0x15;
        break;
    case 17:
        result = 0x1f;
        break;
    case 18:
    case 19:
        break;
    }

    return result;
}
