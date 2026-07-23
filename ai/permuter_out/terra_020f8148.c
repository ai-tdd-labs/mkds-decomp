/* PURPOSE: Parses a byte matrix into a sentinel-terminated table.
 *
 * The input begins with the number of records and columns. Each following
 * byte is widened into the corresponding record, and an extra record marks
 * the end of every column with 0xffff.
 */

typedef struct MatrixRecord {
    unsigned short values[18];
} MatrixRecord;

typedef struct ParsedMatrix {
    int recordCount;
    MatrixRecord *records;
} ParsedMatrix;

extern void *GetActiveExecutionContext(void);
extern void *ExecutionContext_GetHeapHandle(void *context);
extern void *Mem_AllocateHeap(void *heap, unsigned int size);

unsigned char *func_020f8148(ParsedMatrix *matrix, unsigned char *input)
{
    int recordCount = input[0];
    /* Preserve the ROM's input+1 calculation before advancing the cursor. */
    unsigned char *second = input + 1;
    int columnCount;
    int columnIndex;
    int recordIndex;
    MatrixRecord *records;

    input += 2;
    columnCount = *second;
    matrix->recordCount = recordCount;
    matrix->records = Mem_AllocateHeap(
        ExecutionContext_GetHeapHandle(GetActiveExecutionContext()),
        (recordCount + 1) * sizeof(MatrixRecord));
    records = matrix->records;

    for (columnIndex = 0; columnIndex < columnCount; columnIndex++) {
        for (recordIndex = 0; recordIndex < recordCount; recordIndex++) {
            records[recordIndex].values[columnIndex] = *input++;
        }
        records[recordIndex].values[columnIndex] = 0xffff;
    }

    return input;
}
