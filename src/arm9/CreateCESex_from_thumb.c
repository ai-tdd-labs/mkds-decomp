// PURPOSE: Creates the memory-backed state for one kart selection entry.
// The heap supplies a 0xf000-byte backing block for the entry's expansion.
// The remaining fields are cleared for later menu setup.

typedef unsigned char u8;
typedef unsigned short u16;

typedef struct CEEntry {
    void *memory;
    void *expansion;
    void *field_08;
    void *field_0c;
    void *field_10;
    void *field_14;
    void *field_18;
    void *field_1c;
    void *field_20;
    void *field_24;
    void *field_28;
    void *field_2c;
    u16 field_30;
} CEEntry;

extern void *Mem_AllocateHeap(void *heap, unsigned int size);
extern void *Mem_Exp_Create(void *memory, unsigned int size, int flags);

void CreateCESex_from_thumb(void *heap, CEEntry *entry)
{
    void *memory;

    memory = Mem_AllocateHeap(heap, 0xf000);
    entry->expansion = Mem_Exp_Create(memory, 0xf000, 0);
    entry->memory = memory;
    entry->field_10 = 0;
    entry->field_0c = entry->field_10;
    entry->field_08 = entry->field_0c;
    entry->field_1c = 0;
    entry->field_18 = entry->field_1c;
    entry->field_14 = entry->field_18;
    entry->field_28 = 0;
    entry->field_24 = entry->field_28;
    entry->field_20 = entry->field_24;
    entry->field_2c = 0;
    entry->field_30 = 0;
}
