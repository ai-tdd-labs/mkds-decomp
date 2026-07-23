// PURPOSE: Loads CPAT records and finds the first path endpoint.
// Advances the course section cursor and stores the CPAT record list.
// When records exist, this probably derives a path endpoint from the first
// record whose leading field is zero.

typedef struct CpatRecord {
    unsigned short field_00;
    unsigned short field_02;
    unsigned char pad_04[3];
    signed char pathIndex;
    unsigned char pad_08[4];
} CpatRecord;

typedef struct CoursePathState {
    unsigned char pad_00[0x4c];
    CpatRecord *cpatRecords;
    unsigned short cpatRecordCount;
    unsigned char pad_52[0x48];
    unsigned short cpatPathEnd;
} CoursePathState;

extern CoursePathState *data_02175620;
extern unsigned short NkmSection_AdvanceHeaderGetEntryCount_from_thumb(
    void **sectionCursor);

int NkmHandler_CPAT_from_thumb(void *sectionCursor)
{
    register CpatRecord *path;
    int i;

    data_02175620->cpatRecordCount =
        NkmSection_AdvanceHeaderGetEntryCount_from_thumb(&sectionCursor);

    if (data_02175620->cpatRecordCount == 0) {
        data_02175620->cpatRecords = 0;
        data_02175620->cpatPathEnd = 0;
        return 1;
    }

    data_02175620->cpatRecords = sectionCursor;
    for (i = 0; i < data_02175620->cpatRecordCount; i++) {
        if (data_02175620->cpatRecords[(unsigned short)i].field_00 == 0) {
            unsigned short pathIndex =
                data_02175620->cpatRecords[(unsigned short)i].pathIndex;
            path = &data_02175620->cpatRecords[pathIndex];
            {
                unsigned short first =
                    data_02175620->cpatRecords[pathIndex].field_00;

                data_02175620->cpatPathEnd = first + path->field_02 - 1;
            }
            break;
        }
    }

    return 1;
}
