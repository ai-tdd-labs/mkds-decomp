/* PURPOSE: Loads the course's AREA records for later use.
 *
 * Takes a cursor pointing at an AREA section, skips its header, and records
 * the entry count and data pointer globally. It then probably prepares the
 * derived lookup data for the supported area types.
 */

typedef struct CoursePathState {
    unsigned char pad_000[0x74];
    void *areaEntries;
    unsigned short areaEntryCount;
} CoursePathState;

extern CoursePathState *data_02175620;

extern unsigned short NkmSection_AdvanceHeaderGetEntryCount_from_thumb(void **sectionCursor);
extern void InitializeAreaType3s_from_thumb(void);
extern void CountAreaType4_from_thumb(void);
extern void CountAreaType2_from_thumb(void);

int NkmHandler_AREA_from_thumb(void *sectionCursor)
{
    data_02175620->areaEntryCount =
        NkmSection_AdvanceHeaderGetEntryCount_from_thumb(&sectionCursor);

    if (data_02175620->areaEntryCount == 0) {
        data_02175620->areaEntries = 0;
    } else {
        data_02175620->areaEntries = sectionCursor;
    }

    InitializeAreaType3s_from_thumb();
    CountAreaType4_from_thumb();
    CountAreaType2_from_thumb();
    return 1;
}
