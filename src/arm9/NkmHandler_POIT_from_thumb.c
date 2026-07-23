// PURPOSE: Loads POIT point records from the course data.
//
// Takes a cursor for a POIT section, advances past its header, and stores the
// entry count and record pointer in the shared course state. It probably lets
// later course logic use the loaded points.

typedef struct CoursePathState {
    unsigned char pad_000[0x10];
    void *pointEntries;
    unsigned short pointEntryCount;
} CoursePathState;

extern CoursePathState *data_02175620;

extern unsigned short NkmSection_AdvanceHeaderGetEntryCount_from_thumb(
    void **sectionCursor);

int NkmHandler_POIT_from_thumb(void *sectionCursor)
{
    data_02175620->pointEntryCount =
        NkmSection_AdvanceHeaderGetEntryCount_from_thumb(&sectionCursor);

    if (data_02175620->pointEntryCount == 0) {
        data_02175620->pointEntries = 0;
    } else {
        data_02175620->pointEntries = sectionCursor;
    }

    return 1;
}
