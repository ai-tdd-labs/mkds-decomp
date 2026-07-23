// PURPOSE: Loads KTPM records from the course map.
//
// Advances the section cursor and stores the KTPM records when this course
// supports them. Unsupported courses and empty sections have no stored data.

typedef struct CoursePathState {
    char pad_000[0x3c];
    void *ktpmEntries;
    unsigned short ktpmEntryCount;
    char pad_042[0xca];
    unsigned short courseIndex;
} CoursePathState;

extern CoursePathState *data_02175620;

extern unsigned short NkmSection_AdvanceHeaderGetEntryCount_from_thumb(
    void **section);

int NkmHandler_KTPM_from_thumb(void *section)
{
    int loaded = 0;

    if (data_02175620->courseIndex < 0x24) {
        data_02175620->ktpmEntryCount = 0;
        data_02175620->ktpmEntries = 0;
        return loaded;
    }

    data_02175620->ktpmEntryCount =
        NkmSection_AdvanceHeaderGetEntryCount_from_thumb(&section);

    if (data_02175620->ktpmEntryCount == 0) {
        data_02175620->ktpmEntries = 0;
    } else {
        data_02175620->ktpmEntries = section;
    }

    return 1;
}
