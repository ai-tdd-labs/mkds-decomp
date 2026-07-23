// PURPOSE: Loads the course IPAT records for later use.
// Advances the IPAT section cursor past its header and stores its entry count.
// The record pointer is cleared when the section is empty.
// This probably makes IPAT path information available to the course loader.

typedef struct CoursePathState {
    unsigned char pad_000[0x5c];
    void *ipatEntries;
    unsigned short ipatEntryCount;
} CoursePathState;

extern CoursePathState *data_02175620;
extern unsigned short NkmSection_AdvanceHeaderGetEntryCount_from_thumb(void **sectionCursor);

int NkmHandler_IPAT_from_thumb(void *sectionCursor)
{
    data_02175620->ipatEntryCount =
        NkmSection_AdvanceHeaderGetEntryCount_from_thumb(&sectionCursor);

    if (data_02175620->ipatEntryCount == 0) {
        data_02175620->ipatEntries = 0;
    } else {
        data_02175620->ipatEntries = sectionCursor;
    }

    return 1;
}
