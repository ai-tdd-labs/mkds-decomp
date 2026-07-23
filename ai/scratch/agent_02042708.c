/* PURPOSE: Loads cannon points from the course map.
 *
 * Takes a pointer to the KTPC section and advances it to the entry data.
 * Courses below the supported course index probably have no KTPC section, so
 * their stored pointer and count are cleared. Returns whether data was loaded.
 */

typedef struct CoursePathState {
    char pad_000[0x34];
    void *ktpcEntries;
    unsigned short ktpcEntryCount;
    char pad_03a[0xd2];
    unsigned short courseIndex;
} CoursePathState;

extern CoursePathState *data_02175620;

extern unsigned short NkmSection_AdvanceHeaderGetEntryCount_from_thumb(
    void **section);
extern void InitializePECannonTable_from_thumb(void);

int NkmHandler_KTPC_from_thumb(void *section)
{
    int loaded = 0;

    if (data_02175620->courseIndex < 0x1f) {
        data_02175620->ktpcEntryCount = 0;
        data_02175620->ktpcEntries = 0;
    } else {
        data_02175620->ktpcEntryCount =
            NkmSection_AdvanceHeaderGetEntryCount_from_thumb(&section);
        data_02175620->ktpcEntries = section;
        loaded = 1;
    }

    InitializePECannonTable_from_thumb();
    return loaded;
}
