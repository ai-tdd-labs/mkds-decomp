// PURPOSE: Safely starts the global annotation callback once.
// Disables interrupts while checking and setting the shared initialization flag.
// It probably selects an alternate callback path when global state permits it.

typedef struct AnnotationState {
    unsigned char pad_000[0x526];
    unsigned short initialized;
    unsigned char pad_528[0x5e4 - 0x528];
    void *callbackState;
} AnnotationState;

extern AnnotationState *data_0216fda8;
extern unsigned int Os_DisableIrq(void);
extern void Os_RestoreIrq(unsigned int state);
extern int IsGlobalANSet_from_thumb(void);
extern void func_0200aeb4(void (*callback)(void));
extern int SomeAnnFnPtr_Impl_from_thumb(void);
extern void SomeAnnFnPtr_from_thumb(void);

int func_02009c34(void)
{
    unsigned int state;
    int result = 1;

    state = Os_DisableIrq();
    if (data_0216fda8->initialized == 0) {
        result = 0;
        data_0216fda8->callbackState = 0;
        data_0216fda8->initialized = 1;
        if (IsGlobalANSet_from_thumb() != 0) {
            func_0200aeb4(SomeAnnFnPtr_from_thumb);
        } else {
            result = SomeAnnFnPtr_Impl_from_thumb();
        }
    }
    Os_RestoreIrq(state);
    return result;
}
