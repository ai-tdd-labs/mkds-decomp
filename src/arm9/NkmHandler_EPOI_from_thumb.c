// PURPOSE: Loads EPOI records from the course map.
// Advances the section cursor and stores the matching record list globally.
// The active course mode probably selects between normal points and EPOI points.

typedef struct CoursePathState {
    unsigned char pad_000[0x20];
    unsigned short mode;
    unsigned char pad_022[0x42];
    void *points;
    unsigned short pointCount;
    unsigned char pad_06a[0x1a];
    void *epoiEntries;
    unsigned short epoiEntryCount;
} CoursePathState;

extern CoursePathState *data_02175620;

extern unsigned short NkmSection_AdvanceHeaderGetEntryCount_from_thumb(
    void **sectionCursor);

int NkmHandler_EPOI_from_thumb(void *sectionCursor)
{
    if (data_02175620->mode > 1) {
        data_02175620->epoiEntryCount =
            NkmSection_AdvanceHeaderGetEntryCount_from_thumb(&sectionCursor);

        if (data_02175620->epoiEntryCount == 0) {
            data_02175620->epoiEntries = 0;
        } else {
            data_02175620->epoiEntries = sectionCursor;
            data_02175620->points = 0;
            data_02175620->pointCount = 0;
        }
    } else {
        data_02175620->pointCount =
            NkmSection_AdvanceHeaderGetEntryCount_from_thumb(&sectionCursor);

        if (data_02175620->pointCount == 0) {
            data_02175620->points = 0;
        } else {
            data_02175620->points = sectionCursor;
            data_02175620->epoiEntries = 0;
            data_02175620->epoiEntryCount = 0;
        }
    }

    return 1;
}
