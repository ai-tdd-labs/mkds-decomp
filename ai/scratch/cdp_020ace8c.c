#pragma optimize_for_size on
typedef unsigned short u16;
typedef struct { u16 pad[8]; u16 f10; } S;
extern int func_020acebc(S *obj);

int Maybe_helper_0ace8c(S *obj) {
    if (func_020acebc(obj) == 0 && obj->f10 < 5) return 1;
    return 0;
}
