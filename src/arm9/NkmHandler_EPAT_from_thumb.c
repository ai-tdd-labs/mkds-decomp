// PURPOSE: Loads the EPAT course path records.

typedef struct CoursePathState {
    unsigned char pad_000[0x20];
    unsigned short pathMode;
    unsigned char pad_022[0x4a];
    void *paths;
    unsigned short pathCount;
    unsigned char pad_072[0x1a];
    void *alternatePaths;
    unsigned short alternatePathCount;
} CoursePathState;

extern CoursePathState *data_02175620;
extern unsigned short NkmSection_AdvanceHeaderGetEntryCount_from_thumb(
    void **sectionCursor);

int NkmHandler_EPAT_from_thumb(void *sectionCursor)
{
    if (data_02175620->pathMode > 1) {
        data_02175620->alternatePathCount =
            NkmSection_AdvanceHeaderGetEntryCount_from_thumb(&sectionCursor);

        if (data_02175620->alternatePathCount == 0) {
            data_02175620->alternatePaths = 0;
        } else {
            data_02175620->alternatePaths = sectionCursor;
            data_02175620->paths = 0;
            data_02175620->pathCount = 0;
        }
    } else {
        data_02175620->pathCount =
            NkmSection_AdvanceHeaderGetEntryCount_from_thumb(&sectionCursor);

        if (data_02175620->pathCount == 0) {
            data_02175620->paths = 0;
        } else {
            data_02175620->paths = sectionCursor;
            data_02175620->alternatePaths = 0;
            data_02175620->alternatePathCount = 0;
        }
    }

    return 1;
}
