// PURPOSE: Stores the KTP2 section records for later course-path use.
// Advances the supplied section cursor past its header and saves its count.
// The records pointer and count are probably used to build course paths later.

typedef struct CoursePathState {
    unsigned char pad_000[0x2c];
    void *paths;
    unsigned short pathCount;
} CoursePathState;

extern CoursePathState *data_02175620;

extern unsigned short NkmSection_AdvanceHeaderGetEntryCount_from_thumb(void **sectionCursor);

int NkmHandler_KTP2_from_thumb(void *sectionCursor)
{
    data_02175620->pathCount =
        NkmSection_AdvanceHeaderGetEntryCount_from_thumb(&sectionCursor);
    data_02175620->paths = sectionCursor;
    return 1;
}
