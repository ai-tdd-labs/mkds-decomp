// PURPOSE: Starts the selected game execution function.
// Arguments: the function to run through the main execution context.
// It probably installs the function and then begins that context with its startup tag.

extern int data_02174e88[];
extern void ExecutionContext_SetFunction(void *context, void (*function)(void));
extern void ExecutionContext_Execute(void *context, int tag);

void SetExecuteStart(void (*function)(void)) {
    ExecutionContext_SetFunction(data_02174e88, function);
    ExecutionContext_Execute(data_02174e88, 0xBEEF); /* startup tag */
}
