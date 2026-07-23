// PURPOSE: Prepares a cell bank after it is loaded.
// The bank contains offsets that are converted into usable pointers.
// Each metatile entry is fixed up against the object table.
// The optional final block is probably another nested cell-bank table.

typedef unsigned short u16;
typedef unsigned int u32;

typedef struct CellBank {
    u16 metatile_count;
    u16 padding_02;
    u32 metatile_entries;
    u32 padding_08;
    u32 nested_bank;
} CellBank;

typedef struct CellBankEntry {
    u32 padding_00;
    u32 object;
} CellBankEntry;

extern CellBankEntry *CellBank_GetMetatileEntry(CellBank *bank, u16 index);
extern void *CellBank_GetObjectTable(CellBank *bank);

void CellBank_InitializeLoad(CellBank *bank)
{
    CellBankEntry *object_table;
    u16 i;
    CellBank *nested_bank;

    bank->metatile_entries += (u32)bank;
    object_table = CellBank_GetObjectTable(bank);

    for (i = 0; i < bank->metatile_count; i++) {
        CellBankEntry *entry;

        entry = CellBank_GetMetatileEntry(bank, i);
        entry->object += (u32)object_table;
    }

    if (bank->nested_bank == 0) {
        return;
    }

    bank->nested_bank += (u32)bank;
    nested_bank = (CellBank *)bank->nested_bank;
    nested_bank->metatile_entries += (u32)nested_bank;
    bank->nested_bank = (u32)nested_bank;
}
