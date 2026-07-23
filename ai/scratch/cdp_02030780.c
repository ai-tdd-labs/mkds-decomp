#pragma optimize_for_size on
typedef unsigned short u16;
typedef struct { u16 pad[8]; u16 f10; } S;
extern int func_020307b0(S *obj);

int Maybe_helper_030780(S *obj) {
    if (func_020307b0(obj) == 0 && obj->f10 < 5) return 1;
    return 0;
}
