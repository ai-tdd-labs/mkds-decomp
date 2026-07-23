extern void *GetActiveExecutionContext(void *a0);
extern void ExecutionContext_GetHeapHandle(void *a0);

void GetActiveExecutionContextHeapHandle_3(void *a0) {
    ExecutionContext_GetHeapHandle(GetActiveExecutionContext(a0));
}
