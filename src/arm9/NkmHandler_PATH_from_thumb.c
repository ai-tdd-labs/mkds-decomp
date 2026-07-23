// PURPOSE: Loads the course PATH records for later use.
//
// Takes a cursor for the PATH section, advances it past its header, and stores
// its entry count and records globally. Empty sections probably have no data.

typedef struct CoursePathState {
    unsigned char pad_000[8];
    void *paths;
    unsigned short pathCount;
} CoursePathState;

extern CoursePathState *data_02175620;

extern unsigned short NkmSection_AdvanceHeaderGetEntryCount_from_thumb(void **sectionCursor);

int NkmHandler_PATH_from_thumb(void *sectionCursor)
{
    data_02175620->pathCount =
        NkmSection_AdvanceHeaderGetEntryCount_from_thumb(&sectionCursor);

    if (data_02175620->pathCount == 0) {
        data_02175620->paths = 0;
    } else {
        data_02175620->paths = sectionCursor;
    }

    return 1;
}
