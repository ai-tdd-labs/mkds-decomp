// PURPOSE: Loads a cell bank from a tagged data file.
// The first argument receives the initialized cell-bank data.
// The second argument is probably a container of tagged graphics blocks.

extern void *Common_FindBlockByMagic(void *container, unsigned int magic);
extern void CellBank_InitializeLoad(void *cell_bank);

void LoadCellBankFrom(void **cell_bank, void *container)
{
    void *block;

    if (container != 0) {
        block = Common_FindBlockByMagic(container, 0x4345424b);
        if (block != 0) {
            *cell_bank = (char *)block + 8; // Skip the block header.
            CellBank_InitializeLoad(*cell_bank);
        }
    }
}
