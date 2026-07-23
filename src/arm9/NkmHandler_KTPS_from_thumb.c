typedef struct CoursePathState {
    unsigned char pad_000[0x1c];
    void *ktpsEntries;
    unsigned short ktpsEntryCount;
} CoursePathState;

extern CoursePathState *data_02175620;

extern unsigned short NkmSection_AdvanceHeaderGetEntryCount_from_thumb(
    void **sectionCursor);

int NkmHandler_KTPS_from_thumb(void *sectionCursor)
{
    // PURPOSE: Stores the course KTPS records for later use.
    data_02175620->ktpsEntryCount =
        NkmSection_AdvanceHeaderGetEntryCount_from_thumb(&sectionCursor);
    data_02175620->ktpsEntries = sectionCursor;
    return 1;
}
