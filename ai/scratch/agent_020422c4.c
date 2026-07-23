// PURPOSE: Counts type-2 area records for the active race.
/*
 * No arguments. It probably scans every loaded AREA record when the race is
 * in mode four, then writes the number of type-2 records to the hardware
 * location selected relative to the active race configuration.
 */

typedef unsigned char u8;
typedef unsigned short u16;

typedef struct RaceConfig {
    u8 pad00[8];
    int mode;
} RaceConfig;

typedef struct CoursePathState {
    u8 pad00[0x78];
    u16 areaCount;
} CoursePathState;

typedef struct NkmAreaRecord {
    u8 pad00[0x44];
    u8 type;
} NkmAreaRecord;

extern RaceConfig *gRaceConfig;
extern CoursePathState *data_02175620;
extern NkmAreaRecord *GetGlobalPENkmAREAByIndex_from_thumb(int index);

void CountAreaType2_from_thumb(void)
{
    u8 count = 0;

    if (gRaceConfig->mode == 4) {
        u16 index = count;

        if (data_02175620->areaCount > 0) {
            do {
                if (GetGlobalPENkmAREAByIndex_from_thumb(index)->type == 2) {
                    count++;
                }
                index++;
            } while (index < data_02175620->areaCount);
        }
    }

    *(volatile u8 *)((unsigned int)gRaceConfig + 0x04001c60) = count;
}
