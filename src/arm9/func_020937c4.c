/* PURPOSE: Sets up (spawns) a moving game object from a spawn-description.
 * Arguments: arg0 = a position record (x,y,z), arg1 = a velocity/scale
 * record (uses fields 0 and 8), arg2 = a small id/type value (u16).
 * Calls func_02100138(0x1a2) (probably registers/inits a subsystem),
 * then asks func_0209bbfc() for a fresh object slot; if none is free it
 * returns silently. Otherwise it fills the object: lifetime 0x258 at
 * +0xa0, copies the position (y is offset by +0x2a000), copies two
 * fields of arg1 to +0x40/+0x48, and stores arg1.x and arg1.z scaled by
 * 6.0 in fx (value*0x6000>>12) at +0x10/+0x18. The id goes to the u16 at
 * +0x7e. Several fields are zeroed. */

typedef struct {
    int x;   /* +0 */
    int y;   /* +4 */
    int z;   /* +8 */
} Vec3;

typedef struct {
    char pad0[4];
    int f4;              /* +0x04 */
    int f8;              /* +0x08 */
    int fc;              /* +0x0c */
    int f10;             /* +0x10 */
    int f14;             /* +0x14 */
    int f18;             /* +0x18 */
    char pad1c[0x40 - 0x1c];
    int f40;             /* +0x40 */
    int f44;             /* +0x44 */
    int f48;             /* +0x48 */
    char pad4c[0x7e - 0x4c];
    unsigned short f7e;  /* +0x7e */
    char pad80[0xa0 - 0x80];
    int fa0;             /* +0xa0 */
    int fa4;             /* +0xa4 */
} Obj;

extern void func_02100138(int arg);
extern Obj *func_0209bbfc(void);

void func_020937c4(Vec3 *pos, Vec3 *vel, int id)
{
    Obj *o;

    func_02100138(0x1a2);
    o = func_0209bbfc();
    if (o == 0)
        return;

    o->fa0 = 0x258;
    o->f4 = pos->x;
    o->f8 = pos->y + 0x2a000;
    o->fc = pos->z;
    o->f40 = vel->x;
    o->f44 = 0;
    o->f48 = vel->z;
    o->f10 = (int)(((long long)vel->x * 0x6000) >> 12);
    o->f14 = 0;
    o->f18 = (int)(((long long)vel->z * 0x6000) >> 12);
    o->f7e = (unsigned short)id;
    o->fa4 = 0;
}
