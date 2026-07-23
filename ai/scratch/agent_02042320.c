typedef unsigned char u8;
typedef unsigned short u16;

typedef struct NkmAreaRecord {
    u8 pad_00[0x44];
    u8 type;
} NkmAreaRecord;

typedef struct CoursePathState {
    u8 pad_000[0x78];
    u16 areaEntryCount;
    u8 pad_07a[0x88];
    u16 areaType4Count;
} CoursePathState;

extern CoursePathState *data_02175620;
extern NkmAreaRecord *GetGlobalPENkmAREAByIndex_from_thumb(u16 index);

// PURPOSE: Counts loaded AREA records whose type is four.
void CountAreaType4_from_thumb(void)
{
    u16 count = 0;
    u16 index = 0;

    if (data_02175620->areaEntryCount > 0) {
        do {
            if (GetGlobalPENkmAREAByIndex_from_thumb(index)->type == 4) {
                count++;
            }
            index++;
        } while (index < data_02175620->areaEntryCount);
    }

    data_02175620->areaType4Count = count;
}
