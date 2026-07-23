/* PURPOSE: Draws one spinning map object on screen, feeding its position,
 *          a rotation matrix and animation data to the 3D geometry engine first.
 *
 * Args: r0 = render context/target, r1 = obj (a map-object state block).
 * It pushes a small mode word (0x1e) and the object's billboard position
 * matrix (obj+4) into the geometry engine via func_01ff9048, then builds a
 * Z-axis rotation matrix from the object's spin angle (0x1fe0 - obj->angle,
 * looked up as sin/cos pairs in table data_0215d4b4). obj->cc selects the
 * spin direction (negated angle when non-zero). The matrix and the 3 words at
 * obj+0x1c are pushed too, the object's NSBTP texture-pattern frame (obj+0xac)
 * is set, and finally it is drawn in 2D/3D via the shared scene pointer.
 * The angle field at obj+0xc4 is probably a signed rotation counter.
 */

typedef unsigned short u16;

/* geometry-command helper: packs `count` words from `ptr` under command `cmd` */
extern void func_01ff9048(int cmd, void *ptr, int count);
extern void *func_020e6cf8(void *p);           /* build billboard matrix at pos */
extern void MTX_RotZ33__from_thumb(void *mtx, int sinv, int cosv);
extern void StructMapObject_SetNsbtpFrame(void *scene, u16 frame);
extern void DrawObject2D3D(void *ctx, void *scene, void *obj);

extern short data_0215d4b4[];  /* sin/cos pair table, 16 angle-units per entry */
extern void *data_0217b0c4;    /* global pointer to the shared scene struct */

void func_0209280c(void *arg0, void *arg1)
{
    void *obj = arg1;
    int diff = 0x1fe0 - *(int *)((char *)obj + 0xc4);
    int v = 0x1e;   /* sp+0 */
    int mtx[9];     /* sp+4 : MtxFx33 rotation matrix */
    int idx;

    func_01ff9048(0x14, &v, 1);
    func_01ff9048(0x19, func_020e6cf8((char *)obj + 4), 0xc);

    if (*(int *)((char *)obj + 0xcc) != 0) {
        idx = (u16)(-diff) >> 4;
        MTX_RotZ33__from_thumb(mtx, data_0215d4b4[idx * 2], data_0215d4b4[idx * 2 + 1]);
    } else {
        idx = (u16)diff >> 4;
        MTX_RotZ33__from_thumb(mtx, data_0215d4b4[idx * 2], data_0215d4b4[idx * 2 + 1]);
    }

    func_01ff9048(0x1a, mtx, 9);
    func_01ff9048(0x1b, (char *)obj + 0x1c, 3);

    StructMapObject_SetNsbtpFrame(data_0217b0c4, *(u16 *)((char *)obj + 0xac));
    DrawObject2D3D(arg0, data_0217b0c4, obj);
}
