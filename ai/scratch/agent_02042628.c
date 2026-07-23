// PURPOSE: Loads CPOI records and counts their usable entries.

typedef struct NkmCpoiRecord {
    unsigned char pad_00[0x20];
    short selector;
} NkmCpoiRecord;

typedef struct CoursePathState {
    unsigned char pad_000[0x44];
    NkmCpoiRecord *cpoiEntries;
    unsigned short cpoiEntryCount;
    unsigned char pad_04a[0x4e];
    unsigned short cpoiUsableEntryCount;
} CoursePathState;

extern CoursePathState *data_02175620;
extern unsigned short NkmSection_AdvanceHeaderGetEntryCount_from_thumb(
    void **sectionCursor);

int NkmHandler_CPOI_from_thumb(void *sectionCursor)
{
    unsigned short entryIndex;
    unsigned short usableEntryCount;

    data_02175620->cpoiEntryCount =
        NkmSection_AdvanceHeaderGetEntryCount_from_thumb(&sectionCursor);

    if (data_02175620->cpoiEntryCount == 0) {
        data_02175620->cpoiEntries = 0;
        return 1;
    }

    data_02175620->cpoiEntries = sectionCursor;
    usableEntryCount = 0;

    for (entryIndex = 0; entryIndex < data_02175620->cpoiEntryCount;
         entryIndex++) {
        if (data_02175620->cpoiEntries[entryIndex].selector !=
            ~usableEntryCount) {
            usableEntryCount++;
        }
    }

    data_02175620->cpoiUsableEntryCount = usableEntryCount;
    return 1;
}
