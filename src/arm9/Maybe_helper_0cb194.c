#pragma optimize_for_size on
typedef unsigned short u16;
typedef struct { u16 pad[8]; u16 f10; } S;
extern int func_020cb1c4(S *obj);

int Maybe_helper_0cb194(S *obj) {
    if (func_020cb1c4(obj) == 0 && obj->f10 < 5) return 1;
    return 0;
}
