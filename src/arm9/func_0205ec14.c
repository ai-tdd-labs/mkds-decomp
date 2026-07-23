// PURPOSE: Loads the selected save data when its ghost exists.
// The first argument stores the selected slot byte and receives the loaded data.
// The second argument is probably a course number mapped into one of five slots.

typedef unsigned char u8;

typedef struct SaveSelectorState {
    void *field_00;
} SaveSelectorState;

extern SaveSelectorState *data_0217aa08;
extern int func_0205743c(u8 slot, void *selectionData, int mode);
extern void ReadSaveDataSection_NKFE_from_thumb(void *destination, int slot);

void func_0205ec14(char *selection, int course)
{
    u8 slot = (u8)(course / 5);

    if (func_0205743c(slot, (u8 *)data_0217aa08->field_00 + 0x2e, 2) == 0) {
        *selection = -1;
        return;
    }

    if (slot == *selection) {
        return;
    }

    ReadSaveDataSection_NKFE_from_thumb(selection + 4, slot);
    *selection = slot;
}
