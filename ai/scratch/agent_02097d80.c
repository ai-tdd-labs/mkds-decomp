// PURPOSE: Sets up 3D object transformations and draws it with two rendering contexts.
// Initializes matrix state via 3 setup calls, applies position/rotation transformations
// (from struct fields, shifted by 4 bits), then sets up two rendering contexts by
// writing scaled values and using lookup tables, then draws.
//
// Arguments: r0=frame object, r1=state structure with position, rotation, and context data

typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef int s32;

extern void func_01ff9048(u32 id, void *ptr, u32 count);
extern void StructMapObject_SomeFn_8(void *a, void *b, u32 c);
extern void DrawObject2D3D(void *obj, void *state_base, void *state);
extern void *data_0217b0f8;

void func_02097d80(void *a0, void *a1)
{
    volatile u32 sv;

    sv = 0x1e;
    func_01ff9048(0x14, &sv, 1);

    {
        u32 idx = *(u32 *)((char *)a1 + 0xec0);
        u32 *ep = (u32 *)((char *)a1 + 0xa8 + idx * 0x30);
        *(s32 *)((char *)ep + 0x24) = *(s32 *)((char *)a1 + 0x4) >> 4;
        *(s32 *)((char *)ep + 0x28) = *(s32 *)((char *)a1 + 0x8) >> 4;
        *(s32 *)((char *)ep + 0x2c) = *(s32 *)((char *)a1 + 0xc) >> 4;
    }

    func_01ff9048(0x19, (char *)a1 + 0x1c, 0xc);
    func_01ff9048(0x1b, (char *)a1 + 0x1c, 3);

    {
        void *m = data_0217b0f8;
        char *ob = (char *)a1 + 0xe00;

        StructMapObject_SomeFn_8(m, *(void **)((char *)a1 + 0xa4), 0);

        {
            u32 v = (u32)*(u16 *)(ob + 0xc4) << 12;
            *(u32 *)((char *)m + 0x20 + 0xc) = v;
            u16 i = *(u16 *)((char *)m + 0x20 + 0x1a);
            u32 *t = *(u32 **)((char *)m + 0x20 + 0x1c);
            t[i] = v;
        }

        {
            u32 v = (u32)*(u16 *)(ob + 0xc6) << 12;
            m = data_0217b0f8;
            *(u32 *)((char *)m + 0x28 + 0xc) = v;
            u16 i = *(u16 *)((char *)m + 0x28 + 0x1a);
            u32 *t = *(u32 **)((char *)m + 0x28 + 0x1c);
            t[i] = v;
        }

        m = data_0217b0f8;
        DrawObject2D3D(a0, ob, a1);
    }
}
