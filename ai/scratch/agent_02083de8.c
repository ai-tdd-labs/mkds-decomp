/* PURPOSE: Runs a per-object update callback and, if it reported it did
 * something, stamps a shared value onto every live attached part of that
 * object's racer.
 */

typedef unsigned char  u8;
typedef unsigned short u16;

extern u16 *data_0217ae8c;
extern u8   data_02155908[];
extern u8  *data_0217ae84;
extern u16  data_0217ae6c;

typedef int (*UpdateCB)(void *sub, int arg, void *ctx);

void func_02083de8(int idx, void *ctx)
{
    u16 k = data_0217ae8c[*(u16 *)((u8 *)ctx + 0x74)];
    u8 *entry = data_02155908 + idx * 0x20;
    u8 *sub   = entry + k * 0xc;

    UpdateCB cb = *(UpdateCB *)(entry + 0x18);
    if (cb(sub, *(int *)(entry + 0x1c), ctx) == 0)
        return;

    /* re-read the type-id (ROM reloads it; ctx stays in r5) */
    u8 *racer = data_0217ae84 + *(u16 *)((u8 *)ctx + 0x74) * 0x58;
    u16 i = 0;
    if (i < *(u16 *)sub) {
        do {
            u8 *bi = racer + i * 8;
            u16 j = 0;
            do {
                void *p = *(void **)(bi + j * 4 + 0x10);
                if (p != 0)
                    *(u16 *)((u8 *)p + 0x72) = data_0217ae6c;
                j = j + 1;
            } while (j < 2);
            i = i + 1;
        } while (i < *(u16 *)sub);
    }
}
