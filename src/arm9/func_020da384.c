/* Initializes the water effect object: registers the object in a
 * global, clears two flags, sets field 0x66=0x1f, invokes a supplied
 * callback and fetches three file buffers (fields 0x174/0x178/0x17c
 * of the context). */
typedef unsigned short u16;

typedef struct Obj {
    unsigned char _a[2];
    volatile u16 flags;             /* 0x02 */
    unsigned char _b[0x66 - 0x04];
    u16 field_66;                   /* 0x66 */
} Obj;

typedef struct Ctx {
    unsigned char _p[0x174];
    void *field_174;                /* 0x174 */
    void *field_178;                /* 0x178 */
    void *field_17c;                /* 0x17c */
} Ctx;

extern Obj *data_0217b67c;          /* global object pointer */
extern Ctx *data_0217b678;          /* global context pointer */

extern int data_0216bde0;
extern int data_0216bdf8;
extern int data_0216be10;

extern void *FindFileBuffer_CRS_CST_from_thumb(void *desc);

void func_020da384(Obj *o, int unused, void (*fn)(void)) {
    data_0217b67c = o;
    o->flags &= ~2;
    o->flags &= ~8;
    o->field_66 = 0x1f;
    fn();
    data_0217b678->field_174 = FindFileBuffer_CRS_CST_from_thumb(&data_0216bde0);
    data_0217b678->field_178 = FindFileBuffer_CRS_CST_from_thumb(&data_0216bdf8);
    data_0217b678->field_17c = FindFileBuffer_CRS_CST_from_thumb(&data_0216be10);
}
