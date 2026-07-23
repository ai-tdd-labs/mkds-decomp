// PURPOSE: Initializes an object's reaction state.
// The object copies two default vectors and stores its caller-supplied mode.
// It then clears the remaining timers and flags before calculating its reaction.
// The exact meaning of the default vector is probably a reaction offset.

typedef struct {
    int x;
    int y;
    int z;
} Vec3;

typedef struct {
    char pad00[0x18];
    Vec3 *f18;
} ObjSource;

typedef struct Obj {
    char pad00[0x08];
    ObjSource *f08;
    char pad0c[0x38];
    Vec3 f44;
    char pad50[0x10];
    Vec3 f60;
    unsigned short f6c;
    unsigned short f6e;
    int f70;
    int f74;
    unsigned short f78;
    unsigned short f7a;
    int f7c;
    unsigned short f80;
    char pad82[0x02];
    int f84;
    char pad88[0x08];
    int f90;
    int f94;
    int f98;
    char pad9c[0x04];
    int fa0;
    char padA4[0x04];
    int fa8;
    unsigned short fac;
    char padAe[0x02];
    int fb0;
    int fb4;
    int fb8;
    int fbc;
    unsigned short fc0;
    unsigned short fc2;
    int fc4;
} Obj;

extern const Vec3 data_021557d0;
extern void func_0207e7f0(Obj *obj);

void func_0207f9cc(Obj *obj, int mode)
{
    obj->f44 = *obj->f08->f18;
    obj->f60 = data_021557d0;
    obj->f6c = 0;
    obj->f6e = 0;
    obj->f70 = 0;
    obj->f74 = 0;
    obj->f78 = 0;
    obj->f7a = 0;
    obj->f80 = 0;
    obj->f7c = 0;
    obj->f84 = mode;
    obj->fa8 = 0;
    obj->fac = 0;
    obj->fb0 = 0;
    obj->fb4 = 0;
    obj->fb8 = 0;
    obj->fbc = -0x1000;
    obj->fc0 = 0;
    obj->fc2 = 0;
    obj->fc4 = 0;
    obj->f90 = 0;
    obj->f94 = 0;
    obj->f98 = 0;
    obj->fa0 = 0;
    func_0207e7f0(obj);
}
