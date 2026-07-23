// PURPOSE: Starts the DWC service and reports what happened.
/*
 * Takes a probably DWC-related context pointer, initializes its helper state,
 * and returns a status selected from the helper result and initialization state.
 * The SDK banner is registered before the context operations begin.
 */

extern void Os_ReferSymbol(const char *symbol);
extern int StructDC_SomeFn_2_from_thumb(int context);
extern int func_02151da8(int value);
extern void StructDC_SomeFn_4_from_thumb(int context);

extern char data_02000b88[];

int MaybeInitializeDwc_from_thumb(int context)
{
    int helper_value;
    int initialized = 0;

    Os_ReferSymbol(data_02000b88);
    helper_value = StructDC_SomeFn_2_from_thumb(context);
    if (func_02151da8(helper_value) != 0) {
        StructDC_SomeFn_4_from_thumb(context);
        initialized = 1;
    }

    if (helper_value < 0) {
        if (initialized != 0) {
            return 2;
        }
        return 3;
    }
    if (initialized != 0) {
        return 1;
    }
    return 0;
}
