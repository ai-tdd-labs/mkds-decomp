// PURPOSE: Checks whether a generated data record passes a context check.
// A temporary 24-byte record is created first.
// The caller context is then used to validate that record.

typedef struct {
    unsigned int words[6];
} StructDWRecord;

extern int StructDW_SomeFn_from_thumb(StructDWRecord *record);
extern int StructDW_SomeFn_0_from_thumb(StructDWRecord *record, void *context);

int StructDC_SomeFn_4_from_thumb(void *context)
{
    StructDWRecord record;

    if (StructDW_SomeFn_from_thumb(&record) == 0) {
        return 0;
    }

    if (StructDW_SomeFn_0_from_thumb(&record, context) != 0) {
        return 1;
    }

    return 0;
}
