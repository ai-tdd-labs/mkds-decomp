/* PURPOSE: Draws a map object (e.g. a Pakkun-Flower body), first logging a
 * few of its fields to a debug/record system, then drawing it.
 * arg0 (r5/r0) is passed straight through as the draw-context argument to
 * DrawObject2D3D. arg1 (r4/r1) is the map-object struct: fields at +4,+8,
 * +0xc are logged as a 4-word record (with a fixed 0x1e tag), a value
 * derived from field +4 (probably a formatted debug string) is logged next,
 * field +0x1f0 is logged 3 times, and the 3 words at +0x1c (probably a
 * position vector) are logged too. The object's polygon id (u16 at +0xa0)
 * is applied via StructMapObject_MaybeSetPolygonId using the current
 * render-object pointer (data_0217b104), then the object is drawn with
 * DrawObject2D3D. */
extern void func_01ff9048(int type, void *data, int count);
extern void *func_020e6cf8(void *arg);
extern void StructMapObject_MaybeSetPolygonId(void *renderObj, unsigned short polygonId);
extern void DrawObject2D3D(void *arg0, void *renderObj, void *mapObj);
extern void *data_0217b104;

void func_02098a58(void *arg0, void *arg1)
{
    int rec[4];

    rec[1] = *(int *)((char *)arg1 + 0x4);
    rec[2] = *(int *)((char *)arg1 + 0x8) + *(int *)((char *)arg1 + 0x1f8);
    rec[3] = *(int *)((char *)arg1 + 0xc);
    rec[0] = 0x1e;
    func_01ff9048(0x14, rec, 1);

    void *fmt = func_020e6cf8(&rec[1]);
    func_01ff9048(0x19, fmt, 0xc);

    int pos[3];
    int v = *(int *)((char *)arg1 + 0x1f0);
    pos[0] = v;
    pos[1] = v;
    pos[2] = v;
    func_01ff9048(0x1b, pos, 3);

    func_01ff9048(0x1b, (char *)arg1 + 0x1c, 3);

    StructMapObject_MaybeSetPolygonId(data_0217b104, *(unsigned short *)((char *)arg1 + 0xa0));
    DrawObject2D3D(arg0, data_0217b104, arg1);
}
