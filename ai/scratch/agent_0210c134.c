// PURPOSE: Sets up a racer entry and attaches its child objects.
// The entry receives an owner pointer and initializes its small object list.
// It probably starts and updates sound through two callback fields.
// The entry is then registered in the shared racer-entry collection.

typedef void (*Callback)(void);

typedef struct StructMQRacerEntry {
    char unk_00[0x0c];
    char list[8];
    char unk_14[4];
    int unk_18;
    char unk_1c[0x0c];
    void *owner;
    Callback start_callback;
    Callback update_callback;
    unsigned short unk_34;
    char unk_36[2];
    int unk_38;
} StructMQRacerEntry;

extern void IntrusiveListWrapper_InitializeEmpty(void *list, int item_size);
extern void StructMQChild_Create(void *child);
extern void StructMQRacerEntry_MaybeInsertChildEntry(void *entries,
                                                       StructMQRacerEntry *entry);
extern void SfxStart_Unk(void);
extern void SfxUpdate_Unk(void);
extern char data_0217d028[];

void func_0210c134(StructMQRacerEntry *entry, void *owner)
{
    IntrusiveListWrapper_InitializeEmpty(&entry->list, 8);
    entry->unk_38 = 1;
    entry->start_callback = SfxStart_Unk;
    entry->update_callback = SfxUpdate_Unk;
    entry->unk_34 = 0;
    entry->owner = owner;
    entry->unk_18 = 3;
    StructMQChild_Create(&entry->unk_1c);
    StructMQChild_Create(entry);
    StructMQRacerEntry_MaybeInsertChildEntry(data_0217d028, entry);
}
