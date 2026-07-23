// PURPOSE: Adds a child entry to this racer entry when the child is unused.
// The first argument is probably the list-owning racer entry.
// The second argument points at the child-entry storage.
// The racer entry supplies the child's byte offset within that storage.

typedef unsigned short u16;

typedef struct IntrusiveListWrapper IntrusiveListWrapper;

typedef struct StructMQRacerEntry {
    unsigned char padding[0xA];
    u16 child_offset;
} StructMQRacerEntry;

typedef struct StructMQChildEntry {
    unsigned char padding[8];
    StructMQRacerEntry *parent;
} StructMQChildEntry;

extern void IntrusiveListWrapper_InsertLast(IntrusiveListWrapper *list, void *item);

int StructMQRacerEntry_MaybeInsertChildEntry(StructMQRacerEntry *entry, void *child)
{
    StructMQChildEntry *child_entry;
    int inserted;

    child_entry = (StructMQChildEntry *)((unsigned char *)child + entry->child_offset);
    if (child_entry->parent != 0) {
        inserted = 0;
    } else {
        inserted = 1;
        child_entry->parent = entry;
    }

    if (inserted == 0)
        goto not_inserted;

    IntrusiveListWrapper_InsertLast((IntrusiveListWrapper *)entry, child);
    goto inserted_entry;

not_inserted:
    return 0;

inserted_entry:
    return 1;
}
