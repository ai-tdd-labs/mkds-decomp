#pragma optimize_for_size on
typedef unsigned short u16;
typedef struct { u16 pad[8]; u16 f10; } S;
extern int func_0202881c(S *obj);

int Maybe_helper_0287ec(S *obj) {
    if (func_0202881c(obj) == 0 && obj->f10 < 5) return 1;
    return 0;
}
