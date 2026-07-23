// PURPOSE: Updates the selected option menu entry pointer.
// It clears a state field, then uses the current option menu kind to select
// a corresponding entry. The exact state layout is probably menu-related.

typedef struct OptionMenuEntry {
    void *value;
    char pad_04[0x18];
} OptionMenuEntry;

typedef struct OptionMenuState {
    char pad_00[0x24];
    void *field_24;
    void *field_28;
    char pad_2c[0x0c];
    OptionMenuEntry entries[];
} OptionMenuState;

extern OptionMenuState *data_0217b354;
extern int GetCurrentOptionMenuKind_from_thumb(void);

void func_020b3008(void)
{
    data_0217b354->field_24 = 0;
    data_0217b354->field_28 = data_0217b354->entries[GetCurrentOptionMenuKind_from_thumb()].value;
}
