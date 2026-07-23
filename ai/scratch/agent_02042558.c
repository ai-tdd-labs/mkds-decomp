// PURPOSE: Loads IPOI records from the course map.
// Advances the section cursor, saves the record count, and stores the entry
// pointer when records are present. The records probably describe item points.

typedef struct CoursePathState {
    unsigned char pad_000[0x54];
    void *ipoiEntries;
    unsigned short ipoiEntryCount;
} CoursePathState;

extern CoursePathState *data_02175620;

extern unsigned short NkmSection_AdvanceHeaderGetEntryCount_from_thumb(
    void **sectionCursor);

int NkmHandler_IPOI_from_thumb(void *sectionCursor)
{
    data_02175620->ipoiEntryCount =
        NkmSection_AdvanceHeaderGetEntryCount_from_thumb(&sectionCursor);

    if (data_02175620->ipoiEntryCount == 0) {
        data_02175620->ipoiEntries = 0;
    } else {
        data_02175620->ipoiEntries = sectionCursor;
    }

    return 1;
}
