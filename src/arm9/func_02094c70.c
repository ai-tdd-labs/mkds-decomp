/* PURPOSE: Draws a map object's flag/banner-like billboard on screen.
 *
 * Args: r0 = ctx (render context/target), r1 = obj (map-object state block).
 * If obj's NSBTP frame field (obj+0xac) is 0, nothing needs drawing and the
 * function bails out early. Otherwise it assigns the object a polygon id
 * (rolling id from func_020d3c44, keyed to the current driver via
 * GetDriverEntry(gRaceConfig->f62)), pushes the NSBTP frame (obj+0xae),
 * a "some fn 6" property (obj+0xac), a "some fn 7" property (result of
 * func_0206183c), and a "some fn 8" property (obj+0xb0) into the shared
 * scene object (data_0217b0dc). It then feeds a small mode word (0x14) and
 * the object's billboard position matrix (obj+4) into the geometry engine
 * via func_01ff9048. If the current camera/game mode (func_02061818) is 2,
 * an extra 3-word "some max scale" block (0x2000,0x2000,0x2000) is also
 * pushed. The 3 words at obj+0x1c are pushed too, and finally the object is
 * drawn in 2D/3D via the shared scene pointer.
 */

typedef unsigned short u16;

typedef struct { char pad62[0x62]; signed char f62; } RaceConfig;

/* geometry-command helper: packs `count` words from `ptr` under command `cmd` */
extern void func_01ff9048(int cmd, void *ptr, int count);
extern void *func_020e6cf8(void *p);              /* build billboard matrix at pos */
extern void *GetDriverEntry(u16 id);
extern int func_020d3c44(void);                   /* rolling polygon id */
extern int func_0206183c(void);
extern int func_02061818(void);                   /* current camera/game mode */
extern void StructMapObject_MaybeSetPolygonId(void *scene, int id);
extern void StructMapObject_SetNsbtpFrame(void *scene, u16 frame);
extern void StructMapObject_SomeFn_6(void *scene, u16 v);
extern void StructMapObject_SomeFn_7(void *scene, int v);
extern void StructMapObject_SomeFn_8(void *scene, u16 v, int flag);
extern void DrawObject2D3D(void *ctx, void *scene, void *obj);

extern RaceConfig *gRaceConfig;
extern void *data_0217b0dc;   /* global pointer to the shared scene struct */

void func_02094c70(void *arg0, void *arg1)
{
    void *ctx = arg0;
    void *obj = arg1;

    if (*(u16 *)((char *)obj + 0xac) == 0)
        return;

    void volatile *driver = GetDriverEntry(gRaceConfig->f62);
    (void)driver;
    StructMapObject_MaybeSetPolygonId(data_0217b0dc, func_020d3c44());
    StructMapObject_SetNsbtpFrame(data_0217b0dc, *(u16 *)((char *)obj + 0xae));
    StructMapObject_SomeFn_6(data_0217b0dc, *(u16 *)((char *)obj + 0xac));
    StructMapObject_SomeFn_7(data_0217b0dc, func_0206183c());
    StructMapObject_SomeFn_8(data_0217b0dc, *(u16 *)((char *)obj + 0xb0), 0);

    {
        int v = 0x1e;
        func_01ff9048(0x14, &v, 1);
    }
    func_01ff9048(0x19, func_020e6cf8((char *)obj + 4), 0xc);

    if (func_02061818() == 2) {
        int m[3];
        m[0] = 0x2000;
        m[1] = 0x2000;
        m[2] = 0x2000;
        func_01ff9048(0x1b, m, 3);
    }
    func_01ff9048(0x1b, (char *)obj + 0x1c, 3);

    DrawObject2D3D(ctx, data_0217b0dc, obj);
}
