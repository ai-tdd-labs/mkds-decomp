/* PURPOSE: Copies the selected saved ghost record into an output buffer.
 * The first argument selects either a course record or an extra record block.
 * The second argument receives the record payload when the selected entry is valid.
 * The helper probably distinguishes normal course indexes from extra-record indexes.
 */

typedef unsigned char u8;
typedef unsigned int u32;

typedef struct RecordEntry {
    u32 unknown0;
    u32 packedValue;
    u32 valid : 1;
    u32 unknownFlags : 31;
    u8 payload[0x14];
} RecordEntry;

typedef struct GhostRecordContext {
    u8 pad_000[0x80c];
    int extraRecordStartIndex;       /* +0x80c */
    u8 pad_810[4];
    int internalCourseIds[32];       /* +0x814 */
    u32 extraRecordBlockIds[10];     /* +0x894 */
    RecordEntry *courseRecords;      /* +0x8bc, entries have a 0x30-byte stride */
    u8 *extraRecordBlocks;           /* +0x8c0, blocks have a 0x230-byte stride */
} GhostRecordContext;

extern GhostRecordContext *data_02174e44;

extern int func_0202dd80(int recordIndex);
extern int func_0202e43c(int value);
extern int GetCourseIdFromInternalId(int internalId);
extern int func_020616c0(RecordEntry *entry, void *output);

void func_0202dc68(int recordIndex, void *output)
{
    if (func_0202dd80(recordIndex) == 0) {
        int internalCourseId =
            func_0202e43c(data_02174e44->internalCourseIds[recordIndex]);
        RecordEntry *courseRecords = data_02174e44->courseRecords;
        int courseId = GetCourseIdFromInternalId(internalCourseId);

        func_020616c0(
            (RecordEntry *)((u8 *)courseRecords + courseId * 0x30), output);
    } else {
        recordIndex -= data_02174e44->extraRecordStartIndex;

        func_020616c0(
            (RecordEntry *)(data_02174e44->extraRecordBlocks +
                            (u8)data_02174e44->extraRecordBlockIds[recordIndex] *
                                0x230),
            output);
    }
}
