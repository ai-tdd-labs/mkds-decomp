/* PURPOSE: Places a kart's shadow (or attached prop) in the world by adding the
   kart's position to its matrix and copying the driver's scaled offset values.
   Args: index = kart/player slot, v = kart world position (fx32 x,y,z).
   Behaviour: looks up the slot in the global table, grabs its shadow object
   (bails out if there is none), sets the object's position fields to
   position + the object's matrix translation, then multiplies three driver
   values (~0.9 in fx32) and copies them into the object. */

typedef struct { int x, y, z; } VecFx;

typedef struct Obj {
  char pad0[0x20];
  int **mtx;      /* +0x20: pointer to pointer to a matrix row */
  int _24;        /* +0x24 */
  int f28;        /* +0x28 */
  int f2c;        /* +0x2c */
  int f30;        /* +0x30 */
  char pad34[0x40 - 0x34];
  VecFx f40;      /* +0x40: scaled driver offset copied here */
} Obj;

typedef struct Ent {
  char pad0[0x2c];
  Obj *obj;       /* +0x2c */
  char pad30[0x58 - 0x30];
} Ent;             /* size 0x58 */

typedef struct Driver {
  char pad[0x3b0];
  int s0, s1, s2; /* +0x3b0, +0x3b4, +0x3b8 */
} Driver;

extern Ent *data_0217ae84;
extern Driver *GetDriverEntry(int index);

void func_02081618(int index, VecFx *v) {
  Ent *e = &data_0217ae84[index];
  Obj *o = e->obj;
  Driver *d;
  VecFx tmp;
  if (o == 0) return;
  o->f28 = v->x + (*o->mtx)[1];
  o->f2c = v->y + (*o->mtx)[2];
  o->f30 = v->z + (*o->mtx)[3];
  d = GetDriverEntry(index);
  {
    int *p = &d->s0;   /* ROM reserves callee-saved r6 = driver + 0x3b0 up front */
    tmp.x = (int)(((long long)d->s0 * 0x0E66LL) >> 12);
    tmp.y = (int)(((long long)p[1] * 0x0E66LL) >> 12);
    tmp.z = (int)(((long long)p[2] * 0x0E66LL) >> 12);
  }
  e->obj->f40 = tmp;
}
