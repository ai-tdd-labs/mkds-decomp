typedef unsigned short u16;
typedef struct { u16 pad0[2]; u16 f4; u16 pad6[3]; u16 fc; } S;

int Maybe_check_0ace68(S *obj) {
    return obj->fc == 0 && obj->f4 != 0;
}
