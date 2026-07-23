/* PURPOSE: Loads object placement records from a course section.
 *
 * Takes a cursor for the OBJI section and advances it past the header.
 * It records the entry count and the resulting object-record pointer.
 * The stored data is probably used later to create course objects.
 */

typedef struct CoursePathState {
    void *objectEntries;
    unsigned short objectEntryCount;
} CoursePathState;

extern CoursePathState *data_02175620;

extern unsigned short NkmSection_AdvanceHeaderGetEntryCount_from_thumb(
    void **sectionCursor);

int NkmHandler_OBJI_from_thumb(void *sectionCursor)
{
    data_02175620->objectEntryCount =
        NkmSection_AdvanceHeaderGetEntryCount_from_thumb(&sectionCursor);

    if (data_02175620->objectEntryCount == 0) {
        data_02175620->objectEntries = 0;
    } else {
        data_02175620->objectEntries = sectionCursor;
    }

    return 1;
}
