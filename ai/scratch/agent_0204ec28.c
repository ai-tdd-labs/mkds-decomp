// PURPOSE: Copies packed course settings into one active course entry.

typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

typedef struct PackedCourseEntry {
    u8 pad_00[0x15];
    u8 flags;
    u8 pad_16[2];
    u32 courseData;
} PackedCourseEntry;

typedef struct CourseEntryList {
    u8 pad_00[0x1e48];
    u8 *entries;
} CourseEntryList;

extern CourseEntryList *data_0217aa00;
extern int GetSomeInternalCourseId(int courseId);

void func_0204ec28(int index, const PackedCourseEntry *source)
{
    data_0217aa00->entries[index * 8] =
        (source->flags << 25) >> 26;
    data_0217aa00->entries[index * 8 + 1] =
        (source->courseData << 28) >> 28;
    data_0217aa00->entries[index * 8 + 2] =
        GetSomeInternalCourseId((u8)((source->courseData << 23) >> 27));
    data_0217aa00->entries[index * 8 + 3] =
        (source->courseData << 16) >> 25;
    data_0217aa00->entries[index * 8 + 4] =
        (source->courseData << 10) >> 26;
    *(u16 *)(data_0217aa00->entries + index * 8 + 6) =
        source->courseData >> 22;
}
