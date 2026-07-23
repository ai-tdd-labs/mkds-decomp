typedef unsigned char u8;
typedef unsigned int u32;

extern void func_01ff9048(u32 id, void *ptr, u32 count);
extern void *MaybeGetBBMtxAtPosition(void *pos);
extern void DrawObject2DBB(void *a1, void *a2, void *a3);

extern void *data_0217b11c;

void Maybe_helper_09a110(void *a1, void *a2) {
    u32 local = 0x1e;
    func_01ff9048(0x14, &local, 1);
    func_01ff9048(0x19, MaybeGetBBMtxAtPosition((u8 *)a2 + 4), 0xc);
    func_01ff9048(0x1b, (u8 *)a2 + 0x1c, 3);
    DrawObject2DBB(a1, data_0217b11c, a2);
}
