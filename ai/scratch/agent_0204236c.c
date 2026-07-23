// PURPOSE: Builds linked lists for every type-three AREA record.

typedef unsigned char u8;
typedef unsigned short u16;

typedef struct NkmAreaRecord {
    u8 pad_00[0x3c];
    short groupIndex;
    u8 pad_3e[6];
    u8 areaType;
} NkmAreaRecord;

typedef struct AreaType3Node {
    NkmAreaRecord *area;
    struct AreaType3Node *next;
} AreaType3Node;

typedef struct CoursePathState {
    u8 pad_00[0x74];
    void *areaEntries;
    u16 areaEntryCount;
    u8 pad_07a[0x5e];
    AreaType3Node *areaType3s[8];
} CoursePathState;

extern CoursePathState *data_02175620;
extern void *GetActiveExecutionContext(void);
extern void *ExecutionContext_GetHeapHandle(void *context);
extern NkmAreaRecord *GetGlobalPENkmAREAByIndex_from_thumb(int index);
extern void *Mem_AllocateHeap(void *heap, unsigned int size);

void InitializeAreaType3s_from_thumb(void)
{
    u16 i;
    AreaType3Node **node;
    NkmAreaRecord *area;
    void *heap;

    heap = ExecutionContext_GetHeapHandle(GetActiveExecutionContext());

    for (i = 0; i < 8; i++) {
        data_02175620->areaType3s[i] = 0;
    }

    for (i = 0; i < data_02175620->areaEntryCount; i++) {
        area = GetGlobalPENkmAREAByIndex_from_thumb(i);
        if (area->areaType == 3) {
            node = &data_02175620->areaType3s[area->groupIndex];
            while (*node != 0) {
                node = &(*node)->next;
            }
            *node = Mem_AllocateHeap(heap, 8);
            (*node)->area = area;
            (*node)->next = 0;
        }
    }
}
