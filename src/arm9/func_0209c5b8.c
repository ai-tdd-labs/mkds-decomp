/* PURPOSE: Draws a map object using the 2D/3D object renderer.
 *
 * Args: r0 = ctx (render context/target), r1 = obj (map-object state block).
 * Feeds a small mode word (0x1e) into the geometry engine, converts the
 * object's position fields (obj+4/8/0xc, fx32) to a coarser fixed-point
 * scale (>>4) cached at obj+0x4c/0x50/0x54, and pushes those 12 words
 * (obj+0x28) under command 0x19. If obj's mode field (obj+0x11c) is 1, an
 * extra 3-word block built from obj+0xbc/obj+0xdc/obj+0xbc (duplicated) is
 * pushed under command 0x1b. The 3 words at obj+0x1c are always pushed too
 * (also command 0x1b). Finally the object is drawn via the shared scene
 * pointer held in data_0217b17c.
 */

/* geometry-command helper: packs `count` words from `ptr` under command `cmd` */
extern void func_01ff9048(int cmd, void *ptr, int count);
extern void DrawObject2D3D(void *ctx, void *scene, void *obj);

extern void *data_0217b17c;   /* global pointer to the shared scene struct */

void func_0209c5b8(void *arg0, void *arg1)
{
    void *ctx = arg0;
    void *obj = arg1;

    {
        int v = 0x1e;
        func_01ff9048(0x14, &v, 1);
    }

    *(int *)((char *)obj + 0x4c) = *(int *)((char *)obj + 4) >> 4;
    *(int *)((char *)obj + 0x50) = *(int *)((char *)obj + 8) >> 4;
    *(int *)((char *)obj + 0x54) = *(int *)((char *)obj + 0xc) >> 4;
    func_01ff9048(0x19, (char *)obj + 0x28, 0xc);

    if (*(int *)((char *)obj + 0x11c) == 1) {
        int a = *(int *)((char *)obj + 0xbc);
        int b = *(int *)((char *)obj + 0xdc);
        int m[3];
        m[0] = a;
        m[1] = b;
        m[2] = a;
        func_01ff9048(0x1b, m, 3);
    }
    func_01ff9048(0x1b, (char *)obj + 0x1c, 3);

    DrawObject2D3D(ctx, data_0217b17c, obj);
}
