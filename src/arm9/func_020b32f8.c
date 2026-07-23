// PURPOSE: Gets the active option menu data pointer.
typedef struct OptionMenuState {
    unsigned char pad_00[0x17c];
    void *field_17c;
    void *field_180;
    void *field_184;
    void *field_188;
} OptionMenuState;

extern OptionMenuState *data_0217b354;
extern int GetCurrentOptionMenuKind_from_thumb(void);

#pragma optimize_for_size on
void *func_020b32f8(void)
{
    int kind;
    void *result = 0;

    kind = GetCurrentOptionMenuKind_from_thumb();
    if (kind == 0) {
        if (data_0217b354->field_17c != 0)
            result = (unsigned char *)data_0217b354->field_17c + 0xc;
    } else if (kind == 1) {
        if (data_0217b354->field_180 != 0)
            result = (unsigned char *)data_0217b354->field_180 + 0xc;
    } else if (kind == 2) {
        if (data_0217b354->field_184 != 0)
            result = (unsigned char *)data_0217b354->field_184 + 0xc;
    } else if (kind == 3) {
        if (data_0217b354->field_188 != 0)
            result = (unsigned char *)data_0217b354->field_188 + 0xc;
    }

    return result;
}
