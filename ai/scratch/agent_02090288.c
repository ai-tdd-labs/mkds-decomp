/*
PURPOSE: Conditionally invoke an operation based on readiness and field availability.

This function calls a readiness check. If ready (non-zero), invokes the handler.
If not ready, checks if a target field is available; invokes handler only if available.

Arguments:
  param0: some context handle
  param1: pointer to a struct containing a field at offset 0xb0
*/

#pragma optimize_for_size on

extern int func_0207c078(int);
extern int func_0207c614(int, int);

void func_02090288(int param0, int param1) {
    int ready = func_0207c078(param0);

    int should_continue = 1;
    if (ready == 0) {
        if (*(int *)((int)param1 + 0xb0) == 0) {
            should_continue = 0;
        }
    }

    if (should_continue != 0) {
        func_0207c614(param0, param1);
    }
}
