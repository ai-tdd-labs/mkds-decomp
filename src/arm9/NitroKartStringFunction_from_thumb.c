/*
 * PURPOSE: Register a caller-supplied object into the next free slot of a
 * global table and bump the table's live-entry count.
 *
 * data_0217aa00 is a global pointer to a large context/table struct. The
 * next free slot index lives at byte offset 0x1e40 (u16). The slot table
 * itself starts at byte offset 0x16a0 with a stride of 0x88 bytes per
 * entry; within an entry, byte offset 0x74 holds the stored object
 * pointer (so absolute field offset is 0x16a0 + idx*0x88 + 0x74 =
 * idx*0x88 + 0x1714). A helper is invoked with the slot address, a
 * biased slot id, a fixed template string, and the caller's object
 * pointer before the slot is written and the count incremented.
 */
typedef unsigned short u16;

typedef struct UnkStruct_0217aa00 UnkStruct_0217aa00;
extern UnkStruct_0217aa00 *data_0217aa00;
extern char data_02154768[];

extern void StructGO_SomeFn_from_thumb(void *slot, u16 slotId, char *name,
                                        void *obj, int param1, int unused);

void NitroKartStringFunction_from_thumb(void *obj, int param1)
{
    UnkStruct_0217aa00 *st = data_0217aa00;
    u16 idx = *(u16 *)((char *)st + 0x1e40);
    int off = idx * 0x88;
    void *slot = (char *)st + 0x16a0 + off;

    StructGO_SomeFn_from_thumb(slot, (u16)(idx + 1000), data_02154768, obj,
                                param1, 0);

    *(void **)((char *)data_0217aa00 + off + 0x1714) = obj;

    *(u16 *)((char *)data_0217aa00 + 0x1e40) =
        (u16)(*(u16 *)((char *)data_0217aa00 + 0x1e40) + 1);
}
