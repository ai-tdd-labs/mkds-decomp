// PURPOSE: Creates the shared sound context.
//
// The function initializes a probably global sound context and saves it in
// the shared control record.  It also clears the following state field.

typedef struct GlobalCX {
    int unknown_00;
    void *soundContext;
    int unknown_08;
} GlobalCX;

extern void *Sound_InitializeContext(void);
extern GlobalCX data_0217d32c;

void CreateSetGlobalCX(void)
{
    data_0217d32c.soundContext = Sound_InitializeContext();
    data_0217d32c.unknown_08 = 0;
}
